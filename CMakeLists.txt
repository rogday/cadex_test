cmake_minimum_required (VERSION 3.10)

project (test_task)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 17)
add_definitions(-D_USE_MATH_DEFINES)

add_subdirectory(libcurve)
find_package(TBB REQUIRED)

set(TARGET_SOURCES src/main.cpp)
add_executable(test_task ${TARGET_SOURCES})

target_link_libraries(test_task PUBLIC curve)

if (${TBB_FOUND})
    add_definitions(-DTBB_FOUND)
    target_link_libraries(test_task PUBLIC ${TBB_IMPORTED_TARGETS})
endif()
