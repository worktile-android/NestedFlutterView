#include <jni.h>
#include <unordered_map>
#include "nested_flutter_view.h"
#include "ref_cache.h"
#include "main_looper.h"
#include "dart_api_dl.h"
#include "macros.h"
#include "dart_caller.h"

//#define BLOCK_WAIT(label) \
//timespec start{}; \
//clock_gettime(CLOCK_REALTIME, &start); \
//long long start_time = start.tv_sec * 1000 * 1000 * 1000 + start.tv_nsec; \
//while (!result_label) { \
//  timespec current{}; \
//  clock_gettime(CLOCK_REALTIME, &current); \
//  long long current_time = current.tv_sec * 1000 * 1000 * 1000 + current.tv_nsec; \
//  if (current_time - start_time > 10 * 1000 * 1000) { \
//    result_label = alloca(1); \
//  } \
//  usleep(1); \
//}

#define BLOCK_WAIT(label) \
while (!result_label) { \
  usleep(1); \
}

using namespace std;

FFI_PLUGIN_EXPORT intptr_t initDartApiDL(void *data) {
  return Dart_InitializeApiDL(data);
}

FFI_PLUGIN_EXPORT void registerSendPort(int64_t port) {
  DartCaller::GetInstance()->set_send_port(port);
}

FFI_PLUGIN_EXPORT void delegateInvoke(intptr_t invoke_ptr) {
  unique_ptr<function<void()>> invoke_unique_ptr(reinterpret_cast<function<void()>*>(invoke_ptr));
  (*invoke_unique_ptr)();
}

FFI_PLUGIN_EXPORT void cacheMaxScrollExtent(int(*function)(int)) {
  RefCache::GetInstance()->cache_max_scroll_extent(function);
}

FFI_PLUGIN_EXPORT void cacheMinScrollExtent(int(*function)(int)) {
  RefCache::GetInstance()->cache_min_scroll_extent(function);
}

FFI_PLUGIN_EXPORT void cacheViewportDimensions(int(*function)(int)) {
  RefCache::GetInstance()->cache_viewport_dimensions(function);
}

FFI_PLUGIN_EXPORT void cachePixels(int(*function)(int)) {
  RefCache::GetInstance()->cache_pixels(function);
}

FFI_PLUGIN_EXPORT uint8_t startNestedScroll_1(intptr_t handler, int32_t axes) {
  void *result_label = nullptr;
  auto result_ptr = (jboolean *) alloca(sizeof(jboolean));
  MainLooper::GetInstance()->Call([handler, axes, &result_ptr, &result_label]() {
    auto cache = RefCache::GetInstance();
    jboolean result = cache->env()->CallBooleanMethod(to_jobject(handler),
                                                      cache->start_nested_scroll_1(),
                                                      axes);
    *result_ptr = result;
    result_label = result_ptr;
  });
  BLOCK_WAIT(result_label)
  return *result_ptr;
}

FFI_PLUGIN_EXPORT void stopNestedScroll_1(intptr_t handler) {
  MainLooper::GetInstance()->Call([handler]() {
    auto cache = RefCache::GetInstance();
    cache->env()->CallVoidMethod(to_jobject(handler),
                                 cache->stop_nested_scroll_1());
  });
}

FFI_PLUGIN_EXPORT uint8_t dispatchNestedScroll_1(
    intptr_t handler, int32_t dx_consumed, int32_t dy_consumed, int32_t dx_unconsumed,
    int32_t dy_unconsumed, int32_t *offset_in_window) {
  void *result_label = nullptr;
  auto result_ptr = (jboolean *) alloca(sizeof(jboolean));
  MainLooper::GetInstance()->Call([handler, dx_consumed, dy_consumed, dx_unconsumed, dy_unconsumed, offset_in_window, &result_ptr, &result_label]() {
    auto cache = RefCache::GetInstance();
    auto env = cache->env();
    jintArray j_offset_in_window = env->NewIntArray(2);
    *result_ptr = env->CallBooleanMethod(to_jobject(handler),
                                         cache->dispatch_nested_scroll_1(),
                                         dx_consumed,
                                         dy_consumed,
                                         dx_unconsumed,
                                         dy_unconsumed,
                                         j_offset_in_window);
    auto offset_in_window_buffer = env->GetIntArrayElements(j_offset_in_window, JNI_FALSE);
    memcpy(offset_in_window, offset_in_window_buffer, 2 * sizeof(int));
    env->ReleaseIntArrayElements(j_offset_in_window, offset_in_window_buffer, JNI_ABORT);
    result_label = result_ptr;
  });
  BLOCK_WAIT(result_label)
  return *result_ptr;
}

FFI_PLUGIN_EXPORT uint8_t dispatchNestedPreScroll_1(intptr_t handler,
                                                    int32_t dx,
                                                    int32_t dy,
                                                    int32_t *consumed,
                                                    int32_t *offset_in_window) {
  void *result_label = nullptr;
  auto result_ptr = (jboolean *) alloca(sizeof(jboolean));
  MainLooper::GetInstance()->Call([handler, dx, dy, &consumed, &offset_in_window, &result_ptr, &result_label]() {
    auto cache = RefCache::GetInstance();
    auto env = cache->env();
    jintArray j_consumed = env->NewIntArray(2);
    jintArray j_offset_in_window = env->NewIntArray(2);
    *result_ptr = env->CallBooleanMethod(to_jobject(handler),
                                         cache->dispatch_nested_pre_scroll_1(),
                                         dx,
                                         dy,
                                         j_consumed,
                                         j_offset_in_window);
    auto consumed_buffer = env->GetIntArrayElements(j_consumed, JNI_FALSE);
    auto offset_in_window_buffer = env->GetIntArrayElements(j_offset_in_window, JNI_FALSE);
    memcpy(consumed, consumed_buffer, 2 * sizeof(int));
    memcpy(offset_in_window, offset_in_window_buffer, 2 * sizeof(int));
    env->ReleaseIntArrayElements(j_consumed, consumed_buffer, JNI_ABORT);
    env->ReleaseIntArrayElements(j_offset_in_window, offset_in_window_buffer, JNI_ABORT);
    result_label = result_ptr;
  });
  BLOCK_WAIT(result_label)
  return *result_ptr;
}

FFI_PLUGIN_EXPORT uint8_t dispatchNestedFling_1(intptr_t handler,
                                                float velocity_x,
                                                float velocity_y,
                                                uint8_t consumed) {
  void *result_label = nullptr;
  auto result_ptr = (jboolean *) alloca(sizeof(jboolean));
  MainLooper::GetInstance()->Call([handler, velocity_x, velocity_y, consumed, &result_ptr, &result_label]() {
    auto cache = RefCache::GetInstance();
    auto env = cache->env();
    *result_ptr = env->CallBooleanMethod(to_jobject(handler),
                                         cache->dispatch_nested_fling_1(),
                                         velocity_x,
                                         velocity_y,
                                         consumed);
    result_label = result_ptr;
  });
  BLOCK_WAIT(result_label)
  return *result_ptr;
}

FFI_PLUGIN_EXPORT uint8_t dispatchNestedPreFling_1(intptr_t handler,
                                                   float velocity_x,
                                                   float velocity_y) {
  void *result_label = nullptr;
  auto result_ptr = (jboolean *) alloca(sizeof(jboolean));
  MainLooper::GetInstance()->Call([handler, velocity_x, velocity_y, &result_ptr, &result_label]() {
    auto cache = RefCache::GetInstance();
    jboolean result = cache->env()->CallBooleanMethod(
        to_jobject(handler),
        cache->dispatch_nested_pre_fling_1(),
        velocity_x,
        velocity_y
    );
    *result_ptr = result;
    result_label = result_ptr;
  });
  BLOCK_WAIT(result_label)
  return *result_ptr;
}

FFI_PLUGIN_EXPORT uint8_t startNestedScroll_2(intptr_t handler, int32_t axes, int32_t type) {
  void *result_label = nullptr;
  auto result_ptr = (jboolean *) alloca(sizeof(jboolean));
  MainLooper::GetInstance()->Call([handler, axes, type, &result_ptr, &result_label]() {
    auto cache = RefCache::GetInstance();
    jboolean result = cache->env()->CallBooleanMethod(to_jobject(handler),
                                                      cache->start_nested_scroll_2(),
                                                      axes,
                                                      type);
    *result_ptr = result;
    result_label = result_ptr;
  });
  BLOCK_WAIT(result_label)
  return *result_ptr;
}

FFI_PLUGIN_EXPORT void stopNestedScroll_2(intptr_t handler, int32_t type) {
  MainLooper::GetInstance()->Call([handler, type]() {
    auto cache = RefCache::GetInstance();
    cache->env()->CallVoidMethod(to_jobject(handler),
                                 cache->stop_nested_scroll_2(),
                                 type);
  });
}

FFI_PLUGIN_EXPORT uint8_t dispatchNestedScroll_2(
    intptr_t handler, int32_t dx_consumed, int32_t dy_consumed, int32_t dx_unconsumed,
    int32_t dy_unconsumed, int32_t *offset_in_window, int32_t type) {
  void *result_label = nullptr;
  auto result_ptr = (jboolean *) alloca(sizeof(jboolean));
  MainLooper::GetInstance()->Call([handler, dx_consumed, dy_consumed, dx_unconsumed, dy_unconsumed, offset_in_window, type, &result_ptr, &result_label]() {
    auto cache = RefCache::GetInstance();
    auto env = cache->env();
    jintArray j_offset_in_window = env->NewIntArray(2);
    *result_ptr = env->CallBooleanMethod(to_jobject(handler),
                                         cache->dispatch_nested_scroll_2(),
                                         dx_consumed,
                                         dy_consumed,
                                         dx_unconsumed,
                                         dy_unconsumed,
                                         j_offset_in_window,
                                         type);
    auto offset_in_window_buffer = env->GetIntArrayElements(j_offset_in_window, JNI_FALSE);
    memcpy(offset_in_window, offset_in_window_buffer, 2 * sizeof(int));
    env->ReleaseIntArrayElements(j_offset_in_window, offset_in_window_buffer, JNI_ABORT);
    result_label = result_ptr;
  });
  BLOCK_WAIT(result_label)
  return *result_ptr;
}

FFI_PLUGIN_EXPORT uint8_t dispatchNestedPreScroll_2(intptr_t handler,
                                                    int32_t dx,
                                                    int32_t dy,
                                                    int32_t *consumed,
                                                    int32_t *offset_in_window,
                                                    int32_t type) {
  void *result_label = nullptr;
  auto result_ptr = (jboolean *) alloca(sizeof(jboolean));
  MainLooper::GetInstance()->Call([handler, dx, dy, &consumed, &offset_in_window, type, &result_ptr, &result_label]() {
    auto cache = RefCache::GetInstance();
    auto env = cache->env();
    jintArray j_consumed = env->NewIntArray(2);
    jintArray j_offset_in_window = env->NewIntArray(2);
    *result_ptr = env->CallBooleanMethod(to_jobject(handler),
                                         cache->dispatch_nested_pre_scroll_2(),
                                         dx,
                                         dy,
                                         j_consumed,
                                         j_offset_in_window,
                                         type);
    auto consumed_buffer = env->GetIntArrayElements(j_consumed, JNI_FALSE);
    auto offset_in_window_buffer = env->GetIntArrayElements(j_offset_in_window, JNI_FALSE);
    memcpy(consumed, consumed_buffer, 2 * sizeof(int));
    memcpy(offset_in_window, offset_in_window_buffer, 2 * sizeof(int));
    env->ReleaseIntArrayElements(j_consumed, consumed_buffer, JNI_ABORT);
    env->ReleaseIntArrayElements(j_offset_in_window, offset_in_window_buffer, JNI_ABORT);
    result_label = result_ptr;
  });
  BLOCK_WAIT(result_label)
  return *result_ptr;
}

FFI_PLUGIN_EXPORT void dispatchNestedScroll_3(
    intptr_t handler, int32_t dx_consumed, int32_t dy_consumed, int32_t dx_unconsumed,
    int32_t dy_unconsumed, int32_t *offset_in_window, int32_t type, int32_t *consumed) {
  void *result_label = nullptr;
  MainLooper::GetInstance()->Call([handler, dx_consumed, dy_consumed, dx_unconsumed, dy_unconsumed, offset_in_window, type, &consumed, &result_label]() {
    auto cache = RefCache::GetInstance();
    auto env = cache->env();
    jintArray j_offset_in_window = env->NewIntArray(2);
    jintArray j_consumed = env->NewIntArray(2);
    env->CallVoidMethod(to_jobject(handler),
                        cache->dispatch_nested_scroll_3(),
                        dx_consumed,
                        dy_consumed,
                        dx_unconsumed,
                        dy_unconsumed,
                        j_offset_in_window,
                        type,
                        j_consumed);
    auto offset_in_window_buffer = env->GetIntArrayElements(j_offset_in_window, JNI_FALSE);
    auto consumed_buffer = env->GetIntArrayElements(j_consumed, JNI_FALSE);
    memcpy(offset_in_window, offset_in_window_buffer, 2 * sizeof(int));
    memcpy(consumed, consumed_buffer, 2 * sizeof(int));
    env->ReleaseIntArrayElements(j_offset_in_window, offset_in_window_buffer, JNI_ABORT);
    env->ReleaseIntArrayElements(j_consumed, consumed_buffer, JNI_ABORT);
    result_label = alloca(1);
  });
  BLOCK_WAIT(result_label)
}

FFI_PLUGIN_EXPORT void requestParentDisallowInterceptTouchEvent(intptr_t handler,
                                                                uint8_t disallowIntercept) {
  MainLooper::GetInstance()->Call([handler, disallowIntercept]() {
    auto cache = RefCache::GetInstance();
    auto env = cache->env();
    env->CallVoidMethod(to_jobject(handler),
                        cache->request_parent_disallow_intercept_touch_event(),
                        (jboolean) disallowIntercept);
  });
}

FFI_PLUGIN_EXPORT float getYVelocity(intptr_t handler) {
  void *result_label = nullptr;
  auto *result_ptr = (float *) alloca(sizeof(float));
  MainLooper::GetInstance()->Call([handler, &result_ptr, &result_label]() {
    auto cache = RefCache::GetInstance();
    auto env = cache->env();
    *result_ptr = env->CallFloatMethod(to_jobject(handler), cache->get_y_velocity());
    result_label = result_ptr;
  });
  BLOCK_WAIT(result_label)
  return *result_ptr;
}

FFI_PLUGIN_EXPORT void setHorizontalMaxExtent(intptr_t handler, int extent) {
  MainLooper::GetInstance()->Call([handler, extent](){
    auto cache = RefCache::GetInstance();
    auto env = cache->env();
    env->SetIntField(to_jobject(handler), cache->horizontal_max_extent(), extent);
  });
}

FFI_PLUGIN_EXPORT void setHorizontalMinExtent(intptr_t handler, int extent) {
  MainLooper::GetInstance()->Call([handler, extent](){
    auto cache = RefCache::GetInstance();
    auto env = cache->env();
    env->SetIntField(to_jobject(handler), cache->horizontal_min_extent(), extent);
  });
}

FFI_PLUGIN_EXPORT void setHorizontalViewportDimension(intptr_t handler, int viewport_dimension) {
  MainLooper::GetInstance()->Call([handler, viewport_dimension](){
    auto cache = RefCache::GetInstance();
    auto env = cache->env();
    env->SetIntField(to_jobject(handler), cache->horizontal_viewport_dimension(), viewport_dimension);
  });
}

FFI_PLUGIN_EXPORT void setHorizontalOffset(intptr_t handler, int offset) {
  MainLooper::GetInstance()->Call([handler, offset](){
    auto cache = RefCache::GetInstance();
    auto env = cache->env();
    env->SetIntField(to_jobject(handler), cache->horizontal_offset(), offset);
  });
}

FFI_PLUGIN_EXPORT void setVerticalMaxExtent(intptr_t handler, int extent) {
  MainLooper::GetInstance()->Call([handler, extent](){
    auto cache = RefCache::GetInstance();
    auto env = cache->env();
    env->SetIntField(to_jobject(handler), cache->vertical_max_extent(), extent);
  });
}

FFI_PLUGIN_EXPORT void setVerticalMinExtent(intptr_t handler, int extent) {
  MainLooper::GetInstance()->Call([handler, extent](){
    auto cache = RefCache::GetInstance();
    auto env = cache->env();
    env->SetIntField(to_jobject(handler), cache->vertical_min_extent(), extent);
  });
}

FFI_PLUGIN_EXPORT void setVerticalViewportDimension(intptr_t handler, int viewport_dimension) {
  MainLooper::GetInstance()->Call([handler, viewport_dimension](){
    auto cache = RefCache::GetInstance();
    auto env = cache->env();
    env->SetIntField(to_jobject(handler), cache->vertical_viewport_dimension(), viewport_dimension);
  });
}

FFI_PLUGIN_EXPORT void setVerticalOffset(intptr_t handler, int offset) {
  MainLooper::GetInstance()->Call([handler, offset](){
    auto cache = RefCache::GetInstance();
    auto env = cache->env();
    env->SetIntField(to_jobject(handler), cache->vertical_offset(), offset);
  });
}

extern "C" JNIEXPORT jlong JNICALL
Java_com_worktile_flutter_DelegateNestedFlutterView_flutterViewHandler(JNIEnv *env, jobject thiz) {
  return (jlong) env->NewWeakGlobalRef(thiz);
}