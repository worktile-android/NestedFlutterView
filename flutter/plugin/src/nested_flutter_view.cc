#include <jni.h>
#include <unordered_map>
#include "nested_flutter_view.h"
#include "jni_ref_cache.h"
#include "main_looper.h"

using namespace std;

static unordered_map<intptr_t, void (*)()> kCachedDeleteNestedFlutterViewHandlerFunctions;

extern "C" {
FFI_PLUGIN_EXPORT void cache_delete_nested_flutter_view_handle_function(intptr_t shell_id,
                                                                        void (*function)()) {
  kCachedDeleteNestedFlutterViewHandlerFunctions.insert(make_pair(shell_id, function));
}

FFI_PLUGIN_EXPORT void test(int64_t handler) {
  MainLooper::GetInstance()->call([handler]() {
    auto cache = JniRefCache::GetInstance();
    cache->env()->CallVoidMethod(reinterpret_cast<jobject>(handler), cache->test());
  });
}

JNIEXPORT jlong JNICALL
Java_com_worktile_flutter_NestedFlutterView_flutterViewHandler(JNIEnv *env, jobject thiz) {
  return (jlong) env->NewWeakGlobalRef(thiz);
}

JNIEXPORT void JNICALL
Java_com_worktile_flutter_NestedFlutterView_deleteFlutterViewHandler(JNIEnv *env, jobject thiz,
                                                                     jlong handler) {
  auto shell_id = static_cast<intptr_t>(handler);
  auto pair = kCachedDeleteNestedFlutterViewHandlerFunctions.find(shell_id);
  if (pair != kCachedDeleteNestedFlutterViewHandlerFunctions.end()) {
    pair->second();
  }
  kCachedDeleteNestedFlutterViewHandlerFunctions.erase(shell_id);
}
}