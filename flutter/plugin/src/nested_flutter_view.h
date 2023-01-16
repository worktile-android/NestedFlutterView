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

FFI_PLUGIN_EXPORT intptr_t initDartApiDL(void* data);

FFI_PLUGIN_EXPORT void registerSendPort(int64_t port);

FFI_PLUGIN_EXPORT void delegateInvoke(intptr_t invoke_ptr);

FFI_PLUGIN_EXPORT void cacheMaxScrollExtent(int(*function)(int));

FFI_PLUGIN_EXPORT void cacheMinScrollExtent(int(*function)(int));

FFI_PLUGIN_EXPORT void cacheViewportDimensions(int(*function)(int));

FFI_PLUGIN_EXPORT void cachePixels(int(*function)(int));

FFI_PLUGIN_EXPORT uint8_t startNestedScroll_1(intptr_t handler, int32_t axes);

FFI_PLUGIN_EXPORT void stopNestedScroll_1(intptr_t handler);

FFI_PLUGIN_EXPORT uint8_t dispatchNestedScroll_1(intptr_t handler,
                                                 int32_t dx_consumed,
                                                 int32_t dy_consumed,
                                                 int32_t dx_unconsumed,
                                                 int32_t dy_unconsumed,
                                                 int32_t *offset_in_window);

FFI_PLUGIN_EXPORT uint8_t dispatchNestedPreScroll_1(intptr_t handler,
                                                    int32_t dx,
                                                    int32_t dy,
                                                    int32_t *consumed,
                                                    int32_t *offset_in_window);

FFI_PLUGIN_EXPORT uint8_t dispatchNestedFling_1(intptr_t handler,
                                                float velocity_x,
                                                float velocity_y,
                                                uint8_t consumed);

FFI_PLUGIN_EXPORT uint8_t dispatchNestedPreFling_1(intptr_t handler,
                                                   float velocity_x,
                                                   float velocity_y);

FFI_PLUGIN_EXPORT uint8_t startNestedScroll_2(intptr_t handler, int32_t axes, int32_t type);

FFI_PLUGIN_EXPORT void stopNestedScroll_2(intptr_t handler, int32_t type);

FFI_PLUGIN_EXPORT uint8_t dispatchNestedScroll_2(intptr_t handler,
                                                 int32_t dx_consumed,
                                                 int32_t dy_consumed,
                                                 int32_t dx_unconsumed,
                                                 int32_t dy_unconsumed,
                                                 int32_t *offset_in_window,
                                                 int32_t type);

FFI_PLUGIN_EXPORT uint8_t dispatchNestedPreScroll_2(intptr_t handler,
                                                    int32_t dx,
                                                    int32_t dy,
                                                    int32_t *consumed,
                                                    int32_t *offset_in_window,
                                                    int32_t type);

FFI_PLUGIN_EXPORT void dispatchNestedScroll_3(intptr_t handler,
                                              int32_t dx_consumed,
                                              int32_t dy_consumed,
                                              int32_t dx_unconsumed,
                                              int32_t dy_unconsumed,
                                              int32_t *offset_in_window,
                                              int32_t type,
                                              int32_t *consumed);

FFI_PLUGIN_EXPORT void requestParentDisallowInterceptTouchEvent(intptr_t handler, uint8_t disallowIntercept);

FFI_PLUGIN_EXPORT float getYVelocity(intptr_t handler);

FFI_PLUGIN_EXPORT void setHorizontalMaxExtent(intptr_t handler, int extent);

FFI_PLUGIN_EXPORT void setHorizontalMinExtent(intptr_t handler, int extent);

FFI_PLUGIN_EXPORT void setHorizontalViewportDimension(intptr_t handler, int viewport_dimension);

FFI_PLUGIN_EXPORT void setHorizontalOffset(intptr_t handler, int offset);

FFI_PLUGIN_EXPORT void setVerticalMaxExtent(intptr_t handler, int extent);

FFI_PLUGIN_EXPORT void setVerticalMinExtent(intptr_t handler, int extent);

FFI_PLUGIN_EXPORT void setVerticalViewportDimension(intptr_t handler, int viewport_dimension);

FFI_PLUGIN_EXPORT void setVerticalOffset(intptr_t handler, int offset);

#ifdef __cplusplus
}
#endif