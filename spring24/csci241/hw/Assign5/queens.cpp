//***************************************************************************
//
//  queens.cpp
//  CSCI 241 Assignment 5
//
//  Created by Matt Warner (z2004200)
//
//***************************************************************************
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

const int N = 8;

class eightQueens
{
private:

  // 8 x 8 chess board
  int board[N][N] = {{0}};

public:

  bool is_safe(int,int) const;
  void drawBoard() const;
  bool placeQueen(int);

};

int main(int argc, char *argv[]){

  eightQueens q;

    q.placeQueen(0);
    q.drawBoard();

  return 0;
}
/**
 * Recursive function that places queens on the board
 *
 * @param int row the current row that a queen should attemped to be placed on.
 *
 * @return true if successful and false if not.
 */
bool eightQueens::placeQueen(int row)
{
  // Base case
  if (row >= N) 
    return true;

  // iterates through all the columns of the given row
  for (int col = 0; col < N; col++) 
  {
    // checks if safe
    if (is_safe(row, col))
    {

      board[row][col] = 1; // Adds a queen

      if (placeQueen(row + 1)) // recurive call to place another queen on the next row.
        return true;

    board[row][col] = 0; // removes queen
    }

  }
  return false;
}
/**
 * Takes a square on the board as input to the function, 
 * and checks if the square (position in the 2D array) is safe
 *
 * @param int row - the row corresponding to the square that needs to be checked
 * @param int col - The column corresponding to the square that needs to be checked
 *
 * @returns true if the square is safe.
 *          false is the square is not safe.
 */
bool eightQueens::is_safe(int row, int col) const
{
    // iterates through all squares above the square passed into the function,
    // checking if they are safe, if one of the squares above is not safe, the function
    // returns false.
    for (int i = row  - 1; i >= 0; i--)
    {
        if (board[i][col] == 1)
            return false;
    }
    // iterates through the left diagnal on the board, checking if the squares are safe
    for (int i = row - 1, j = col - 1; i >= 0 &&j >= 0; i--, j--)
    {
        if (board[i][j] == 1)
            return false;
    }
    // Iterates through the squares on the right diagnal, checking if safe.
    for (int i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++)
    {
        if (board[i][j] == 1)
            return false;
    }

    return true; // Passed all checks, returns true
}
/**
 * Prints the 2D array that is used to represent the chess board.
 *
 *
 */
void eightQueens::drawBoard() const
{
    // Iterate through the rows 
    for (int i = 0; i < N; i++)
    {
        // Iterate through the columns
        for (int j = 0; j < N; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}
