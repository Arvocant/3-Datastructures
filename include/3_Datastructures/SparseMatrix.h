//
// Created by canta on 22/11/2023.
//

#ifndef INC_3_DATASTRUCTURES_SPARSEMATRIX_H
#define INC_3_DATASTRUCTURES_SPARSEMATRIX_H

#include <cstddef>
#include <vector>
#include <iostream>

namespace SparseMatrix{

    template <typename T>
    class SparseMatrix
    {
        public:
            //Create the matrix
            SparseMatrix(size_t n); //Square matrix
            SparseMatrix(size_t rows, size_t columns);

            SparseMatrix();

//            const T& operator()(std::size_t row, std::size_t column)
//            const;
//            T& operator()(std::size_t row, std::size_t column);

            //SparseMatrix(const SparseMatrix<T> & m); //Copy constructor
            //SparseMatrix<T> & operator = (const SparseMatrix<T> & m);

            //Values
            T get(size_t row, size_t column) const;
            SparseMatrix & set(T val, size_t row, size_t column);

            //Getter & Setter
            [[nodiscard]] size_t getRowCount() const;
            [[nodiscard]] size_t getColumnCount() const;


            //Friend functions
//            template<typename U>
//            friend SparseMatrix<U> operator*(
//                    const SparseMatrix<U>& left,
//                    const SparseMatrix<U>& right
//            );


            //Operations
            template<typename U>
            friend bool operator == (const SparseMatrix<U> &valA, const SparseMatrix<U> &valB); //We check if the value we want to add is equal to the value in the indice.

            template<typename U>
            friend bool operator != (const SparseMatrix<U> &valA, const SparseMatrix<U> &valB);

            template<typename U>
            friend std::ostream & operator << (const SparseMatrix<U> &outputStream, const SparseMatrix<U> &matrix);
            //friend gives access to private and protected elements of SparseMatrix a & b;
            //std::ostream allows chaining of multiple << operations. << = output stream.

            ///Math functions
            SparseMatrix<T> multiply(const SparseMatrix<T> & m) const;
            SparseMatrix<T> add(const SparseMatrix<T> & m) const;
            SparseMatrix<T> subtract(const SparseMatrix<T> & m) const;

            void print() const;

        // TODO: You should decide the return type of this method.
        auto begin();

        // TODO: You should decide the return type of this method.
        auto end();

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
