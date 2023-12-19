//
// Created by canta on 22/11/2023.
//
#include "3_Datastructures/SparseMatrix.h"

namespace SparseMatrix{

    ///Initializing a new sparseMatrix
    template<typename T>
    SparseMatrix<T>::SparseMatrix(size_t n)
    {
        this->construct(n,n);
    }

    template<typename T>
    SparseMatrix<T>::SparseMatrix(size_t rows, size_t columns)
    {
        this->construct(rows, columns);
    }

    template<typename T>
    SparseMatrix<T>::SparseMatrix(){
        this->destruct();
    }

    template<typename T>
    void SparseMatrix<T>::construct(size_t row, size_t column){

        //Check if rows and columns are empty
        if (row < 1 || column < 1)
            throw std::out_of_range("Matrix dimensions cannot be lower than 1");

        this->m = row;
        this->n = column;

        //Init new Matrix row
        this->values = NULL;

        this->rows = new std::vector<size_t>(row+1, 1);
        this->columns = NULL;
    }

    template<typename T>
    void SparseMatrix<T>::destruct() {
        if (values->empty() == true){ //Check if values are empty
            delete this->values;
            delete this->columns;
        }
        delete this->rows;
    }

    //Values
    template<typename T>
    T SparseMatrix<T>::get(size_t row, size_t column) const {
        std::cout << "Entering get(" << row << ", " << column << ")\n";

        if (row < 1 || column < 1 )
            return 0;

        int currCol;

        for (int pos = (*(this->rows))[row - 1] - 1; pos < (*(this->rows))[row] - 1; ++pos) {
            currCol = (*(this->columns))[pos];

            if (currCol == column) {
                return (*(this->values))[pos];

            } else if (currCol > column) {
                break;
            }
        }
        std::cout << "Exiting get"  << "\n";
        return T(); //Default construct if nothing was found
    }

    template<typename T>
    SparseMatrix<T> &SparseMatrix<T>::set(T val, size_t row, size_t column) {
        std::cout << "Entering set(" << val << ", " << row << ", " << column << ")\n";


        if (row < 1 || column < 1)
            throw std::out_of_range("Size can't be smaller than 1");

        //size_t position = this->rows - 1;

//        size_t start = 0;
//        size_t end = 0;
        size_t currentColumn = 0;
//        size_t currPos = 0;
        size_t pos = (*(this->rows))[row - 1] - 1;

        for (; pos < (*(this->rows))[row] - 1; pos++) {
            currentColumn = (*(this->columns))[pos];

            if (currentColumn >= column) {
                break;
            }
        }

//        for (size_t i = 0; i < row; i++) {
//            start = end;
//            end = this->rows[i];
//
//            for (size_t pos = start; pos < end; pos++) {
//                currentColumn = this->columns[pos];
//                currPos = pos;
//
//                if (currentColumn >= column)
//                    break;
//            }
//        }

        if (currentColumn != column){
            if (val != T())
                this->insert(pos, row, column, val);
        }
        else if (val == T()) {
            this->remove(pos, row);
        }
        else {
            (*(this->values))[pos] = val;
        }

        std::cout << "Exiting set\n";
        return *this; //Return a reference to the object, NOT the pointer
    }


    //Getter&Setter
    template<typename T>
    size_t SparseMatrix<T>::getRowCount() const {
        return this->m;
    }

    template<typename T>
    size_t SparseMatrix<T>::getColumnCount() const {
        return this->n;
    }

    //Insert & Remove a value
    template<typename T>
    void SparseMatrix<T>::insert(size_t index, size_t row, size_t column, T val) {
        // Ensure the index is within bounds
        if (index < 0 || index > this->values->size()) {
            throw std::out_of_range("Index out of bounds");
        }

        // Inserting at the specified index
        values->insert(values->begin() + index, val);
        columns->insert(columns->begin() + index, column);

        // Update the row pointers if necessary
        for (size_t i = row; i <= this->m; i++) {
            (*(this->rows))[i] += 1; // Increment row pointers after the insertion point
        }
    }

    template<typename T>
    void SparseMatrix<T>::remove(size_t index, size_t row) {
        values->erase(this->values->begin() + index);
        columns->erase(this->columns->begin() + index);

        // Update the row pointers
        for (size_t i = row; i < this->m; i++) {
            (*(this->rows))[i] -= 1; // Decrement row pointers after the remove
        }
    }

    ///Math functions

    template<typename T>
    SparseMatrix<T> SparseMatrix<T>::multiply(const SparseMatrix<T> &m) const {
        if (this->n != m.getRowCount() ){
            std::cerr << "Dimensions don't match. Left column and right row don't match size" << std::endl;
            throw std::runtime_error("Type mismatch");
        }

        SparseMatrix<T> result(this->m, T());

        if(!this->values){ //If there are no values there is nothing to multiply
           throw std::runtime_error("There are no values");
        }

        for (int row = 0; row < this->m; row++) { //rows
            for (int column = 0; column < m.getColumnCount(); column++) { //columns
                T product = T(); //new SparseMatrix for the product

                //Calculate the product of the 'i' row 1st matrix and the 'j' column of the 2nd
                for (int k = 0; k < this->n; k++) {
                    product = product + this->get(row,k) * m.get(k, column);
                }

                result.set(product, row, column);
            }
        }

        return result;
    }

    template<typename T>
    SparseMatrix<T> SparseMatrix<T>::add(const SparseMatrix<T> &m) const {
        if (this->m != m.getRowCount() || this->n != m.getColumnCount()){
            std::cerr << "Dimensions don't match. Matrix sizes must be the same." << std::endl;
            throw std::runtime_error("Type mismatch");
        }

        SparseMatrix<T> result(this->m, this->n);

        for (int i = 0; i < this->m; ++i) {
            for (int j = 0; j < this->n; ++j) {
                result.set((this->get(i,j) + m.get(i,j)), i ,j);
            }
        }
        return result;
    }

    template<typename T>
    SparseMatrix<T> SparseMatrix<T>::subtract(const SparseMatrix<T> & m) const
    {
        if (this->m != m.getRowCount() || this->n != m.getColumnCount()) {
            std::cerr << "Dimensions don't match. Matrix sizes must be the same." << std::endl;
        }

        SparseMatrix<T> result(this->m, this->n);

        for (int i = 1; i <= this->m; i++) {
            for (int j = 1; j <= this->n; j++) {
                result.set((this->get(i, j) - m.get(i, j)), i, j);
            }
        }

        return result;
    }

    //Friend functions
    template<typename U>
    bool operator==(const SparseMatrix<U> &valA, const SparseMatrix<U> &valB) {

        bool valuesEqual;
        if (valA.values == nullptr && valB.values == nullptr)
            valuesEqual = true;
        else if (valA.values != nullptr && valB.values)
            valuesEqual = std::equal(valA.values->begin(), valA.values->end(), valB.values->begin());

        // Check if both matrices have either NULL columns or non-NULL columns that are equal
        bool columnsEqual;
        if (valA.columns == nullptr && valB.columns == nullptr) {
            columnsEqual = true;
        } else if (valA.columns != nullptr && valB.columns != nullptr) {
            columnsEqual = std::equal(valA.columns->begin(), valA.columns->end(), valB.columns->begin());
        } else {
            columnsEqual = false;
        }

        // Check if row vectors are equal
        bool rowsEqual = (*(valA.rows) == *(valB.rows));

        return valuesEqual && columnsEqual && rowsEqual;
    }

    template<typename U>
    bool operator!=(const SparseMatrix<U> &valA, const SparseMatrix<U> &valB) {
        return !(valA == valB);
    }

    template<typename U>
    std::ostream &operator<<(const SparseMatrix<U> &outputStream, const SparseMatrix<U> &matrix) {
        for (size_t i = 0; i < matrix.getRowCount(); ++i) {
            for (size_t j = 0; j < matrix.getColumnCount(); ++j) {
                if (j != 0) {
                    outputStream << ' ';
                }

                outputStream << matrix.get(i + 1, j + 1);
            }

            if (i < matrix.getRowCount() - 1) {
                outputStream << '\n';
            }
        }

        return outputStream;
    }


    template
    SparseMatrix<int>::SparseMatrix(size_t n);

    template
    SparseMatrix<int>::SparseMatrix(size_t rows, size_t columns);

    template
    SparseMatrix<int>::SparseMatrix();

    template
    void SparseMatrix<int>::construct(size_t row, size_t column);

    template
    SparseMatrix<int> &SparseMatrix<int>::set(int val, size_t row, size_t column);

    //Getter&Setter
    template
    size_t SparseMatrix<int>::getRowCount() const;

    template
    size_t SparseMatrix<int>::getColumnCount() const;

    //Insert & Remove a value
    template
    void SparseMatrix<int>::insert(size_t index, size_t row, size_t column, int val);

    template
    void SparseMatrix<int>::remove(size_t index, size_t row);

    template
    SparseMatrix<int> SparseMatrix<int>::multiply(const SparseMatrix<int> &m) const;

    template
    SparseMatrix<int> SparseMatrix<int>::add(const SparseMatrix<int> &m) const;

    template
    SparseMatrix<int> SparseMatrix<int>::subtract(const SparseMatrix<int> & m) const;

    template
    bool operator==(const SparseMatrix<int> &valA, const SparseMatrix<int> &valB);

    template
    bool operator!=(const SparseMatrix<int> &valA, const SparseMatrix<int> &valB);

    //template
    //std::ostream &operator<<(const SparseMatrix<int> &outputStream, const SparseMatrix<int> &matrix);
}

int rows[] = {};
int columns[] = {};

int results[] = {};

