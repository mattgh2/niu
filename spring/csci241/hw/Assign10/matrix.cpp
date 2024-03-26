//***************************************************************************
//
//  file-name
//  CSCI 241 Assignment 10
//
//  Created by Matt Warner (z2004200)
//
//***************************************************************************
#include "matrix.h"

// Max rows and columns for matrices
const int ROWS = 2;
const int COLS = 2;
/**
 * Default constructor that initalizes matrix to default values 
 *
 */
matrix::matrix() {
  matrixArray[0][0] = 1; matrixArray[0][1] = 0; // first row
  matrixArray[1][0] = 0; matrixArray[1][1] = 1; // second row
}
/**
 * Array initalization constructor
 *
 * @param matrixArray: a 2x2 two dimensional array of integers
 *
 * @note
 * copies the values from the matrix passed into the function into the data member of the matrix class
 */
matrix::matrix(int matrixArray[][2]) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      this->matrixArray[i][j] = matrixArray[i][j];
    }
  }
}
/**
 * performs simple calculation to get the determinant of the matrix.
 *
 * @return The integer determinant of the matrix
 */
int matrix::determinant() const
{
  return (matrixArray[0][0] * matrixArray[1][1]) - (matrixArray[0][1] * matrixArray[1][0]);
}
/**
 * performs matrix addition
 *
 * @param matrixObj: a constant reference to an object of the matrix class.
 *
 * @return The result of the matrix addition of the left and right operands. i.e., a new matrix object
 */
matrix matrix::operator+(const matrix &matrixObj) const {
  matrix result; // temp object to hold results
  
  // Loops through rows and columns of matrix
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      result.matrixArray[i][j] = (this->matrixArray[i][j] + matrixObj.matrixArray[i][j]);
    }
  }
  return result;
}
/**
 * performs scalar multiplication with the scalar as the right operand
 *
 * @param scalar: An integer value that is treated as the scalar
 *
 * @return the result of multiplying the elements of the matrix by scalar
 */ 
matrix matrix::operator*(int scalar) const {
  matrix result;

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      result.matrixArray[i][j] = (this->matrixArray[i][j] * scalar);
    }
  }
  return result;
}
/**
 * Multiplies two matrices together
 *
 * @param matrixObj: A reference to a constant matrix object.
 *
 * @return a new matrix object that is the result of multiplying two matrices together.
 *
 */
matrix matrix::operator*(const matrix &matrixObj) const {
  matrix result;

  // Brute forced the matrix
  result.matrixArray[0][0] = (this->matrixArray[0][0] * matrixObj.matrixArray[0][0]) + (this-> matrixArray[0][1] * matrixObj.matrixArray[1][0]);
  result.matrixArray[0][1] = (this->matrixArray[0][0] * matrixObj.matrixArray[0][1]) + (this-> matrixArray[0][1] * matrixObj.matrixArray[1][1]);
  result.matrixArray[1][0] = (this->matrixArray[1][0] * matrixObj.matrixArray[0][0]) + (this-> matrixArray[1][1] * matrixObj.matrixArray[1][0]);
  result.matrixArray[1][1] = (this->matrixArray[1][0] * matrixObj.matrixArray[0][1]) + (this-> matrixArray[1][1] * matrixObj.matrixArray[1][1]);

  return result;
}
/**
 * Overloading relational "==" operator to check for equality with two matrices
 *
 * @param a constant reference to a matrix object
 *
 * @return true if all elements of the two matrices are the same. Otherwise the function returns false.
 *
 */
bool matrix::operator==(const matrix &matrixObj) const {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (this->matrixArray[i][j] != matrixObj.matrixArray[i][j])
        return false;
    }
  }
  return true;
}
/**
 * Overloading relational "!=" operator to see if two matrices are not equal to each other.
 *
 * @param a reference to a constant matrix object, representing the right operand of the relational expression.
 *
 * @return false if the two matrices are identical. Otherwise the function returns true.
 */
bool matrix::operator!=(const matrix &matrixObj) const {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (this->matrixArray[i][j] == matrixObj.matrixArray[i][j])
        return false;
    }
  }
  return true;
}
/**
 * Overloading the stream insertion operator << to print out objects of the matrix class.
 *
 * @param os: the stream insertion operator
 * @param matrixObj: a reference to a constant matrix object.
 *
 * @return a reference to an ostream object
 */
std::ostream& operator<<(std::ostream& os, const matrix &matrixObj) {
  os << "[[" << matrixObj.matrixArray[0][0] << ", " 
     << matrixObj.matrixArray[0][1] << "], [" 
     << matrixObj.matrixArray[1][0] << ", " 
     << matrixObj.matrixArray[1][1] << "]]";

  return os;
}
/**
 * Performs scalar multiplication on matrix with scalar as the left operand
 *
 * @param scalar: an integer value used as the scalar
 * @param matrixObj: a reference to a constant matrix object.
 *
 * @return a matrix object that is a new matrix holding the results of the multiplication
 *
 * @note:
 * not a member function because the left operand is not an object,
 * has a friend so that we can access the private data members.
 */
matrix operator*(int scalar, const matrix &matrixObj) {
  matrix result; // temp matrix

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      result.matrixArray[i][j] = scalar * matrixObj.matrixArray[i][j];
    }
  }
  return result;
}
