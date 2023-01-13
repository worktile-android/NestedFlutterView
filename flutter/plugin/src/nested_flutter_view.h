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

FFI_PLUGIN_EXPORT uint8_t start_nested_scroll_1(intptr_t handler, int32_t axes);

FFI_PLUGIN_EXPORT void stop_nested_scroll_1(intptr_t handler);

FFI_PLUGIN_EXPORT uint8_t dispatch_nested_scroll_1(intptr_t handler,
                                                   int32_t dx_consumed,
                                                   int32_t dy_consumed,
                                                   int32_t dx_unconsumed,
                                                   int32_t dy_unconsumed,
                                                   int32_t *offset_in_window);

FFI_PLUGIN_EXPORT uint8_t dispatch_nested_pre_scroll_1(intptr_t handler,
                                                       int32_t dx,
                                                       int32_t dy,
                                                       int32_t *consumed,
                                                       int32_t *offset_in_window);

FFI_PLUGIN_EXPORT uint8_t dispatch_nested_fling_1(intptr_t handler,
                                                  float velocity_x,
                                                  float velocity_y,
                                                  uint8_t consumed);

FFI_PLUGIN_EXPORT uint8_t dispatch_nested_pre_fling_1(intptr_t handler,
                                                      float velocity_x,
                                                      float velocity_y);

FFI_PLUGIN_EXPORT uint8_t start_nested_scroll_2(intptr_t handler, int32_t axes, int32_t type);

FFI_PLUGIN_EXPORT void stop_nested_scroll_2(intptr_t handler, int32_t type);

FFI_PLUGIN_EXPORT uint8_t dispatch_nested_scroll_2(intptr_t handler,
                                                   int32_t dx_consumed,
                                                   int32_t dy_consumed,
                                                   int32_t dx_unconsumed,
                                                   int32_t dy_unconsumed,
                                                   int32_t *offset_in_window,
                                                   int32_t type);

FFI_PLUGIN_EXPORT uint8_t dispatch_nested_pre_scroll_2(intptr_t handler,
                                                       int32_t dx,
                                                       int32_t dy,
                                                       int32_t *consumed,
                                                       int32_t *offset_in_window,
                                                       int32_t type);

FFI_PLUGIN_EXPORT void dispatch_nested_scroll_3(intptr_t handler,
                                                int32_t dx_consumed,
                                                int32_t dy_consumed,
                                                int32_t dx_unconsumed,
                                                int32_t dy_unconsumed,
                                                int32_t *offset_in_window,
                                                int32_t type,
                                                int32_t *consumed);

FFI_PLUGIN_EXPORT void request_parent_disallow_intercept_touch_event(intptr_t handler, uint8_t disallowIntercept);

FFI_PLUGIN_EXPORT float get_y_velocity(intptr_t handler);

#ifdef __cplusplus
}
#endif