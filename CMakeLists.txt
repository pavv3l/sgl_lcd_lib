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

add_executable(${APP_NAME} sgl_lcd_lib.cpp)

pico_set_program_name(lcd_lib "lcd_lib")
pico_set_program_version(lcd_lib "0.1")

pico_enable_stdio_uart(${APP_NAME} 0)
pico_enable_stdio_usb(${APP_NAME} 1)

target_link_libraries(${APP_NAME} PUBLIC
        pico_stdlib
        sgl_lib_st7789vw
        hardware_spi
        pico_multicore)

pico_add_extra_outputs(lcd_lib)

endif()