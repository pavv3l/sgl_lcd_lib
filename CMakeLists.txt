# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

if(${BUILD_UT})
message(INFO "BUILD UT FOR LINUX")
add_subdirectory(external/googletest-release-1.12.1)
else()
message(INFO "BUILD UT FOR ARM")
include(pico_sdk_import.cmake)
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(APP_NAME lcd_lib)

project(${APP_NAME} C CXX ASM)

add_subdirectory(sgl)

