//***************************************************************************
//
//  matrix.h
//  CSCI 241 Assignment 10
//
//  Created by Matt Warner (z2004200)
//
//***************************************************************************

#ifndef MATRIX_H
#define MATRIX_H
#include <ostream>

class matrix {

private:
  int matrixArray[2][2];

public:

  // Constructors
  matrix(); 
  matrix(int matrixArray[][2]);

  // friend declarations
  friend std::ostream& operator<<(std::ostream& os, const matrix &matrixObj);
  friend matrix operator*(int scalar, const matrix &matrixObj);
  
  int determinant() const;

  // Operation overloading
  matrix operator+(const matrix &matrixObj) const;
  matrix operator*(int scalar) const;
  matrix operator*(const matrix &matrixObj) const;
  bool operator==(const matrix &matrixObj) const;
  bool operator!=(const matrix &matrixObj) const;
};

// standalone function prototypes
std::ostream& operator<<(std::ostream& os, const matrix &matrixObj);
matrix operator*(int scalar, const matrix &matrixObj);

#endif
