//
// Created by 马星海 on 2023/1/4.
//

#ifndef NESTEDFLUTTERVIEW_FLUTTER_PLUGIN_SRC_JNI_REF_CACHE_H_
#define NESTEDFLUTTERVIEW_FLUTTER_PLUGIN_SRC_JNI_REF_CACHE_H_

#include <jni.h>
#include <memory>

using namespace std;

class JniRefCache {
 public:
  virtual ~JniRefCache();
  static shared_ptr<JniRefCache> GetInstance();

  void set_env(JNIEnv* env) { env_ = env; }
  JNIEnv* env() const { return env_; }

  void set_test(jmethodID test) { test_ = test; }
  jmethodID test() const { return test_; }

 private:
  JniRefCache();
  JNIEnv* env_{};
  jmethodID test_{};
  static shared_ptr<JniRefCache> shared_jni_ref_cache_;
};

#endif //NESTEDFLUTTERVIEW_FLUTTER_PLUGIN_SRC_JNI_REF_CACHE_H_
