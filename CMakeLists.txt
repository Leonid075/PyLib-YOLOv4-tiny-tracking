cmake_minimum_required(VERSION 2.8)
project(pydarknet)

include_directories(/content/cpython/Include)
include_directories(/content/PyLib-YOLOv4-tiny-tracking/include)

set(SOURCE_LIB lib.cpp /content/cpython/Include/ /content/PyLib-YOLOv4-tiny-tracking/include/)

add_library(libpython3.8 SHARED IMPORTED)
set_property(TARGET libpython3.8 PROPERTY
             IMPORTED_LOCATION /usr/lib/x86_64-linux-gnu/libpython3.8.so)

add_library(libdarknet SHARED IMPORTED)
set_property(TARGET libdarknet PROPERTY
              IMPORTED_LOCATION /content/drive/MyDrive/libdarknet.so)

add_library(pylib SHARED ${SOURCE_LIB})

target_link_libraries(pylib libpython3.8 libdarknet)
