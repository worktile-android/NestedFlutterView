//
// Created by 马星海 on 2023/1/5.
//

#ifndef NESTEDFLUTTERVIEW_FLUTTER_PLUGIN_SRC_MACROS_H_
#define NESTEDFLUTTERVIEW_FLUTTER_PLUGIN_SRC_MACROS_H_

#include "android/log.h"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "Native", __VA_ARGS__)

#define to_jobject(handler) reinterpret_cast<jobject>(handler)

#endif //NESTEDFLUTTERVIEW_FLUTTER_PLUGIN_SRC_MACROS_H_
