//
// Created by 马星海 on 2023/1/3.
//

#include <jni.h>
#include "jni_ref_cache.h"
#include "main_looper.h"

extern "C" {
jint JNI_OnLoad(JavaVM* vm, void* reserved) {
  JNIEnv* env;
  if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
    return -1;
  }
  JniRefCache::GetInstance()->set_env(env);
  jclass nested_flutter_view_class = env->FindClass("com/worktile/flutter/NestedFlutterView");
  jmethodID test_method = env->GetMethodID(nested_flutter_view_class, "test", "()V");
  JniRefCache::GetInstance()->set_test(test_method);

  MainLooper::GetInstance()->init();

  env->DeleteLocalRef(nested_flutter_view_class);
  return JNI_VERSION_1_6;
}
}

