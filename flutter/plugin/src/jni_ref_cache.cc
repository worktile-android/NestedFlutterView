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

