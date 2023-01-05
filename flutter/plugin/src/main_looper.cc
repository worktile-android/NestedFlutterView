//
// Created by 马星海 on 2023/1/4.
//

#include <unistd.h>
#include "main_looper.h"

shared_ptr<MainLooper> MainLooper::shared_main_looper_ = nullptr;

MainLooper::MainLooper() {
  pthread_mutex_init(&looper_mutex_, nullptr);
}

MainLooper::~MainLooper() {
  if (android_main_looper_ && read_pipe_ != -1) {
    ALooper_removeFd(android_main_looper_, read_pipe_);
    ALooper_release(android_main_looper_);
  }
  if (read_pipe_ != -1) {
    close(read_pipe_);
  }
  if (write_pipe_ != -1) {
    close(write_pipe_);
  }
  pthread_mutex_destroy(&looper_mutex_);
}

shared_ptr<MainLooper> MainLooper::GetInstance() {
  if (shared_main_looper_ == nullptr) {
    shared_ptr<MainLooper> instance(new MainLooper());
    shared_main_looper_ = instance;
  }
  return shared_main_looper_;
}

void MainLooper::Init() {
  int message_pipe[2];
  pipe(message_pipe);
  read_pipe_ = message_pipe[0];
  write_pipe_ = message_pipe[1];

  android_main_looper_ = ALooper_prepare(0);
  ALooper_addFd(android_main_looper_, read_pipe_, 1, ALOOPER_EVENT_INPUT, MainLooper::HandleMessage,
                nullptr);
}

void MainLooper::Call(const function<void()>& invoke) const {
  auto invoke_unique_ptr = make_unique<function<void()>>(invoke);
  auto invoke_ptr = invoke_unique_ptr.release();
  write(write_pipe_, &invoke_ptr, sizeof(intptr_t));
}

int MainLooper::HandleMessage(int fd, int events, void *data) {
  function<void()>* invoke_ptr = nullptr;
  if (read(fd, &invoke_ptr, sizeof(intptr_t)) != -1) {
    unique_ptr<function<void()>> invoke_unique_ptr(invoke_ptr);
    (*invoke_unique_ptr)();
  }
  return 1;
}
