cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${CMAKE_SOURCE_DIR}/cmake/modules"
)

find_package(LibClangTooling REQUIRED)

add_definitions(${LibClangTooling_DEFINITIONS})

include_directories(
  ${LibClangTooling_INCLUDE_DIRS}
)

add_executable(apitege main.cpp)
target_link_libraries(apitege ${LibClangTooling_LIBRARIES})
add_executable(testapitege test.cpp)
target_link_libraries(testapitege  gtest gtest_main pthread ${LibClangTooling_LIBRARIES})
