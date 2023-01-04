//
// Created by 马星海 on 2023/1/4.
//

#ifndef NESTEDFLUTTERVIEW_FLUTTER_PLUGIN_SRC_MAIN_LOOPER_H_
#define NESTEDFLUTTERVIEW_FLUTTER_PLUGIN_SRC_MAIN_LOOPER_H_

#include <functional>
#include <memory>
#include <pthread.h>
#include "android/looper.h"

using namespace std;

class MainLooper {
 public:
  static shared_ptr<MainLooper> GetInstance();
  ~MainLooper();
  void init();
  void call(const function<void()>& invoke) const;

 private:
  MainLooper();
  ALooper* android_main_looper_{};
  int read_pipe_{};
  int write_pipe_{};
  pthread_mutex_t looper_mutex_{};
  static int HandleMessage(int fd, int events, void* data);
  static shared_ptr<MainLooper> shared_main_looper_;
};

#endif //NESTEDFLUTTERVIEW_FLUTTER_PLUGIN_SRC_MAIN_LOOPER_H_
