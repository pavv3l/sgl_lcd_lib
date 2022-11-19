# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(APP_NAME lcd_lib)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/home/nte/pico/pico-sdk")

set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(${APP_NAME} C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(${APP_NAME} sgl_lcd_lib.c )

pico_set_program_name(${APP_NAME} "lcd_lib")
pico_set_program_version(${APP_NAME} "0.1")

pico_enable_stdio_uart(${APP_NAME} 1)
pico_enable_stdio_usb(${APP_NAME} 1)

target_link_libraries(${APP_NAME}
  pico_stdlib)

#target_link_libraries(${APP_NAME}
#  sgl_lib)

  #add_subdirectory(sgl)


# Add the standard include files to the build
target_include_directories(${APP_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

target_link_libraries(${APP_NAME}
        hardware_spi
        )

pico_add_extra_outputs(${APP_NAME})

add_subdirectory(sgl)

