//
// Created by 马星海 on 2023/1/4.
//

#include "jni_ref_cache.h"

shared_ptr<JniRefCache> JniRefCache::shared_jni_ref_cache_ = nullptr;

JniRefCache::JniRefCache() = default;

JniRefCache::~JniRefCache() = default;

shared_ptr<JniRefCache> JniRefCache::GetInstance() {
  if (shared_jni_ref_cache_ == nullptr) {
    shared_ptr<JniRefCache> instance(new JniRefCache());
    shared_jni_ref_cache_ = instance;
  }
  return shared_jni_ref_cache_;
}

void JniRefCache::CacheJniReferences(JNIEnv *env) {
  env_ = env;
  nested_flutter_view_class_ = env->FindClass("com/worktile/flutter/NestedFlutterView");

  start_nested_scroll_1_ = env->GetMethodID(nested_flutter_view_class_, "startNestedScroll", "(I)Z");
  stop_nested_scroll_1_ = env->GetMethodID(nested_flutter_view_class_, "stopNestedScroll", "()V");
  dispatch_nested_scroll_1_ = env->GetMethodID(nested_flutter_view_class_, "dispatchNestedScroll", "(IIII[I)Z");
  dispatch_nested_pre_scroll_1_ = env->GetMethodID(nested_flutter_view_class_, "dispatchNestedPreScroll", "(II[I[I)Z");
  dispatch_nested_fling_1_ = env->GetMethodID(nested_flutter_view_class_, "dispatchNestedFling", "(FFZ)Z");
  dispatch_nested_pre_fling_1_ = env->GetMethodID(nested_flutter_view_class_, "dispatchNestedPreFling", "(FF)Z");

  start_nested_scroll_2_ = env->GetMethodID(nested_flutter_view_class_, "startNestedScroll", "(II)Z");
  stop_nested_scroll_2_ = env->GetMethodID(nested_flutter_view_class_, "stopNestedScroll", "(I)V");
  dispatch_nested_scroll_2_ = env->GetMethodID(nested_flutter_view_class_, "dispatchNestedScroll", "(IIII[II)Z");
  dispatch_nested_pre_scroll_2_ = env->GetMethodID(nested_flutter_view_class_, "dispatchNestedPreScroll", "(II[I[II)Z");

  dispatch_nested_scroll_3_ = env->GetMethodID(nested_flutter_view_class_, "dispatchNestedScroll", "(IIII[II[I)V");

  request_parent_disallow_intercept_touch_event_ = env->GetMethodID(nested_flutter_view_class_, "requestParentDisallowInterceptTouchEvent", "(Z)V");
  get_y_velocity_ = env->GetMethodID(nested_flutter_view_class_, "getYVelocity", "()F");
}

