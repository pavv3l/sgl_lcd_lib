set(LIB_NAME sgl_hal_lib)

project(${LIB_NAME})

aux_source_directory(src SRC_FILES)

message(INFO "${LIB_NAME} files: ${SRC_FILES}")

#add_library(${LIB_NAME} STATIC ${SRC_FILES})
add_library(${LIB_NAME} INTERFACE)
#target_compile_options(${LIB_NAME} PRIVATE -Wall -Wextra)

target_include_directories(${LIB_NAME} INTERFACE inc)