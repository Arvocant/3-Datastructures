//
// Created by canta on 22/11/2023.
//
#include <catch2/catch.h>
#include "3_Datastructures/sparseMatrix.h"
#include <string>
#include <vector>
#include <iostream>

TEST_CASE("ProjectSparseMatrix Constructor Test", "[ProjectSparseMatrix][Constructor]") {

    SECTION("Constructor n x n matrix, square") {
        ProjectSparseMatrix::sparseMatrix<int> matrix(3); //Try different sorts of size_t's for a square

        REQUIRE(matrix.rowCount() == 3);
        REQUIRE(matrix.columnCount() == 3);

    }

    SECTION("Constructor m x n matrix, rectangle") {
        ProjectSparseMatrix::sparseMatrix<int> matrix(2, 4); //Try a rectangular sparse matrix

        REQUIRE(matrix.rowCount() == 2);
        REQUIRE(matrix.columnCount() == 4);

        std::cout << "Construct an empty 2x4 matrix" << std::endl;

        matrix.print();

        std::cout << "\n" << std::string(80, '-') << "\n";
    }
}

TEST_CASE("ProjectSparseMatrix Empty elements test", "[ProjectSparseMatrix]") {
    ProjectSparseMatrix::sparseMatrix<int> matrix(3, 4);
    // Attempting to get an element from an uninitialized matrix should return 0
    REQUIRE(matrix.get(2, 2) == 0);
}

TEST_CASE("Set a value in the ProjectSparseMatrix", "[ProjectSparseMatrix]") {
    ProjectSparseMatrix::sparseMatrix<int> matrix(2, 3);

    std::cout << " Set a value to an empty matrix" << std::endl;

    matrix.print();

    std::cout << " Now we add a value " << std::endl;

    matrix.set(5, 1, 2);

    matrix.print();

    CHECK(matrix.get(1, 2) == 5);
    std::cout << "\n" << std::string(80, '-') << "\n";
}

TEST_CASE("ProjectSparseMatrix Multiply 3x3 Matrices", "[ProjectSparseMatrix][Multiply]") {
    ProjectSparseMatrix::sparseMatrix<int> matrixA(3, 3);
    ProjectSparseMatrix::sparseMatrix<int> matrixB(3, 3);

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

    ProjectSparseMatrix::sparseMatrix<int> result = matrixA.multiply(matrixB);

    std::cout << " Result: " << std::endl;

    result.print();

    std::cout << " End of multiplication test" << std::endl;

    // Check the result matrix dimensions
    REQUIRE(result.rowCount() == 3);
    REQUIRE(result.columnCount() == 3);

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
    std::cout << "\n" << std::string(80, '-') << "\n";
}

TEST_CASE("ProjectSparseMatrix Add 2x3 Matrices", "[ProjectSparseMatrix][Add]") {
    ProjectSparseMatrix::sparseMatrix<int> matrixA(2, 3);
    ProjectSparseMatrix::sparseMatrix<int> matrixB(2, 3);

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

    ProjectSparseMatrix::sparseMatrix<int> result = matrixA.add(matrixB);

    std::cout << " Result: " << std::endl;

    result.print();

    std::cout << " End of addition test" << std::endl;

    // Check the result matrix dimensions
    REQUIRE(result.rowCount() == 2);
    REQUIRE(result.columnCount() == 3);

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
    std::cout << "\n" << std::string(80, '-') << "\n";
}

// Test case for ProjectSparseMatrix subtraction with a 2x7 rectangular matrix
TEST_CASE("ProjectSparseMatrix Subtract Rectangular Matrices", "[ProjectSparseMatrix][Subtract]") {
    // Create two SparseMatrices of the same size
    ProjectSparseMatrix::sparseMatrix<int> matrixA(2, 7);
    ProjectSparseMatrix::sparseMatrix<int> matrixB(2, 7);

    std::cout << " Start of subtraction 2x7 matrix " << std::endl;

    // Set values for matrixA
    matrixA.set(1, 1, 1);
    matrixA.set(2, 1, 2);
    matrixA.set(3, 1, 3);
    matrixA.set(4, 1, 4);
    matrixA.set(5, 1, 5);
    matrixA.set(6, 1, 6);
    matrixA.set(7, 1, 7);
    matrixA.set(8, 2, 1);
    matrixA.set(9, 2, 2);
    matrixA.set(10, 2, 3);
    matrixA.set(11, 2, 4);
    matrixA.set(12, 2, 5);
    matrixA.set(13, 2, 6);
    matrixA.set(14, 2, 7);

    matrixA.print();

    // Set values for matrixB
    matrixB.set(14, 1, 1);
    matrixB.set(13, 1, 2);
    matrixB.set(12, 1, 3);
    matrixB.set(11, 1, 4);
    matrixB.set(10, 1, 5);
    matrixB.set(9, 1, 6);
    matrixB.set(8, 1, 7);
    matrixB.set(7, 2, 1);
    matrixB.set(6, 2, 2);
    matrixB.set(5, 2, 3);
    matrixB.set(4, 2, 4);
    matrixB.set(3, 2, 5);
    matrixB.set(2, 2, 6);
    matrixB.set(1, 2, 7);

    matrixB.print();

    // Perform subtraction
    ProjectSparseMatrix::sparseMatrix<int> result = matrixA.subtract(matrixB);

    std::cout << " Result: " << std::endl;

    result.print();

    std::cout << " End of subtraction test" << std::endl;

    // Check the result matrix dimensions
    REQUIRE(result.rowCount() == 2);
    REQUIRE(result.columnCount() == 7);

    // Check specific elements in the result matrix
    REQUIRE(result.get(1, 1) == -13);
    REQUIRE(result.get(1, 2) == -11);
    REQUIRE(result.get(1, 3) == -9);
    REQUIRE(result.get(1, 4) == -7);
    REQUIRE(result.get(1, 5) == -5);
    REQUIRE(result.get(1, 6) == -3);
    REQUIRE(result.get(1, 7) == -1);
    REQUIRE(result.get(2, 1) == 1);
    REQUIRE(result.get(2, 2) == 3);
    REQUIRE(result.get(2, 3) == 5);
    REQUIRE(result.get(2, 4) == 7);
    REQUIRE(result.get(2, 5) == 9);
    REQUIRE(result.get(2, 6) == 11);
    REQUIRE(result.get(2, 7) == 13);
    std::cout << "\n" << std::string(80, '-') << "\n";
}

TEST_CASE("ProjectSparseMatrix Addition with Blank Spaces", "[ProjectSparseMatrix][Addition]") {
    std::cout << "Test Case: ProjectSparseMatrix Addition with Blank Spaces\n";

    ProjectSparseMatrix::sparseMatrix<int> matrixA(3, 3);
    ProjectSparseMatrix::sparseMatrix<int> matrixB(3, 3);

    // Set values for matrixA
    matrixA.set(1, 1, 1);
    matrixA.set(2, 1, 2);
    matrixA.set(3, 1, 3);
    matrixA.set(4, 2, 1);
    // Leave matrixA[2][2] blank
    matrixA.set(6, 2, 3);
    matrixA.set(7, 3, 1);
    matrixA.set(8, 3, 2);
    matrixA.set(9, 3, 3);

    std::cout << "Matrix A:\n";
    matrixA.print();

    // Set values for matrixB
    matrixB.set(9, 1, 1);
    matrixB.set(8, 1, 2);
    matrixB.set(7, 1, 3);
    matrixB.set(6, 2, 1);
    matrixB.set(5, 2, 2);
    matrixB.set(4, 2, 3);
    matrixB.set(3, 3, 1);
    // Leave matrixB[3][2] and matrixB[3][3] blank
    //matrixB.set(1, 3, 3);

    std::cout << "Matrix B:\n";
    matrixB.print();

    ProjectSparseMatrix::sparseMatrix<int> result = matrixA.add(matrixB);

    std::cout << "Result Matrix:\n";
    result.print();

    // Check the result matrix dimensions
    REQUIRE(result.rowCount() == 3);
    REQUIRE(result.columnCount() == 3);

    // Check specific elements in the result matrix
    REQUIRE(result.get(1, 1) == 10);
    REQUIRE(result.get(1, 2) == 10);
    REQUIRE(result.get(1, 3) == 10);
    REQUIRE(result.get(2, 1) == 10);
    // Check if the blank space in matrixA was handled correctly
    REQUIRE(result.get(2, 2) == 5);
    REQUIRE(result.get(2, 3) == 10);
    REQUIRE(result.get(3, 1) == 10);
    // Check if the blank spaces in matrixB were handled correctly
    REQUIRE(result.get(3, 2) == 8);
    REQUIRE(result.get(3, 3) == 9);

    std::cout << "Test Case Completed.\n";
    std::cout << "\n" << std::string(120, '-') << "\n";
}

TEST_CASE("ProjectSparseMatrix Create Big Sparse Matrix", "[ProjectSparseMatrix][Create]") {
    std::cout << "Creating a big sparse matrix with 6 random values:\n";

    ProjectSparseMatrix::sparseMatrix<int> bigSparseMatrix(8, 8);

    // Set values at random positions
    bigSparseMatrix.set(1, 2, 3);
    bigSparseMatrix.set(2, 4, 6);
    bigSparseMatrix.set(3, 1, 8);
    bigSparseMatrix.set(4, 7, 2);
    bigSparseMatrix.set(5, 5, 5);
    bigSparseMatrix.set(6, 8, 1);

    // Print the big sparse matrix
    bigSparseMatrix.print();

    // Check the values
    REQUIRE(bigSparseMatrix.get(2, 3) == 1);
    REQUIRE(bigSparseMatrix.get(4, 6) == 2);
    REQUIRE(bigSparseMatrix.get(1, 8) == 3);
    REQUIRE(bigSparseMatrix.get(7, 2) == 4);
    REQUIRE(bigSparseMatrix.get(5, 5) == 5);
    REQUIRE(bigSparseMatrix.get(8, 1) == 6);

    std::cout << "\n" << std::string(120, '-') << "\n";
}

TEST_CASE("ProjectSparseMatrix Complex Operations", "[ProjectSparseMatrix][Complex]") {
    std::cout << "Initializing a 10x10 matrix:\n";
    ProjectSparseMatrix::sparseMatrix<int> complexMatrix(10, 10);
    complexMatrix.print();

    std::cout << "\nAdding values to random positions:\n";
    complexMatrix.set(42, 3, 5);
    complexMatrix.set(23, 7, 2);
    complexMatrix.set(15, 9, 8);
    complexMatrix.print();

    std::cout << "\nAdding 5 to some existing values:\n";
    complexMatrix.set(complexMatrix.get(3, 5) + 5, 3, 5);
    complexMatrix.set(complexMatrix.get(7, 2) + 5, 7, 2);
    complexMatrix.set(complexMatrix.get(9, 8) + 5, 9, 8);
    complexMatrix.print();

    std::cout << "\nSubtracting 8 from values at (3, 5) and (9, 8):\n";
    complexMatrix.set(complexMatrix.get(3, 5) - 8, 3, 5);
    complexMatrix.set(complexMatrix.get(9, 8) - 8, 9, 8);
    complexMatrix.print();

    std::cout << "\nAdding more random values to different positions:\n";
    complexMatrix.set(30, 2, 6);
    complexMatrix.set(18, 5, 3);
    complexMatrix.set(25, 8, 7);
    complexMatrix.print();

    std::cout << "\n" << std::string(120, '-') << "\n";
}
