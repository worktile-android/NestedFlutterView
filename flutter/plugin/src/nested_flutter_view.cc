#include <jni.h>
#include <unordered_map>
#include "nested_flutter_view.h"
#include "jni_ref_cache.h"
#include "main_looper.h"
#include "dart_api_dl.h"
#include "macros.h"

#define BLOCK_WAIT(label) \
timespec start{}; \
clock_gettime(CLOCK_REALTIME, &start); \
long long start_time = start.tv_sec * 1000 * 1000 * 1000 + start.tv_nsec; \
while (!result_label) { \
  timespec current{}; \
  clock_gettime(CLOCK_REALTIME, &current); \
  long long current_time = current.tv_sec * 1000 * 1000 * 1000 + current.tv_nsec; \
  if (current_time - start_time > 10 * 1000 * 1000) { \
    result_label = alloca(1); \
  } \
  usleep(1); \
}

using namespace std;

static unordered_map<intptr_t, void (*)()> kCachedDeleteNestedFlutterViewHandlerFunctions;

extern "C" {
FFI_PLUGIN_EXPORT void cache_delete_nested_flutter_view_handle_function(intptr_t shell_id,
                                                                        void (*function)()) {
  kCachedDeleteNestedFlutterViewHandlerFunctions.insert(make_pair(shell_id, function));
}

FFI_PLUGIN_EXPORT uint8_t start_nested_scroll_1(intptr_t handler, int32_t axes) {
  void *result_label = nullptr;
  auto result_ptr = (jboolean *) alloca(sizeof(jboolean));
  MainLooper::GetInstance()->Call([handler, axes, &result_ptr, &result_label]() {
    auto cache = JniRefCache::GetInstance();
    jboolean result = cache->env()->CallBooleanMethod(to_jobject(handler),
                                                      cache->start_nested_scroll_1(),
                                                      axes);
    *result_ptr = result;
    result_label = result_ptr;
  });
  BLOCK_WAIT(result_label)
  return *result_ptr;
}

FFI_PLUGIN_EXPORT void stop_nested_scroll_1(intptr_t handler) {
  MainLooper::GetInstance()->Call([handler]() {
    auto cache = JniRefCache::GetInstance();
    cache->env()->CallVoidMethod(to_jobject(handler),
                                 cache->stop_nested_scroll_1());
  });
}

FFI_PLUGIN_EXPORT uint8_t dispatch_nested_scroll_1(
    intptr_t handler, int32_t dx_consumed, int32_t dy_consumed, int32_t dx_unconsumed,
    int32_t dy_unconsumed, int32_t *offset_in_window) {
  void *result_label = nullptr;
  auto result_ptr = (jboolean *) alloca(sizeof(jboolean));
  MainLooper::GetInstance()->Call([handler, dx_consumed, dy_consumed, dx_unconsumed, dy_unconsumed, offset_in_window, &result_ptr, &result_label]() {
    auto cache = JniRefCache::GetInstance();
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

FFI_PLUGIN_EXPORT uint8_t dispatch_nested_pre_scroll_1(intptr_t handler,
                                                       int32_t dx,
                                                       int32_t dy,
                                                       int32_t *consumed,
                                                       int32_t *offset_in_window) {
  void *result_label = nullptr;
  auto result_ptr = (jboolean *) alloca(sizeof(jboolean));
  MainLooper::GetInstance()->Call([handler, dx, dy, &consumed, &offset_in_window, &result_ptr, &result_label]() {
    auto cache = JniRefCache::GetInstance();
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
    env->ReleaseIntArrayElements(j_consumed, consumed, JNI_ABORT);
    env->ReleaseIntArrayElements(j_offset_in_window, offset_in_window, JNI_ABORT);
    result_label = result_ptr;
  });
  BLOCK_WAIT(result_label)
  return *result_ptr;
}

FFI_PLUGIN_EXPORT uint8_t dispatch_nested_fling_1(intptr_t handler,
                                                  float velocity_x,
                                                  float velocity_y,
                                                  uint8_t consumed) {
  void *result_label = nullptr;
  auto result_ptr = (jboolean *) alloca(sizeof(jboolean));
  MainLooper::GetInstance()->Call([handler, velocity_x, velocity_y, consumed, &result_ptr, &result_label]() {
    auto cache = JniRefCache::GetInstance();
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

FFI_PLUGIN_EXPORT uint8_t dispatch_nested_pre_fling_1(intptr_t handler,
                                                      float velocity_x,
                                                      float velocity_y) {
  void *result_label = nullptr;
  auto result_ptr = (jboolean *) alloca(sizeof(jboolean));
  MainLooper::GetInstance()->Call([handler, velocity_x, velocity_y, &result_ptr, &result_label]() {
    auto cache = JniRefCache::GetInstance();
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

FFI_PLUGIN_EXPORT uint8_t start_nested_scroll_2(intptr_t handler, int32_t axes, int32_t type) {
  void *result_label = nullptr;
  auto result_ptr = (jboolean *) alloca(sizeof(jboolean));
  MainLooper::GetInstance()->Call([handler, axes, type, &result_ptr, &result_label]() {
    auto cache = JniRefCache::GetInstance();
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

FFI_PLUGIN_EXPORT void stop_nested_scroll_2(intptr_t handler, int32_t type) {
  MainLooper::GetInstance()->Call([handler, type]() {
    auto cache = JniRefCache::GetInstance();
    cache->env()->CallVoidMethod(to_jobject(handler),
                                 cache->stop_nested_scroll_2(),
                                 type);
  });
}

FFI_PLUGIN_EXPORT uint8_t dispatch_nested_scroll_2(
    intptr_t handler, int32_t dx_consumed, int32_t dy_consumed, int32_t dx_unconsumed,
    int32_t dy_unconsumed, int32_t *offset_in_window, int32_t type) {
  void *result_label = nullptr;
  auto result_ptr = (jboolean *) alloca(sizeof(jboolean));
  MainLooper::GetInstance()->Call([handler, dx_consumed, dy_consumed, dx_unconsumed, dy_unconsumed, offset_in_window, type, &result_ptr, &result_label]() {
    auto cache = JniRefCache::GetInstance();
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

FFI_PLUGIN_EXPORT uint8_t dispatch_nested_pre_scroll_2(intptr_t handler,
                                                       int32_t dx,
                                                       int32_t dy,
                                                       int32_t *consumed,
                                                       int32_t *offset_in_window,
                                                       int32_t type) {
  void *result_label = nullptr;
  auto result_ptr = (jboolean *) alloca(sizeof(jboolean));
  MainLooper::GetInstance()->Call([handler, dx, dy, &consumed, &offset_in_window, type, &result_ptr, &result_label]() {
    auto cache = JniRefCache::GetInstance();
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
    env->ReleaseIntArrayElements(j_consumed, consumed, JNI_ABORT);
    env->ReleaseIntArrayElements(j_offset_in_window, offset_in_window, JNI_ABORT);
    result_label = result_ptr;
  });
  BLOCK_WAIT(result_label)
  return *result_ptr;
}

FFI_PLUGIN_EXPORT uint8_t dispatch_nested_scroll_3(
    intptr_t handler, int32_t dx_consumed, int32_t dy_consumed, int32_t dx_unconsumed,
    int32_t dy_unconsumed, int32_t *offset_in_window, int32_t type, int32_t *consumed) {
  void *result_label = nullptr;
  auto result_ptr = (jboolean *) alloca(sizeof(jboolean));
  MainLooper::GetInstance()->Call([handler, dx_consumed, dy_consumed, dx_unconsumed, dy_unconsumed, offset_in_window, type, &consumed, &result_ptr, &result_label]() {
    auto cache = JniRefCache::GetInstance();
    auto env = cache->env();
    jintArray j_offset_in_window = env->NewIntArray(2);
    jintArray j_consumed = env->NewIntArray(2);
    *result_ptr = env->CallBooleanMethod(to_jobject(handler),
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
    result_label = result_ptr;
  });
  BLOCK_WAIT(result_label)
  return *result_ptr;
}

FFI_PLUGIN_EXPORT int test_result_array(intptr_t handler, int32_t *array) {
  void *result_label = nullptr;
  int *result_ptr = (int *) alloca(sizeof(int));
  MainLooper::GetInstance()->Call([handler, &array, &result_ptr, &result_label]() {
    auto cache = JniRefCache::GetInstance();
    auto env = cache->env();
    jintArray j_array = env->NewIntArray(2);
    *result_ptr = env->CallIntMethod(to_jobject(handler), cache->test_result_array(), j_array);
    auto array_buffer = env->GetIntArrayElements(j_array, JNI_FALSE);
    memcpy(array, array_buffer, 2 * sizeof(int32_t));
    env->ReleaseIntArrayElements(j_array, array_buffer, JNI_ABORT);
    result_label = result_ptr;
  });
  BLOCK_WAIT(result_label)
  return *result_ptr;
}

JNIEXPORT jlong JNICALL
Java_com_worktile_flutter_NestedFlutterView_flutterViewHandler(JNIEnv *env, jobject thiz) {
  return (jlong) env->NewWeakGlobalRef(thiz);
}

JNIEXPORT void JNICALL
Java_com_worktile_flutter_NestedFlutterView_deleteFlutterViewHandler(JNIEnv *env,
                                                                     jobject thiz,
                                                                     jlong handler) {
  auto shell_id = static_cast<intptr_t>(handler);
  auto pair = kCachedDeleteNestedFlutterViewHandlerFunctions.find(shell_id);
  if (pair != kCachedDeleteNestedFlutterViewHandlerFunctions.end()) {
    pair->second();
  }
  kCachedDeleteNestedFlutterViewHandlerFunctions.erase(shell_id);
}
}