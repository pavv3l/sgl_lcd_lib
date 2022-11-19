set(LIB_NAME sgl_lib)

project(${LIB_NAME})

aux_source_directory(src SRC_FILES)

add_library(${LIB_NAME} STATIC ${SRC_FILES})
target_compile_options(${LIB_NAME} PRIVATE -Wall -Wextra)

target_include_directories(${LIB_NAME} PUBLIC inc)

if(${BUILD_UT})
add_subdirectory(ut)
endif()