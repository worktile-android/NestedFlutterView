import 'dart:ffi';
import 'dart:ui' show window;

import 'package:flutter/widgets.dart';

import 'ffi/allocation.dart';
import 'nested_flutter_view.dart';
import 'nested_flutter_view_bindings_generated.dart';

final DynamicLibrary _dylib = () {
  return DynamicLibrary.open('libnested_flutter_view.so');
}();

@protected
final NestedFlutterViewBindings bindings = NestedFlutterViewBindings(_dylib);

void requestParentDisallowInterceptTouchEvent(bool disallowIntercept) {
  if (nestedFlutterViewHandler != 0) {
    bindings.requestParentDisallowInterceptTouchEvent(
      nestedFlutterViewHandler,
      disallowIntercept ? 1 : 0,
    );
  }
}

void startNestedScroll(int axis, int type) {
  if (nestedFlutterViewHandler != 0) {
    bindings.startNestedScroll_2(nestedFlutterViewHandler, axis, type);
  }
}

void stopNestedScroll(int type) {
  if (nestedFlutterViewHandler != 0) {
    bindings.stopNestedScroll_2(nestedFlutterViewHandler, type);
  }
}

bool dispatchNestedPreScroll(
    int dx, int dy, List<int> consumed, List<int> offsetInWindow, int type) {
  if (nestedFlutterViewHandler != 0) {
    Pointer<Int32> consumedArray = malloc.allocate(sizeOf<Int32>() * 2);
    Pointer<Int32> offsetInWindowArray = malloc.allocate(sizeOf<Int32>() * 2);
    int result = bindings.dispatchNestedPreScroll_2(
      nestedFlutterViewHandler,
      dx,
      dy,
      consumedArray,
      offsetInWindowArray,
      type,
    );
    consumed.clear();
    consumed.addAll(consumedArray.asTypedList(2));
    offsetInWindow.clear();
    offsetInWindow.addAll(offsetInWindowArray.asTypedList(2));
    malloc.free(consumedArray);
    malloc.free(offsetInWindowArray);
    return result > 0;
  }
  return false;
}

void dispatchNestedScroll(int dxConsumed, int dyConsumed, int dxUnconsumed,
    int dyUnconsumed, List<int> offsetInWindow, int type, List<int> consumed) {
  if (nestedFlutterViewHandler != 0) {
    Pointer<Int32> consumedArray = malloc.allocate(sizeOf<Int32>() * 2);
    Pointer<Int32> offsetInWindowArray = malloc.allocate(sizeOf<Int32>() * 2);
    bindings.dispatchNestedScroll_3(
      nestedFlutterViewHandler,
      dxConsumed,
      dyConsumed,
      dxUnconsumed,
      dyUnconsumed,
      offsetInWindowArray,
      type,
      consumedArray,
    );
    consumed.clear();
    consumed.addAll(consumedArray.asTypedList(2));
    offsetInWindow.clear();
    offsetInWindow.addAll(offsetInWindowArray.asTypedList(2));
    malloc.free(consumedArray);
    malloc.free(offsetInWindowArray);
  }
}

bool dispatchNestedPreFling(double yVelocity) {
  if (nestedFlutterViewHandler != 0) {
    var result = bindings.dispatchNestedPreFling_1(
      nestedFlutterViewHandler,
      0,
      yVelocity,
    );
    return result > 0;
  }
  return false;
}

bool dispatchNestedFling(double yVelocity) {
  if (nestedFlutterViewHandler != 0) {
    var result = bindings.dispatchNestedFling_1(
      nestedFlutterViewHandler,
      0,
      yVelocity,
      1,
    );
    return result > 0;
  }
  return false;
}

double getYVelocity() {
  if (nestedFlutterViewHandler != 0) {
    return bindings.getYVelocity(nestedFlutterViewHandler) /
        window.devicePixelRatio;
  }
  return 0;
}

@protected
extension ScrollPositionChannelExtension on ScrollPosition {
  void setMaxExtent() {
    if (nestedFlutterViewHandler != 0) {
      final maxExtent = maxScrollExtent.roundDevicePixel();
      switch (axis) {
        case Axis.horizontal:
          bindings.setHorizontalMaxExtent(nestedFlutterViewHandler, maxExtent);
          break;
        case Axis.vertical:
          bindings.setVerticalMaxExtent(nestedFlutterViewHandler, maxExtent);
          break;
      }
    }
  }

  void setMinExtent() {
    if (nestedFlutterViewHandler != 0) {
      final minExtent = minScrollExtent.roundDevicePixel();
      switch (axis) {
        case Axis.horizontal:
          bindings.setHorizontalMinExtent(nestedFlutterViewHandler, minExtent);
          break;
        case Axis.vertical:
          bindings.setVerticalMinExtent(nestedFlutterViewHandler, minExtent);
          break;
      }
    }
  }

  void setViewportDimension() {
    if (nestedFlutterViewHandler != 0) {
      final dimension = viewportDimension.roundDevicePixel();
      switch (axis) {
        case Axis.horizontal:
          bindings.setHorizontalViewportDimension(nestedFlutterViewHandler, dimension);
          break;
        case Axis.vertical:
          bindings.setVerticalViewportDimension(nestedFlutterViewHandler, dimension);
          break;
      }
    }
  }

  void setOffset() {
    if (nestedFlutterViewHandler != 0) {
      final offset = pixels.roundDevicePixel();
      switch (axis) {
        case Axis.horizontal:
          bindings.setHorizontalOffset(nestedFlutterViewHandler, offset);
          break;
        case Axis.vertical:
          bindings.setVerticalOffset(nestedFlutterViewHandler, offset);
          break;
      }
    }
  }
}
