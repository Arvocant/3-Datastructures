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
    CHECK(matrix.get(1, 2) == 5);
}

TEST_CASE("Multiply two SparseMatrixs", "[SparseMatrix]") {
    SparseMatrix::SparseMatrix<int> m1(2, 3);
    m1.set(1, 1, 1);
    m1.set(1, 2, 2);
    m1.set(2, 1, 3);
    m1.set(2, 2, 4);

    SparseMatrix::SparseMatrix<int> m2(3, 2);
    m2.set(1, 1, 4);
    m2.set(1, 2, 5);
    m2.set(2, 1, 6);
    m2.set(2, 2, 7);

    SparseMatrix::SparseMatrix<int> result = m1.multiply(m2);

    CHECK(result.get(1, 1) == 22);
    CHECK(result.get(1, 2) == 28);
    CHECK(result.get(2, 1) == 47);
    CHECK(result.get(2, 2) == 62);
}