//
// Created by 马星海 on 2023/1/14.
//

#ifndef NESTEDFLUTTERVIEW_FLUTTER_PLUGIN_SRC_DART_CALLER_H_
#define NESTEDFLUTTERVIEW_FLUTTER_PLUGIN_SRC_DART_CALLER_H_

#include <memory>
#include <functional>
#include "dart_api_dl.h"

using namespace std;

class DartCaller {
 public:
  DartCaller();
  ~DartCaller();
  static shared_ptr<DartCaller> GetInstance();
  void Call(const function<void()>& invoke) const;
  void set_send_port(int64_t port) { send_port_ = (Dart_Port) port; }

 private:
  Dart_Port send_port_{};
  static shared_ptr<DartCaller> instance_;
};

#endif //NESTEDFLUTTERVIEW_FLUTTER_PLUGIN_SRC_DART_CALLER_H_
