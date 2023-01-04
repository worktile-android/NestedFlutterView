# The Flutter tooling requires that developers have CMake 3.10 or later
# installed. You should not increase this version, as doing so will cause
# the plugin to fail to compile for some customers of the plugin.
cmake_minimum_required(VERSION 3.10)

project(plugin_library VERSION 0.0.1)

set(DART_DIR ${FLUTTER_SDK}/bin/cache/dart-sdk/include)

add_library(
        nested_flutter_view
        SHARED
        nested_flutter_view.cc
        jni_lifecycle.cc
        jni_ref_cache.cc
        main_looper.cc
        ${DART_DIR}/dart_api_dl.c
)

target_include_directories(
        nested_flutter_view
        PUBLIC
        ${DART_DIR}
)

target_link_libraries(
        nested_flutter_view
        android
)

set_target_properties(nested_flutter_view PROPERTIES
  PUBLIC_HEADER nested_flutter_view.h
  OUTPUT_NAME "nested_flutter_view"
)

target_compile_definitions(nested_flutter_view PUBLIC DART_SHARED_LIB)
