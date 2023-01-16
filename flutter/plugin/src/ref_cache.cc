//
// Created by 马星海 on 2023/1/4.
//

#include "ref_cache.h"

shared_ptr<RefCache> RefCache::shared_ref_cache_ = nullptr;

RefCache::RefCache() = default;

RefCache::~RefCache() = default;

shared_ptr<RefCache> RefCache::GetInstance() {
  if (shared_ref_cache_ == nullptr) {
    shared_ptr<RefCache> instance(new RefCache());
    shared_ref_cache_ = instance;
  }
  return shared_ref_cache_;
}

void RefCache::CacheJniReferences(JNIEnv *env) {
  env_ = env;
  nested_flutter_view_class_ = env->FindClass("com/worktile/flutter/DelegateNestedFlutterView");

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

  horizontal_max_extent_ = env->GetFieldID(nested_flutter_view_class_, "horizontalMaxExtent", "I");
  horizontal_min_extent_ = env->GetFieldID(nested_flutter_view_class_, "horizontalMinExtent", "I");
  horizontal_viewport_dimension_ = env->GetFieldID(nested_flutter_view_class_, "horizontalViewportDimension", "I");
  horizontal_offset_ = env->GetFieldID(nested_flutter_view_class_, "horizontalOffset", "I");
  vertical_max_extent_ = env->GetFieldID(nested_flutter_view_class_, "verticalMaxExtent", "I");
  vertical_min_extent_ = env->GetFieldID(nested_flutter_view_class_, "verticalMinExtent", "I");
  vertical_viewport_dimension_ = env->GetFieldID(nested_flutter_view_class_, "verticalViewportDimension", "I");
  vertical_offset_ = env->GetFieldID(nested_flutter_view_class_, "verticalOffset", "I");
}

