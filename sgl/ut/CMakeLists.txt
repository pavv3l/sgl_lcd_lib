set(UT_NAME sgl_ut)


enable_testing()

project(${UT_NAME})

aux_source_directory(src SRC_FILES_UT)

message(INFO " PLIKI UT: ${SRC_FILES_UT}")

add_executable(${UT_NAME} ${SRC_FILES_UT})

target_link_libraries(${UT_NAME} PRIVATE gtest gmock gtest_main sgl_lib)

target_include_directories(${LIB_NAME} PUBLIC inc)