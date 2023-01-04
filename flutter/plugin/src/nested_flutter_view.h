#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#if _WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <unistd.h>
#endif

#if _WIN32
#define FFI_PLUGIN_EXPORT __declspec(dllexport)
#else
#define FFI_PLUGIN_EXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif

FFI_PLUGIN_EXPORT void cache_delete_nested_flutter_view_handle_function(intptr_t shell_id,
                                                                        void (*function)());

FFI_PLUGIN_EXPORT void test(int64_t handler);

#ifdef __cplusplus
}
#endif