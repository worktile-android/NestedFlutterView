import 'dart:ffi';
import 'dart:ui' show window;

import 'ffi/allocation.dart';
import 'nested_flutter_view.dart';
import 'nested_flutter_view_bindings_generated.dart';

final DynamicLibrary _dylib = () {
  return DynamicLibrary.open('libnested_flutter_view.so');
}();

final NestedFlutterViewBindings _bindings = NestedFlutterViewBindings(_dylib);

void requestParentDisallowInterceptTouchEvent(bool disallowIntercept) {
  if (nestedFlutterViewHandler != 0) {
    _bindings.request_parent_disallow_intercept_touch_event(
      nestedFlutterViewHandler,
      disallowIntercept ? 1 : 0,
    );
  }
}

void startNestedScroll(int axis, int type) {
  if (nestedFlutterViewHandler != 0) {
    _bindings.start_nested_scroll_2(nestedFlutterViewHandler, axis, type);
  }
}

void stopNestedScroll(int type) {
  if (nestedFlutterViewHandler != 0) {
    _bindings.stop_nested_scroll_2(nestedFlutterViewHandler, type);
  }
}

bool dispatchNestedPreScroll(
    int dx, int dy, List<int> consumed, List<int> offsetInWindow, int type) {
  if (nestedFlutterViewHandler != 0) {
    Pointer<Int32> consumedArray = malloc.allocate(sizeOf<Int32>() * 2);
    Pointer<Int32> offsetInWindowArray = malloc.allocate(sizeOf<Int32>() * 2);
    int result = _bindings.dispatch_nested_pre_scroll_2(
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
    _bindings.dispatch_nested_scroll_3(
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
    var result = _bindings.dispatch_nested_pre_fling_1(
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
    var result = _bindings.dispatch_nested_fling_1(
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
    return _bindings.get_y_velocity(nestedFlutterViewHandler) /
        window.devicePixelRatio;
  }
  return 0;
}
