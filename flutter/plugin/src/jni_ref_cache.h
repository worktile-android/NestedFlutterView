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

  void CacheJniReferences(JNIEnv* env);
  JNIEnv* env() const { return env_; }

  jmethodID start_nested_scroll_1() const { return start_nested_scroll_1_; }
  jmethodID stop_nested_scroll_1() const { return stop_nested_scroll_1_; }
  jmethodID dispatch_nested_scroll_1() const { return dispatch_nested_scroll_1_; }
  jmethodID dispatch_nested_pre_scroll_1() const { return dispatch_nested_pre_scroll_1_; }
  jmethodID dispatch_nested_fling_1() const { return dispatch_nested_fling_1_; }
  jmethodID dispatch_nested_pre_fling_1() const { return dispatch_nested_pre_fling_1_; }

  jmethodID start_nested_scroll_2() const { return start_nested_scroll_2_; }
  jmethodID stop_nested_scroll_2() const { return stop_nested_scroll_2_; }
  jmethodID dispatch_nested_scroll_2() const { return dispatch_nested_scroll_2_; }
  jmethodID dispatch_nested_pre_scroll_2() const { return dispatch_nested_pre_scroll_2_; }

  jmethodID dispatch_nested_scroll_3() const { return dispatch_nested_scroll_3_; }

  jmethodID test_result_array() const { return test_result_array_; }

 private:
  JniRefCache();
  JNIEnv* env_{};
  jclass nested_flutter_view_class_{};

  jmethodID start_nested_scroll_1_{};
  jmethodID stop_nested_scroll_1_{};
  jmethodID dispatch_nested_scroll_1_{};
  jmethodID dispatch_nested_pre_scroll_1_{};
  jmethodID dispatch_nested_fling_1_{};
  jmethodID dispatch_nested_pre_fling_1_{};

  jmethodID start_nested_scroll_2_{};
  jmethodID stop_nested_scroll_2_{};
  jmethodID dispatch_nested_scroll_2_{};
  jmethodID dispatch_nested_pre_scroll_2_{};

  jmethodID dispatch_nested_scroll_3_{};

  jmethodID test_result_array_{};

  static shared_ptr<JniRefCache> shared_jni_ref_cache_;
};

#endif //NESTEDFLUTTERVIEW_FLUTTER_PLUGIN_SRC_JNI_REF_CACHE_H_
