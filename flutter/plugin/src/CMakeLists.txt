# The Flutter tooling requires that developers have CMake 3.10 or later
# installed. You should not increase this version, as doing so will cause
# the plugin to fail to compile for some customers of the plugin.
cmake_minimum_required(VERSION 3.10)

project(plugin_library VERSION 0.0.1)

message(STATUS "${CMAKE_SYSTEM_NAME}")

add_library(plugin SHARED
  "nested_flutter_view.cpp"
)

set_target_properties(plugin PROPERTIES
  PUBLIC_HEADER nested_flutter_view.h
  OUTPUT_NAME "plugin"
)

target_compile_definitions(plugin PUBLIC DART_SHARED_LIB)
