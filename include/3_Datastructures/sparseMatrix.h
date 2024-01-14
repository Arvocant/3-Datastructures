//
// Created by canta on 22/11/2023.
//

#ifndef INC_3_DATASTRUCTURES_SPARSEMATRIX_H
#define INC_3_DATASTRUCTURES_SPARSEMATRIX_H

#include <cstddef>
#include <vector>
#include <iostream>

namespace ProjectSparseMatrix{

    template <typename T>
    class sparseMatrix
    {
        public:
            //Create the matrix
            sparseMatrix(size_t n); //Square matrix
            sparseMatrix(size_t rows, size_t columns);

            sparseMatrix();

//            const T& operator()(std::size_t row, std::size_t column)
//            const;
//            T& operator()(std::size_t row, std::size_t column);

            //ProjectSparseMatrix(const ProjectSparseMatrix<T> & m); //Copy constructor
            //ProjectSparseMatrix<T> & operator = (const ProjectSparseMatrix<T> & m);

            //Values
            T get(size_t row, size_t column) const;
            sparseMatrix & set(T val, size_t row, size_t column);

            //Getter & Setter
            [[nodiscard]] size_t rowCount() const;
            [[nodiscard]] size_t columnCount() const;

            //Math functions
            sparseMatrix<T> multiply(const sparseMatrix<T> & m) const;
            sparseMatrix<T> add(const sparseMatrix<T> & m) const;
            sparseMatrix<T> subtract(const sparseMatrix<T> & m) const;

            void print() const;

    protected:
        std::size_t m = 0, n = 0; //m rows, n columns


        std::vector<T> * values;
        std::vector<std::size_t> * rows, * columns;

        //std::vector<size_t> * setRow{}, * setColumn{};

        //Construct methods
        void construct(size_t m, size_t n); //Init a new Sparsematrix
        void destruct();
        void insert(size_t index, size_t row, size_t column, T val);
        void remove(size_t index, size_t row);

    };

}
#endif //INC_3_DATASTRUCTURES_SPARSEMATRIX_H
