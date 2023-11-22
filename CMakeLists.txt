cmake_minimum_required(VERSION 3.26)
project(3_Datastructures)

set(CMAKE_CXX_STANDARD 23)

add_library(MatrixLib STATIC
        "include/3_Datastructures/SparseMatrix.h"
        "src/SparseMatrix.cpp"

)

target_include_directories(MatrixLib PRIVATE "include/")

# Add the executable
add_executable(TestSuite
        "test/SparseMatrix.cpp"
)

target_include_directories(TestSuite PRIVATE "include/")

target_link_libraries(TestSuite PRIVATE MatrixLib)

# Add compiler flags
add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Werror
)

# Alternatively, if you want to set flags for a specific configuration (e.g., Release or Debug)
# set(CMAKE_CXX_FLAGS_RELEASE " -flag3 -flag4" CACHE STRING "" FORCE)
# set(CMAKE_CXX_FLAGS_DEBUG "-flag5 -flag6" CACHE STRING " " FORCE)