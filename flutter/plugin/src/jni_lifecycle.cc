//
// Created by 马星海 on 2023/1/3.
//

#include <jni.h>
#include "ref_cache.h"
#include "main_looper.h"

extern "C" {
jint JNI_OnLoad(JavaVM* vm, void* reserved) {
  JNIEnv* env;
  if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
    return -1;
  }
  RefCache::GetInstance()->CacheJniReferences(env);
  MainLooper::GetInstance()->Init();
  return JNI_VERSION_1_6;
}
}

