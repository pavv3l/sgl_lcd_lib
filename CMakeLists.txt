# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(APP_NAME lcd_lib)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if(${BUILD_UT})
message(INFO " BUILD UT FOR LINUX")
add_subdirectory(external/googletest-release-1.12.1)

else()

message(INFO " BUILD ${APP_NAME} FOR ARM")
set(PICO_SDK_PATH "/home/nte/pico/pico-sdk")
set(PICO_BOARD pico CACHE STRING "Board type")
include(pico_sdk_import.cmake)
endif()

project(${APP_NAME} C CXX ASM)

if(${BUILD_UT})
add_subdirectory(sgl)
else()
pico_sdk_init()

add_subdirectory(sgl)
add_subdirectory(drivers)
endif()