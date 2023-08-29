set(LIB_NAME sgl_lib)

project(${LIB_NAME})

aux_source_directory(src SRC_FILES)

message(INFO "${LIB_NAME} files: ${SRC_FILES}")

add_library(${LIB_NAME} STATIC ${SRC_FILES})
target_compile_options(${LIB_NAME} PRIVATE -Wall -Wextra)

target_include_directories(${LIB_NAME} PUBLIC inc)
target_include_directories(${LIB_NAME} PUBLIC font/inc2)
target_link_libraries(${LIB_NAME} PUBLIC sgl_hal_lib)

#target_include_directories(${LIB_NAME} PUBLIC
#  ${CMAKE_CURRENT_LIST_DIR}
#  ${CMAKE_CURRENT_LIST_DIR})

if(${BUILD_UT})
add_subdirectory(ut)
endif()
