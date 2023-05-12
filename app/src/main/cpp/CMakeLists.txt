cmake_minimum_required(VERSION 3.4.1)

set(cl_stub_SRC "../cl_stub/")
set(cl_stub_build_DIR ${PROJECT_BINARY_DIR}/cl_stub_outputs)
file(MAKE_DIRECTORY ${cl_stub_build_DIR})
add_subdirectory(${cl_stub_SRC} ${cl_stub_build_DIR})
add_library(libcl_stub SHARED IMPORTED)

set_target_properties(libcl_stub PROPERTIES IMPORTED_LOCATION ${cl_stub_build_DIR}/${ANDROID_ABI}/libcl_stub.so)

add_library(OpenCLDemo SHARED
            OpenCLDemo.cpp
            openCLNR.cpp
            refNR.cpp)

target_include_directories(OpenCLDemo PRIVATE
                           ${cl_stub_SRC}/include)

target_link_libraries(OpenCLDemo
                      android
                      libcl_stub
                      log)