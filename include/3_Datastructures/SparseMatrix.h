//
// Created by canta on 22/11/2023.
//

#ifndef INC_3_DATASTRUCTURES_SPARSEMATRIX_H
#define INC_3_DATASTRUCTURES_SPARSEMATRIX_H

#include <cstddef>

// This class represents our sparse matrix.
// It takes 1 template argument,
// which reflects the type of element the matrix will be made up of
// (int, float, double, ...)
// Operations between two matrices (Such as multiplication)
// are only allowed between matrices with the same template argument.
//
// A sparse matrix of size N x M with Z non-zero elements
// (Z <= N x M) should have a space complexity of O(Z).
template <typename ElementType>
class SparseMatrix
{
public:
    // matrix has a fixed size, specified by `rows` and `columns`
    SparseMatrix(std::size_t rows, std::size_t columns);
    // We use operator() to access individual elements of the matrix.
    // Note that this method returns a const reference. Thus, the element must exist
    // and the element will not be modified
    // (Because the reference is const).

    // Note that the method itself is not marked const.
    // This is to accommodate the case where
    // an element that has not been accessed before is accessed.
    // In this case, you must assume the element is zero,
    // and return a const-reference to a default-constructed object
    // of type ElementType.
    // (We will make the assumption that default constructing
    // an element yields the equivalent of the value 0).
    // Note that the method is marked `const`.
    // This is required to distinguish it from the non-const overload.
    // This will prevent you from modifying the underlying matrix,
    // however, this shouldn’t be an issue.
    const ElementType& operator()(std::size_t row, std::size_t column)
    const;
    // This is another overload of the operator().
    // This one, however returns a mutable reference (non-const),
    // which means the user may assign to or otherwise modify
    // the value returned.
    // Thus, it is important that this value already exists,
    // and is in its final place.
    // When accessing an element that hasn’t been accessed before,
    // the same rules apply as in the previous overload of operator().
    ElementType& operator()(std::size_t row, std::size_t column);
    // In this case, operator* implements matrix-matrix multiplication.
    // For 2 sparse matrices A and B of size
    // N x M and M x K respectively, each with
    // Y or Z non-zero elements respectively,
    // the time-complexity of this operation should be
    // O((K * Y) + (N * Z)).
    // Before this method starts calculating,
    // it should verify that both matrices have compatible shapes
    // (`left` should have the same number of columns as
    // `right` has rows).
    // If this is not the case, the method should throw an exception.
    // We only allow this operation between matrices with
    // the same template argument.
    template<typename U>
    friend SparseMatrix<U> operator*(
            const SparseMatrix<U>& left,
            const SparseMatrix<U>& right
    );
    // This method should return an iterator that iterates over
    // all elements in the matrix,
    // regardless of whether they are non-zero or not.
    // When dereferenced, the elements in the iterator can be
    // mutable or immutable.
    // TODO: You should decide the return type of this method.
    auto begin();

    // This method should return an end iterator,
    // that can be compared against the iterator returned by begin().
    // When dereferenced, the elements in the iterator can be
    // mutable or immutable.
    // TODO: You should decide the return type of this method.
    auto end();
};

#endif //INC_3_DATASTRUCTURES_SPARSEMATRIX_H
