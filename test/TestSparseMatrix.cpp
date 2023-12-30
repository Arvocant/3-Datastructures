//
// Created by canta on 22/11/2023.
//
#include <catch2/catch.h>
#include "3_Datastructures/SparseMatrix.h"
#include <string>
#include <vector>
#include <iostream>

TEST_CASE("SparseMatrix Constructor Test", "[SparseMatrix][Constructor]") {

    SECTION("Constructor n x n matrix, square") {
        SparseMatrix::SparseMatrix<int> matrix(3); //Try different sorts of size_t's for a square

        REQUIRE(matrix.getRowCount() == 3);
        REQUIRE(matrix.getColumnCount() == 3);

    }

    SECTION("Constructor m x n matrix, rectangle") {
        SparseMatrix::SparseMatrix<int> matrix(2, 4); //Try a rectangular sparse matrix

        REQUIRE(matrix.getRowCount() == 2);
        REQUIRE(matrix.getColumnCount() == 4);
    }
}

TEST_CASE("SparseMatrix Empty elements test", "[SparseMatrix]") {
    SparseMatrix::SparseMatrix<int> matrix(3, 4);
    // Attempting to get an element from an uninitialized matrix should return 0
    REQUIRE(matrix.get(2, 2) == 0);
}

TEST_CASE("Set a value in the SparseMatrix", "[SparseMatrix]") {
    SparseMatrix::SparseMatrix<int> matrix(2, 3);
    matrix.set(5, 1, 2);

    matrix.print();

    CHECK(matrix.get(1, 2) == 5);
}

TEST_CASE("SparseMatrix Multiply 3x3 Matrices", "[SparseMatrix][Multiply]") {
    SparseMatrix::SparseMatrix<int> matrixA(3, 3);
    SparseMatrix::SparseMatrix<int> matrixB(3, 3);

    std::cout << " Start of multiplication of 2 [3x3] matrices" << std::endl;

    // Set values for matrixA
    matrixA.set(1, 1, 1);
    matrixA.set(2, 1, 2);
    matrixA.set(3, 1, 3);
    matrixA.set(4, 2, 1);
    matrixA.set(5, 2, 2);
    matrixA.set(6, 2, 3);
    matrixA.set(7, 3, 1);
    matrixA.set(8, 3, 2);
    matrixA.set(9, 3, 3);

    matrixA.print();

    // Set values for matrixB
    matrixB.set(9, 1, 1);
    matrixB.set(8, 1, 2);
    matrixB.set(7, 1, 3);
    matrixB.set(6, 2, 1);
    matrixB.set(5, 2, 2);
    matrixB.set(4, 2, 3);
    matrixB.set(3, 3, 1);
    matrixB.set(2, 3, 2);
    matrixB.set(1, 3, 3);

    matrixB.print();

    SparseMatrix::SparseMatrix<int> result = matrixA.multiply(matrixB);

    std::cout << " Result: " << std::endl;

    result.print();

    std::cout << " End of multiplication test" << std::endl;

    // Check the result matrix dimensions
    REQUIRE(result.getRowCount() == 3);
    REQUIRE(result.getColumnCount() == 3);

    // Check specific elements in the result matrix

    // (1, 1): 1*9 + 2*6 + 3*3 = 30
    REQUIRE(result.get(1, 1) == 30);

    // (1, 2): 1*8 + 2*5 + 3*2 = 24
    REQUIRE(result.get(1, 2) == 24);

    // (1, 3): 1*7 + 2*4 + 3*1 = 18
    REQUIRE(result.get(1, 3) == 18);

    // (2, 1): 4*9 + 5*6 + 6*3 = 84
    REQUIRE(result.get(2, 1) == 84);

    // (2, 2): 4*8 + 5*5 + 6*2 = 69
    REQUIRE(result.get(2, 2) == 69);

    // (2, 3): 4*7 + 5*4 + 6*1 = 54
    REQUIRE(result.get(2, 3) == 54);

    // (3, 1): 7*9 + 8*6 + 9*3 = 138
    REQUIRE(result.get(3, 1) == 138);

    // (3, 2): 7*8 + 8*5 + 9*2 = 114
    REQUIRE(result.get(3, 2) == 114);

    // (3, 3): 7*7 + 8*4 + 9*1 = 90
    REQUIRE(result.get(3, 3) == 90);
}

TEST_CASE("SparseMatrix Add 2x3 Matrices", "[SparseMatrix][Add]") {
    SparseMatrix::SparseMatrix<int> matrixA(2, 3);
    SparseMatrix::SparseMatrix<int> matrixB(2, 3);

    std::cout << " Start of addition 2x3 matrix with 3x2 matrix " << std::endl;

    // Set values for matrixA
    matrixA.set(1, 1, 1);
    matrixA.set(2, 1, 2);
    matrixA.set(3, 1, 3);
    matrixA.set(4, 2, 1);
    matrixA.set(5, 2, 2);
    matrixA.set(6, 2, 3);

    matrixA.print();

    // Set values for matrixB
    matrixB.set(14, 1, 1);
    matrixB.set(20, 1, 2);
    matrixB.set(33, 1, 3);
    matrixB.set(0, 2, 1);
    matrixB.set(67, 2, 2);
    matrixB.set(101, 2, 3);

    matrixB.print();

    SparseMatrix::SparseMatrix<int> result = matrixA.add(matrixB);

    std::cout << " Result: " << std::endl;

    result.print();

    std::cout << " End of addition test" << std::endl;

    // Check the result matrix dimensions
    REQUIRE(result.getRowCount() == 2);
    REQUIRE(result.getColumnCount() == 3);

    // Check specific elements in the result matrix

    // (1, 1): 1 + 14 = 15
    REQUIRE(result.get(1, 1) == 15);

    // (1, 2): 2 + 20 = 22
    REQUIRE(result.get(1, 2) == 22);

    // (1, 3): 3 + 33 = 36
    REQUIRE(result.get(1, 3) == 36);

    // (2, 1): 4 + 0 = 4
    REQUIRE(result.get(2, 1) == 4);

    // (2, 2): 5 + 67 = 72
    REQUIRE(result.get(2, 2) == 72);

    // (2, 3): 6 + 101 = 107
    REQUIRE(result.get(2, 3) == 107);
}



