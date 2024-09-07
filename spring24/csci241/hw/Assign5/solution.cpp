#include <iostream>

using std::cout;
using std::cin;
using std::endl;

const int N = 8;


class eightQueens
{
private:

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
bool eightQueens::placeQueen(int row)
{
  if (row >= N) 
    return true;

  for (int col = 0; col < N; col++)
  {

    if (is_safe(row, col))
    {

      board[row][col] = 1;

      if (placeQueen(row + 1))
        return true;
    }

    board[row][col] = 0;
  }
  return false;
}

bool eightQueens::is_safe(int row, int col) const
{
    // Check the rows above this column. col stays the same, row varies
    // from row - 1 down to 0.
    for (int i = row  - 1; i >= 0; i--)
    {
        if (board[i][col] == 1)
            return false;
    }
    // Check the left diagonal above this row. col varies from col - 1
    // down to 0, row varies from row - 1 down to 0.
    for (int i = row - 1, j = col - 1; i >= 0 and j >= 0; i--, j--)
    {
        if (board[i][j] == 1)
            return false;
    }
    // Check the right diagonal above this row. col varies from col + 1
    // up to 7, row varies from row - 1 down to 0.
    for (int i = row - 1, j = col + 1; i >= 0 and j < N; i++, j++)
    {
        if (board[i][j] == 1)
            return false;
    }
    return true;
}
void eightQueens::drawBoard() const
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << board[i][j];
        }
        cout << endl;
    }
}

