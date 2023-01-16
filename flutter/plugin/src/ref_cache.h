//
// Created by 马星海 on 2023/1/4.
//

#ifndef NESTEDFLUTTERVIEW_FLUTTER_PLUGIN_SRC_REF_CACHE_H_
#define NESTEDFLUTTERVIEW_FLUTTER_PLUGIN_SRC_REF_CACHE_H_

#include <jni.h>
#include <memory>
#include <functional>

using namespace std;

class RefCache {
 public:
  virtual ~RefCache();
  static shared_ptr<RefCache> GetInstance();

  void cache_max_scroll_extent(int(*function)(int)) { max_scroll_extent_ = function; }
  function<int(int)> max_scroll_extent() const { return max_scroll_extent_; }

  void cache_min_scroll_extent(int(*function)(int)) { min_scroll_extent_ = function; }
  function<int(int)> min_scroll_extent() const { return min_scroll_extent_; }

  void cache_viewport_dimensions(int(*function)(int)) { viewport_dimensions_ = function; }
  function<int(int)> viewport_dimensions() const { return viewport_dimensions_; }

  void cache_pixels(int(*function)(int)) { pixels_ = function; }
  function<int(int)> pixels() const { return pixels_; }

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

  jmethodID request_parent_disallow_intercept_touch_event() const { return request_parent_disallow_intercept_touch_event_; }
  jmethodID get_y_velocity() const { return get_y_velocity_; }

  jfieldID horizontal_max_extent() const { return horizontal_max_extent_; }
  jfieldID horizontal_min_extent() const { return horizontal_min_extent_; }
  jfieldID horizontal_viewport_dimension() const { return horizontal_viewport_dimension_; }
  jfieldID horizontal_offset() const { return horizontal_offset_; }
  jfieldID vertical_max_extent() const { return vertical_max_extent_; }
  jfieldID vertical_min_extent() const { return vertical_min_extent_; }
  jfieldID vertical_viewport_dimension() const { return vertical_viewport_dimension_; }
  jfieldID vertical_offset() const { return vertical_offset_; }

 private:
  RefCache();

  function<int(int/*方向*/)> max_scroll_extent_{};
  function<int(int)> min_scroll_extent_{};
  function<int(int)> viewport_dimensions_{};
  function<int(int)> pixels_{};

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

  jmethodID request_parent_disallow_intercept_touch_event_{};
  jmethodID get_y_velocity_{};

  jfieldID horizontal_max_extent_{};
  jfieldID horizontal_min_extent_{};
  jfieldID horizontal_viewport_dimension_{};
  jfieldID horizontal_offset_{};
  jfieldID vertical_max_extent_{};
  jfieldID vertical_min_extent_{};
  jfieldID vertical_viewport_dimension_{};
  jfieldID vertical_offset_{};

  static shared_ptr<RefCache> shared_ref_cache_;
};

#endif //NESTEDFLUTTERVIEW_FLUTTER_PLUGIN_SRC_REF_CACHE_H_
