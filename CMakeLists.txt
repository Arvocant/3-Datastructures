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
        "test/TestSparseMatrix.cpp"
        "include/3_Datastructures/SparseMatrix.h"
        test/main.cpp
        # Include the header files
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
