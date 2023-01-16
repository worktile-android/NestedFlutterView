//
// Created by 马星海 on 2023/1/14.
//

#include <pthread.h>
#include "dart_caller.h"
#include "macros.h"

shared_ptr<DartCaller> DartCaller::instance_ = nullptr;

DartCaller::DartCaller() = default;

DartCaller::~DartCaller() = default;

shared_ptr<DartCaller> DartCaller::GetInstance() {
  if (instance_ == nullptr) {
    shared_ptr<DartCaller> instance(new DartCaller);
    instance_ = instance;
  }
  return instance_;
}

void DartCaller::Call(const function<void()> &invoke) const {
  auto invoke_unique_ptr = make_unique<function<void()>>(invoke);
  auto invoke_ptr = invoke_unique_ptr.release();
  Dart_CObject message;
  message.type = Dart_CObject_kInt64;
  message.value.as_int64 = (int64_t) invoke_ptr;
  Dart_PostCObject_DL(send_port_, &message);
}
