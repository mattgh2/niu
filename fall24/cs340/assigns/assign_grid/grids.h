/************************************************************************************
* NIU CSCI 340 Section 3
* Assignment # 4
* Matt Warner - z2004200
* *
* I certify that everything I am submitting is either provided by the professor for use in *
* the assignment, or work done by me personally. I understand that if I am caught submitting *
* the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic *
* Misconduct and will be punished as such. *
* *
* Implementation of a container that provides a resizeable 2D grid.
* 
************************************************************************************/
#ifndef NIU_CSCI_340_GRIDS_IMPL_H
#define NIU_CSCI_340_GRIDS_IMPL_H

// include the declarations needed for this
#include <iostream>
#include <fstream>
#include "grids.decl.h"
#include <numeric>

inline void throw_out_of_range();


////////////////////////////////////////////////////////////////////////////////
//
// grid_row_major method implementations
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Checks if coordinates are inside the boundaries of the container.
 *
 * @param x X coordinate for container.
 * @param y Y coordinate for container.
 *
 * @return true if coordinates (x,y) are in bounds.
 */
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::boundscheckxy(int x, int y) const {
  if ((x < 0 || x >= _width) || (y < 0 || y >= _height)) {
    return false;
  }
  return true;
}
/**
 * Checks if an entry at (row,column) is inside the boundaries of the container.
 *
 * @param row The row number of the container.
 * @param col The col number of the container.
 *
 * @return true if the entry at (row,column) is inside the bounds of the container.
 */
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::boundscheckrc(int row, int col) const {
    if ((row < 0 || row >= _height) || (col < 0 || col >= _width)) {
        return false;
    }
    return true;
}

/**
 * Checks if the container is empty.
 *
 * @return true if the container is empty.
 */
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::empty() const {
    return (_width == 0 && _height == 0);
}

/**
 * Clears the contents of the container.
 */
template <typename T, typename RA_CONTAINER>
void grid_row_major<T,RA_CONTAINER>::clear() {
    data.clear();
    _width = 0;
    _height = 0;
}
/**
 * Gets an element at position (x,y).
 *
 * @param y The x coordinate of the container.
 * @param y The y  coordinate of the container.
 *
 * @return the element at (x,y)
 */
template <typename T, typename RA_CONTAINER>
T & grid_row_major<T,RA_CONTAINER>::atxy(int x, int y) {
    if (!boundscheckxy(x,y)) {
        throw_out_of_range();
    }
    int pos = (_width * y) + x;
    return data[pos];
}

/**
 * Const version of grid_row_major::atxy()
 * Gets an element at position (x,y).
 *
 * @param y The x coordinate of the container.
 * @param y The y  coordinate of the container.
 *
 * return the element at (x,y)
 */
template <typename T, typename RA_CONTAINER>
const T & grid_row_major<T,RA_CONTAINER>::atxy(int x, int y) const {
    // Checks if row,col is in bounds.
    if (!boundscheckxy(x,y)) {
        throw_out_of_range();
    }
    // Calculate position in matrix
    int pos = (_width * y) + x;
    return data[pos];
}
/**
 * Gets an element at row, col from the container.
 *
 * @param row The row number of the container.
 * @param col The col number of the container.
 *
 * @return The element at (row,col)
 */
template <typename T, typename RA_CONTAINER>
T & grid_row_major<T,RA_CONTAINER>::atrc(int row, int col) {
    // Check if row,col is in bounds.
    if (!boundscheckrc(row,col)) {
        throw_out_of_range();
    }
    // Calculates the position of the element.
    int pos = (_width * row) + col;
    return data[pos];
}
/**
 * Const version of grid_row_major::atrc()
 * Gets an element at row, col from the container.
 *
 * @param row The row number of the container.
 * @param col The col number of the container.
 *
 * @return The element at (row,col)
 */
template <typename T, typename RA_CONTAINER>
const T & grid_row_major<T,RA_CONTAINER>::atrc(int row, int col) const {
    // Check if row,col is in bounds.
    if (!boundscheckrc(row,col)) {
        throw_out_of_range();
    }
    // Calculates the position of the element.
    int pos = (_width * row) + col;
    return data[pos];
}
/**
 * Gets the width (number of entries per row) of the container.
 *
 *
 * @return The width of the container
 */
template <typename T, typename RA_CONTAINER>
int grid_row_major<T,RA_CONTAINER>::width() const {
    return _width;
}

/**
 * Gets the height (number of entries per column) of the container.
 *
 * @return The height of the container.
 */
template <typename T, typename RA_CONTAINER>
int grid_row_major<T,RA_CONTAINER>::height() const {
    return _height;
}
/**
 * Copy assignment operator.
 *
 * @param source The source container that gets its state copied.
 *
 * @return The current objects new state after copy.
 */
template <typename T, typename RA_CONTAINER>
template <typename OTHER_CONTAINER>
grid_row_major <T, RA_CONTAINER> & grid_row_major<T, RA_CONTAINER>::operator = (const grid_row_major<T, OTHER_CONTAINER> & source) {
    // Check for self assignment.
    if (this != &source) {

        // Copy state.
        _width = source.width;
        _height = source.height;

        // Call copy assignment on source data.
        data = source.data;  

        return *this;
    }
}
/**
 * Gets an iterator to the beginning of a row.
 *
 * @param row The row to point at.
 *
 * @return An iterator pointing to the beginning of a given row.
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::rowbegin(int row) {
    return std::begin(this->data) + (row * this->_width);
}
/**
 * Gets an iterator to the end of a given row.
 *
 * @param row The row to point to.
 *
 * @return An iterator pointing one past the end of a row.
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::rowend(int row) {
    return rowbegin(row) + this->_width;
}
/**
 * Const version of rowbegin()
 * @param row The row to point to.
 *
 * @return An iterator pointing one past the end of a row.
 *
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::rowbegin(int row) const {
    return std::begin(this->data) + (row * this->_width);
}
/**
 * Const version of rowend()
 * Gets an iterator to the end of a given row.
 *
 * @param row The row to point to.
 *
 * @return An iterator pointing one past the end of a row.
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::rowend(int row) const {
    return rowbegin(row) + this->_width;
}
/**
 * Gets an iterator to the beginning of a column.
 *
 * @param col The column to point to the start of.
 *
 * @return A col_iterator.
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::colbegin(int col) {
    return col_iterator(std::begin(this->data) + col, _width);
}
/**
 * Gets an iterator to one past the end of a column. 
 *
 * @param col the column to point to.
 *
 * @return A col_iterator pointing one past the desired column.
 */
template <typename T, typename RA_CONTAINER>
auto grid_row_major<T,RA_CONTAINER>::colend(int col) {
    return ++(col_iterator((data.end() - _width) + col, _width));
}
/**
 * Destructivly resizes the container.
 *
 * @param new_width The new width for the container.
 * @param new_height The new height for the container.
 *
 */
template <typename T, typename RA_CONTAINER>
void grid_row_major<T, RA_CONTAINER>::resize(int new_width, int new_height) {
    // Calculate new size of the grid.
    int new_sz = new_width * new_height;
    
    // Adjust to new width and height.
    _width = new_width;
    _height = new_height;

    // Remove all data from grid.
    data.clear();

    // Resize to fit new data.
    data.resize(new_sz);

}
/**
 * Loads input from file into container.
 *
 * @param filename The filename to extract from.
 *
 * @return true if the operation is a success.
 */
template <typename T, typename RA_CONTAINER>
bool grid_row_major<T,RA_CONTAINER>::load_from_file(const std::string & filename) {

    // Open file.
    std::ifstream infile(filename);

    // Check for successful file open.
    if (infile.fail()) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return false;
    }
    // Read _width and _height from file 
    infile >> _width >> _height;

    // Resize to fit data from file.
    this->resize(_width, _height);
    
    // Read from file to data.
    auto it = std::begin(data);
    while (infile) { 
        // Check if container ran out of storage space.
        if (it == data.end()) {
            break;
        } 
        // Check if file has no more data left before
        // attempting to add to container.
        if (!(infile >> *it)) {
            std::cerr << filename <<  " does not provide enough data\n";
            return false;
        }
        ++it; 
    }

    infile.close();
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//
// Matrix Multiplication Implementation
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Computes matrix multiplication on two given matricies.
 * Height of matrix1 must match matrix2.
 *
 * @param lhs A matrix.
 * @param rhs A matrix.
 * @param result the resulting Matix, 
 *
 * @return 
 */
template <typename GRID1, typename GRID2, typename GRID3>
bool matrix_multiply(GRID1 lhs, GRID2 rhs, GRID3 & result) {

    // Height of first matrix must match the width of second matrix.
    if (lhs.height() != rhs.width()) {
        return false;
    }
    // Resize result to fit the output of matrix multiplication.
    result.resize(lhs.width(), rhs.height());

    int row_count = 0, column_count = 0;

    // For each row in lhs, compute the dot product against every column and add to the result matricies.
    while (row_count < lhs.height()) {
    
        // Compute the i,jth entry for the result matrix.
        result.atrc(row_count, column_count) = std::transform_reduce(lhs.rowbegin(row_count), lhs.rowend(row_count), rhs.colbegin(column_count), 0);

        // If current row has seen every column, reset column_count back to 0 and increment row.
        (column_count == rhs.width() - 1) ? ++row_count, column_count = 0 : ++column_count;
    }

    return true; 
}

////////////////////////////////////////////////////////////////////////////////
//
// Column iterator implementation
//    These are for the col_iterator class I provided for you. Feel free to
// implement these to use that for your column iterators, or you can implement
// it in another way if you prefer that.
//
////////////////////////////////////////////////////////////////////////////////

/**
 * preincrement col_iterator to the next entry in the column
 *
 * @return col_iterator after increment.
 */
template <typename ITERATOR>
auto & col_iterator<ITERATOR>::operator ++ () { // preincrement
    this->pos = pos + width;
    return *this;
}

/**
 * Postincrement col_iterator to the next entry in the column.
 *
 * @return col_iterators state before increment.
 */
template <typename ITERATOR>
auto col_iterator<ITERATOR>::operator ++ (int) { // postincrement
    // Capture state before increment
    col_iterator before_increment(*this);

    ++(*this);
    return before_increment;
}
    
/**
 * Performs addition on a col_iteartor to get at a new position in the container.
 *
 * @param n Value to add to col_iterator
 *
 * @return A col_iterator pointing to the result of arithmetic.
 */
template <typename ITERATOR>
col_iterator <ITERATOR> col_iterator<ITERATOR>::operator + (int n) const {
    return col_iterator(pos + (width * n), width);
}
/**
 * Gets a position in the container via indexing.
 *
 * @param The position to index to.
 *
 * @return The element at index n.
 */
template <typename ITERATOR>
auto & col_iterator <ITERATOR>::operator [] (int n) {
    return *(pos+ (width * n));
}
/**
 * Const version of operator[] for col_iteartor.
 * Gets a position in the container via indexing.
 *
 * @param The position to index to.
 *
 * @return The element at index n.
 */
template <typename ITERATOR>
const auto & col_iterator <ITERATOR>::operator [] (int n) const {
    return *(pos+ (width * n));
}
/**
 * Deferences a col_iterator.
 * Provides the value pointed to by col_iterator.
 *
 * @return The element that the col_iterator points to.
 */    
template <typename ITERATOR>
auto & col_iterator<ITERATOR>::operator * () {
    return *(pos);
}
/**
 * Const version of operator*
 * Provides the value pointed to by col_iterator.
 *
 * @return The element that the col_iterator points to.
 */
template <typename ITERATOR>
const auto & col_iterator<ITERATOR>::operator * () const {
    return *(pos);
}
/**
 * Tests two col_iterators for equality.
 *
 * @param other A col_iterator.
 *
 * @return true if both iterators point to the same location.
 */
template <typename ITERATOR>
bool col_iterator <ITERATOR>::operator == (const col_iterator <ITERATOR> &other) {
    return (pos == other.pos);
}

/**
 * Helper function for atxy(), atrc().
 * Throws an error message.
 *
 */
inline void throw_out_of_range() {
    throw std::out_of_range("coordinates are out of bounds.");
}
#endif

