set(LIB_NAME sgl_lib)

project(${LIB_NAME})

aux_source_directory(src SRC_FILES)

add_library(${LIB_NAME} STATIC ${SRC_FILES})

target_include_directories(${LIB_NAME} INTERFACE inc)