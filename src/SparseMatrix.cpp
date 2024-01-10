//
// Created by canta on 22/11/2023.
//
#include "3_Datastructures/sparseMatrix.h"

namespace ProjectSparseMatrix{

    ///Initializing a new sparseMatrix
    template<typename T>
    sparseMatrix<T>::sparseMatrix(size_t n)
    {
        this->construct(n,n);
    }

    template<typename T>
    sparseMatrix<T>::sparseMatrix(size_t rows, size_t columns)
    {
        this->construct(rows, columns);
    }

    template<typename T>
    sparseMatrix<T>::sparseMatrix(){
        this->destruct();
    }

    template<typename T>
    void sparseMatrix<T>::construct(size_t row, size_t column){

        //Check if rows and columns are empty
        if (row < 1 || column < 1)
            throw std::out_of_range("Matrix dimensions cannot be lower than 1");

        this->m = row;
        this->n = column;

        //Init new Matrix row
        values = NULL;
        rows = new std::vector<size_t>(row+1, 1);
        columns = NULL;
    }

    template<typename T>
    void sparseMatrix<T>::destruct() {
        if (values->empty() == true){ //Check if values are empty
            delete values;
        }
        //Also delete columns and rows
        delete columns;
        delete rows;
    }

    //Values
    template<typename T>
    T sparseMatrix<T>::get(size_t row, size_t column) const {
        //std::cout << "Entering get(" << row << ", " << column << ")\n";

        if (row < 1 || column < 1 )
            return 0;

        int currCol;

        for (int pos = (*(rows))[row - 1] - 1; pos < (*(rows))[row] - 1; ++pos) {
            currCol = (*(columns))[pos];

            if (currCol == column) {
                return (*(values))[pos];

            } else if (currCol > column) {
                break;
            }
        }
        //std::cout << "Exiting get"  << "\n";
        return T(); //Default construct if nothing was found
    }

    template<typename T>
    sparseMatrix<T> &sparseMatrix<T>::set(T val, size_t row, size_t column) {
        //std::cout << "Entering set(" << val << ", " << row << ", " << column << ")\n";

        //Check if coordinates are OK
        if (row < 1 || column < 1)
            throw std::out_of_range("Size can't be smaller than 1");

        size_t position = (*(this->rows))[row - 1] - 1;
        size_t currentColumn = 0;

        for (position; position < (*(this->rows))[row] - 1; position++) {
            currentColumn = (*(this->columns))[position];

            if (currentColumn >= column) {
                break;
            }
        }

        // Check if the column already exists
        if (currentColumn != column) {
            // Insert new value if != 0
            if (val != T()) {
                this->insert(position, row, column, val);
            }
        } else {
            // Check if new value == 0
            if (val == T()) {
                // Remove
                this->remove(position, row);
            } else {
                // Update the existing value in the header class with the non-zero value
                (*(this->values))[position] = val;
            }
        }

        //std::cout << "Exiting set\n";
        return *this; //Return a reference to the object, NOT the pointer
    }


    //Getter&Setter
    template<typename T>
    size_t sparseMatrix<T>::rowCount() const {
        return this->m;
    }

    template<typename T>
    size_t sparseMatrix<T>::columnCount() const {
        return this->n;
    }

    //Insert & Remove a value
    template<typename T>
    void sparseMatrix<T>::insert(size_t index, size_t row, size_t column, T val) {

        // valid index?
        if (this->values == NULL) {
            values = new std::vector<T>(1, val);
            columns = new std::vector<size_t>(1, column);
        }else{
            // Inserting at parameter's index
            values->insert(values->begin() + index, val);
            columns->insert(columns->begin() + index, column);
        }

        // Update row pointers on row change
        for (size_t i = row; i <= this->m; i++) {
            (*(this->rows))[i] += 1; // Increment row pointers
        }
    }

    template<typename T>
    void sparseMatrix<T>::remove(size_t index, size_t row) {
        values->erase(this->values->begin() + index);
        columns->erase(this->columns->begin() + index);

        // row pointers again
        for (size_t i = row; i < this->m; i++) {
            (*(this->rows))[i] -= 1; // Decrement row pointers after the remove
        }
    }

    ///Math functions
    template<typename T>
    sparseMatrix<T> sparseMatrix<T>::multiply(const sparseMatrix<T> &matrixToMultiply) const {
        if (this->n != matrixToMultiply.rowCount()) {
            std::cerr << "Dimensions don't match. Left column and right row don't match size" << std::endl;
            throw std::runtime_error("Type mismatch");
        }

        sparseMatrix<T> result(this->m, matrixToMultiply.n); //Resulting matrix

        if (!values) { // Check if values aren't empty, if empty --> there is nothing to multiply
            throw std::runtime_error("There are no values");
        }

        for (size_t resultRow = 1; resultRow <= this->m; ++resultRow) { //Go over the rows
            for (size_t resultCol = 1; resultCol <= matrixToMultiply.n; ++resultCol) { //Go over the columns
                T product = T(); // Initialize product

                for (size_t Dimensions = 1; Dimensions <= this->n; ++Dimensions) { //Dimensions  = (number of columns in the first matrix and rows in the second matrix)
                    product += this->get(resultRow, Dimensions) * matrixToMultiply.get(Dimensions, resultCol);
                }

                result.set(product, resultRow, resultCol); //Set values of the resulting product to result
            }
        }

        return result;
    }

    template<typename T>
    sparseMatrix<T> sparseMatrix<T>::add(const sparseMatrix<T> &matrix) const {
        if (m != matrix.rowCount() || n != matrix.columnCount()) {
            std::cerr << "Matrices must have the same dimensions for addition." << std::endl;
            throw std::runtime_error("Dimension mismatch");
        }
        sparseMatrix<T> result(m, n);
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                T sum = get(i, j) + matrix.get(i, j);
                result.set(sum, i, j);
            }
        }
        return result;
    }

    template<typename T>
    sparseMatrix<T> sparseMatrix<T>::subtract(const sparseMatrix<T> & m) const
    {
        if (this->m != m.rowCount() || this->n != m.columnCount()) {
            std::cerr << "Dimensions don't match. Matrix sizes must be the same." << std::endl;
        }

        sparseMatrix<T> result(this->m, this->n);

        for (int i = 1; i <= this->m; i++) {
            for (int j = 1; j <= this->n; j++) {
                result.set((this->get(i, j) - m.get(i, j)), i, j);
            }
        }
        return result;
    }

    ///Friend functions
    template<typename U>
    bool operator==(const sparseMatrix<U> &valA, const sparseMatrix<U> &valB) {
        bool valuesEqual;
        if (valA.values == nullptr && valB.values == nullptr)
            valuesEqual = true;
        else if (valA.values != nullptr && valB.values)
            valuesEqual = std::equal(valA.values->begin(), valA.values->end(), valB.values->begin());

        // Check if both matrices have either NULL columns or columns with a value that are equal
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
    bool operator!=(const sparseMatrix<U> &valA, const sparseMatrix<U> &valB) {
        return !(valA == valB);
    }

    template<typename T>
    void sparseMatrix<T>::print() const {
        const char horizontalBorderChar = '=';
        const char verticalBorderChar = '#';
        const size_t cellWidth = 8;

        // Print the top border
        std::cout << verticalBorderChar << std::string(n * (cellWidth + 1), horizontalBorderChar) << verticalBorderChar << '\n';

        // Print the matrix content
        for (size_t i = 1; i <= m; ++i) {
            std::cout << verticalBorderChar;

            for (size_t j = 1; j <= n; ++j) {
                T value = get(i, j);
                size_t valueWidth = std::to_string(value).length();

                // Print cell value centered within the cell
                size_t paddingBefore = (cellWidth - valueWidth) / 2;
                size_t paddingAfter = cellWidth - valueWidth - paddingBefore;

                if (!value)
                    std::cout << std::string(paddingBefore, ' ') << "." << std::string(paddingAfter, ' ');
                else
                    std::cout << std::string(paddingBefore, ' ') << value << std::string(paddingAfter, ' ');

                // Print vertical border between cells
                if (j < n) {
                    std::cout << verticalBorderChar;
                }
            }

            std::cout << '\n';
        }

        // Print the bottom border
        std::cout << verticalBorderChar << std::string(n * (cellWidth + 1), horizontalBorderChar) << verticalBorderChar << '\n';
    }

    template
    void sparseMatrix<int>::print() const;

    template
    sparseMatrix<int>::sparseMatrix(size_t n);

    template
    sparseMatrix<int>::sparseMatrix(size_t rows, size_t columns);

    template
    sparseMatrix<int>::sparseMatrix();

    template
    void sparseMatrix<int>::construct(size_t row, size_t column);

    template
    sparseMatrix<int> &sparseMatrix<int>::set(int val, size_t row, size_t column);

    //Getter&Setter
    template
    size_t sparseMatrix<int>::rowCount() const;

    template
    size_t sparseMatrix<int>::columnCount() const;

    //Insert & Remove a value
    template
    void sparseMatrix<int>::insert(size_t index, size_t row, size_t column, int val);

    template
    void sparseMatrix<int>::remove(size_t index, size_t row);

    template
    sparseMatrix<int> sparseMatrix<int>::multiply(const sparseMatrix<int> &m) const;

    template
    sparseMatrix<int> sparseMatrix<int>::add(const sparseMatrix<int> &m) const;

    template
    sparseMatrix<int> sparseMatrix<int>::subtract(const sparseMatrix<int> & m) const;

    template
    bool operator==(const sparseMatrix<int> &valA, const sparseMatrix<int> &valB);

    template
    bool operator!=(const sparseMatrix<int> &valA, const sparseMatrix<int> &valB);
}

int rows[] = {};
int columns[] = {};

int results[] = {};