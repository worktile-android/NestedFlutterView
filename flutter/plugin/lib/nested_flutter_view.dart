import 'dart:ffi';
import 'dart:isolate';
import 'dart:ui' show window;

import 'package:flutter/foundation.dart';
import 'package:flutter/gestures.dart';
import 'package:flutter/rendering.dart';
import 'package:flutter/services.dart';
import 'package:flutter/widgets.dart';
import 'package:nested_flutter_view/constants.dart';
import 'package:nested_flutter_view/nested_channel.dart';

@protected
int nestedFlutterViewHandler = 0;
ScrollPosition? _connectedScrollPosition;

BasicMessageChannel<Object?>? _handlerChannel;

final ReceivePort _receivePort = () {
  return ReceivePort()
    ..listen(
      (message) {
        int invokePtr = message;
        bindings.delegateInvoke(invokePtr);
      },
    );
}();

final double _dpr = window.devicePixelRatio;

@protected
extension RoundDevicePixel on double {
  int roundDevicePixel() {
    double dpr = window.devicePixelRatio;
    int devicePixelAbs = (this * dpr).abs().round();
    if (this > 0) {
      return devicePixelAbs;
    } else if (this < 0) {
      return -devicePixelAbs;
    } else {
      return devicePixelAbs;
    }
  }
}

///
/// 不要把一个[NestedScrollController]作用于多个可滚动Widget
///
class NestedScrollController extends ScrollController {
  NestedScrollController({
    super.initialScrollOffset,
    super.keepScrollOffset,
    super.debugLabel,
  });

  @override
  ScrollPosition createScrollPosition(ScrollPhysics physics,
      ScrollContext context, ScrollPosition? oldPosition) {
    _connectedScrollPosition = null;
    var scrollPosition = NestedScrollPosition(
      physics: physics,
      context: context,
      initialPixels: initialScrollOffset,
      keepScrollOffset: keepScrollOffset,
      oldPosition: oldPosition,
      debugLabel: debugLabel,
    );
    _connectedScrollPosition = scrollPosition;

    if (_handlerChannel == null) {
      _handlerChannel = const BasicMessageChannel<Object?>(
        "com.worktile.flutter.nested_flutter_view/handler",
        StandardMessageCodec(),
      );
      _handlerChannel?.setMessageHandler((message) {
        return Future(() {
          if (message is int) {
            nestedFlutterViewHandler = message;
            scrollPosition.setViewportDimension();
            scrollPosition.setMinExtent();
            scrollPosition.setMaxExtent();
            scrollPosition.setOffset();
          }
          return null;
        });
      });
    }

    return scrollPosition;
  }

  @override
  void dispose() {
    _connectedScrollPosition = null;
    super.dispose();
  }
}

class NestedScrollPosition extends ScrollPositionWithSingleContext {
  NestedScrollPosition({
    required super.physics,
    required super.context,
    super.initialPixels,
    super.keepScrollOffset,
    super.oldPosition,
    super.debugLabel,
  });

  List<int> offsetInWindowByDrag = [0, 0];

  bool _fromDragEnd = false;

  set fromDragEnd(bool value) => _fromDragEnd = value;

  late int directionIndex = () {
    switch (axis) {
      case Axis.horizontal:
        return 0;
      case Axis.vertical:
        return 1;
    }
  }();

  @override
  Drag drag(DragStartDetails details, VoidCallback dragCancelCallback) {
    var result = super.drag(details, () {
      stopNestedScroll(typeTouch);
      dragCancelCallback();
    });
    switch (axis) {
      case Axis.horizontal:
        startNestedScroll(scrollAxisHorizontal, typeTouch);
        break;
      case Axis.vertical:
        startNestedScroll(scrollAxisVertical, typeTouch);
        break;
    }
    offsetInWindowByDrag[0] = 0;
    offsetInWindowByDrag[1] = 0;
    if (result is ScrollDragController) {
      result = ScrollDragControllerDelegate(controller: result, position: this);
    }

    return result;
  }

  // 手指向上滑动：
  // Android: delta正数，consumed[]正数，offsetInWindow负数
  // Flutter: delta负数，方向为ScrollDirection.reserve
  double nestedScroll(double delta, int type) {
    int deltaDevicePixel = -delta.roundDevicePixel();

    if (deltaDevicePixel == 0) {
      return 0;
    }

    int dx = 0, dy = 0;
    switch (axis) {
      case Axis.horizontal:
        dx = deltaDevicePixel;
        break;
      case Axis.vertical:
        dy = deltaDevicePixel;
        break;
    }
    List<int> consumed = [];
    List<int> offsetInWindow = [];
    List<int> dragOffset = [0, 0];
    if (dispatchNestedPreScroll(dx, dy, consumed, offsetInWindow, type)) {
      dragOffset[0] += offsetInWindow[0];
      dragOffset[1] += offsetInWindow[1];

      deltaDevicePixel -= consumed[directionIndex];

      requestParentDisallowInterceptTouchEvent(true);
    }

    // overscroll的符号：当手指上滑到底时，为正数
    double overscroll = () {
      if (deltaDevicePixel != 0) {
        return physics.applyBoundaryConditions(
          this,
          pixels + deltaDevicePixel / _dpr,
        );
      } else {
        return 0.0;
      }
    }();
    int unconsumedDevicePixel = overscroll.roundDevicePixel();
    int consumedDevicePixel = deltaDevicePixel - unconsumedDevicePixel;

    correctPixels(pixels + consumedDevicePixel / _dpr);
    if (consumedDevicePixel != 0) {
      updateUserScrollDirection(
        delta > 0.0 ? ScrollDirection.forward : ScrollDirection.reverse,
      );
      notifyListeners();
      didUpdateScrollPositionBy(consumedDevicePixel / _dpr);
      requestParentDisallowInterceptTouchEvent(true);
    }

    int dxConsumed = 0, dyConsumed = 0, dxUnconsumed = 0, dyUnconsumed = 0;
    switch (axis) {
      case Axis.horizontal:
        dxConsumed = consumedDevicePixel;
        dxUnconsumed = unconsumedDevicePixel;
        break;
      case Axis.vertical:
        dyConsumed = consumedDevicePixel;
        dyUnconsumed = unconsumedDevicePixel;
        break;
    }
    offsetInWindow[0] = 0;
    offsetInWindow[1] = 0;
    consumed[0] = 0;
    consumed[1] = 0;

    dispatchNestedScroll(
      dxConsumed,
      dyConsumed,
      dxUnconsumed,
      dyUnconsumed,
      offsetInWindow,
      type,
      consumed,
    );

    dragOffset[0] += offsetInWindow[0];
    dragOffset[1] += offsetInWindow[1];
    offsetInWindowByDrag[0] = dragOffset[0];
    offsetInWindowByDrag[1] = dragOffset[1];

    unconsumedDevicePixel -= consumed[directionIndex];
    overscroll = unconsumedDevicePixel / _dpr;
    if (overscroll != 0) {
      didOverscrollBy(overscroll);
    }
    return overscroll;
  }

  @override
  void applyUserOffset(double delta) {
    delta += offsetInWindowByDrag[directionIndex] / _dpr;
    nestedScroll(delta, typeTouch);
  }

  @override
  void goBallistic(double velocity) {
    // 通常drag结束之后会调用到这里，然后把手指离开时的速度传递过来，以便开始fling？
    if (_fromDragEnd) {
      velocity = getYVelocity();
      _fromDragEnd = false;
    }

    Simulation? simulation = () {
      if (velocity.abs() < physics.tolerance.velocity) {
        return null;
      }
      return ClampingScrollSimulation(
        position: pixels,
        velocity: velocity,
        tolerance: physics.tolerance,
      );
    }();
    if (simulation != null) {
      switch (axis) {
        case Axis.horizontal:
          startNestedScroll(scrollAxisHorizontal, typeTouch);
          break;
        case Axis.vertical:
          startNestedScroll(scrollAxisVertical, typeTouch);
          break;
      }
      if (!dispatchNestedPreFling(velocity * _dpr)) {
        dispatchNestedFling(velocity * _dpr);
        stopNestedScroll(typeTouch);
        switch (axis) {
          case Axis.horizontal:
            startNestedScroll(scrollAxisHorizontal, typeNonTouch);
            break;
          case Axis.vertical:
            startNestedScroll(scrollAxisVertical, typeNonTouch);
            break;
        }
        beginActivity(
          NestedBallisticScrollActivity(this, simulation, context.vsync,
              activity?.shouldIgnorePointer ?? true),
        );
      }
      stopNestedScroll(typeTouch);
    } else {
      goIdle();
    }
  }

  @override
  void goIdle() {
    stopNestedScroll(typeNonTouch);
    super.goIdle();
  }

  @override
  void absorb(ScrollPosition other) {
    super.absorb(other);
    setOffset();
    setMaxExtent();
    setMinExtent();
    setViewportDimension();
  }

  @override
  void correctBy(double correction) {
    super.correctBy(correction);
    setOffset();
  }

  @override
  void correctPixels(double value) {
    super.correctPixels(value);
    setOffset();
  }

  @override
  void forcePixels(double value) {
    super.forcePixels(value);
    setOffset();
  }

  @override
  double setPixels(double newPixels) {
    double result = super.setPixels(newPixels);
    setOffset();
    return result;
  }

  @override
  bool applyContentDimensions(double minScrollExtent, double maxScrollExtent) {
    bool result =
        super.applyContentDimensions(minScrollExtent, maxScrollExtent);
    setMaxExtent();
    setMinExtent();
    return result;
  }

  @override
  bool applyViewportDimension(double viewportDimension) {
    bool result = super.applyViewportDimension(viewportDimension);
    setViewportDimension();
    return result;
  }
}

class ScrollDragControllerDelegate extends Drag {
  ScrollDragControllerDelegate({
    required ScrollDragController controller,
    required NestedScrollPosition position,
  })  : _controller = controller,
        _position = position;

  final ScrollDragController _controller;

  final NestedScrollPosition _position;

  @override
  void update(DragUpdateDetails details) {
    _controller.update(details);
  }

  @override
  void end(DragEndDetails details) {
    _position.fromDragEnd = true;
    _controller.end(details);
  }

  @override
  void cancel() {
    _controller.cancel();
  }
}

class NestedBallisticScrollActivity extends BallisticScrollActivity {
  NestedBallisticScrollActivity(
    super.delegate,
    super.simulation,
    super.vsync,
    super.shouldIgnorePointer,
  );

  int nestedOffsetY = 0;

  late final ScrollPosition? _position = () {
    if (delegate is ScrollPosition) {
      return delegate as ScrollPosition;
    } else {
      return null;
    }
  }();

  late double _previousOffset = () {
    return _position?.pixels ?? 0;
  }();

  @override
  bool applyMoveTo(double value) {
    // 通过simulation计算之后会调用到这里，把每次需要滚动到的距离传递到这里
    double delta = _previousOffset - value;
    _previousOffset = value;
    if (delegate is NestedScrollPosition) {
      return (delegate as NestedScrollPosition)
              .nestedScroll(delta, typeNonTouch)
              .abs() <
          precisionErrorTolerance;
    }
    return super.applyMoveTo(value);
  }
}
