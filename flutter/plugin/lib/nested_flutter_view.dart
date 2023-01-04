import 'dart:ffi';
import 'dart:io';
import 'dart:typed_data';

import 'package:flutter/services.dart';
import 'package:flutter/widgets.dart';

import 'nested_flutter_view_bindings_generated.dart';

int nestedFlutterViewHandler = 0;

BasicMessageChannel<Object?>? handlerChannel;

final DynamicLibrary _dylib = () {
  return DynamicLibrary.open('libnested_flutter_view.so');
}();

final NestedFlutterViewBindings _bindings = NestedFlutterViewBindings(_dylib);

void deleteNestedFlutterViewHandler() {
  nestedFlutterViewHandler = 0;
}

class NestedScrollNotificationListener
    extends NotificationListener<ScrollNotification> {
  NestedScrollNotificationListener({Key? key, required Widget child})
      : super(
    key: key,
    child: child,
    onNotification: (scrollNotification) {
      print(DateTime.now().millisecondsSinceEpoch);
      _bindings.test(nestedFlutterViewHandler);
      return false;
    },
  ) {
    if (handlerChannel == null) {
      handlerChannel = const BasicMessageChannel<Object?>(
        "com.worktile.flutter.nested_flutter_view/handler",
        StandardMessageCodec(),
      );
      handlerChannel?.setMessageHandler(
            (message) =>
            Future(() {
              if (message is int) {
                nestedFlutterViewHandler = message;
                _bindings.cache_delete_nested_flutter_view_handle_function(
                  nestedFlutterViewHandler,
                  Pointer.fromFunction(deleteNestedFlutterViewHandler),
                );
              }
              return null;
            }),
      );
    }
  }
}

class NestedScrollPhysics extends ClampingScrollPhysics {
  const NestedScrollPhysics(
      {ScrollPhysics? parent = const RangeMaintainingScrollPhysics()})
      : super(parent: parent);

  @override
  Simulation? createBallisticSimulation(ScrollMetrics position,
      double velocity,) {
    if (velocity != 0) {
      print(DateTime.now().millisecondsSinceEpoch);
      _bindings.test(nestedFlutterViewHandler);
    }
    return super.createBallisticSimulation(position, velocity);
  }
}
