bool is_Even(int grid[][4], int row, int col)
{
  return (grid[row][col] % 2 == 0);
}
int compute_score(int grid[][4])
{
  int score = 0;

  // Cbecking the corners
  if (is_Even(grid, 0, 0) && is_Even(grid,0,3) && is_Even(grid,3,0) && is_Even(grid, 3,3))
    score+=20;

  else if (!is_Even(grid, 0, 0) && !is_Even(grid,0,3) && !is_Even(grid,3,0) && !is_Even(grid, 3,3))
    score+=20;

  // Checking odd/even rows
  int evenCount, oddCount;
  bool gotEven = false, gotOdd = false;
  for (int i = 0; i < 4; i++) 
  {
    evenCount = (gotEven) ? 999 : 0;
    oddCount = (gotOdd) ? 999 : 0;

    for (int j = 0; j < 4; j++) 
    {
      if (!is_Even(grid, i, j))
      {
        oddCount++;
      }
      else
        evenCount++;
    }
    if (oddCount == 4)
    {
      score+=20;
      gotOdd = true;
    }
    else if (evenCount == 4)
    {
      score+=20;
      gotEven = true;
    }
  }

  // Checking the columns
  gotEven = false, gotOdd = false;
  for (int i = 0; i < 4; i++) 
  {
    evenCount = (gotEven) ? 999 : 0;
    oddCount = (gotOdd) ? 999 : 0;
    for (int j = 0; j < 4; j++)
    {
      if (!is_Even(grid, j, i))
        oddCount++;
      else
        evenCount++;
    }
    if (oddCount == 4)
    {
      score+=20;
      gotOdd = true;
    }
    else if (evenCount ==4)
    {
      score+=20;
      gotEven = true;
    }
  }
  // Checking the diaganols
  if (is_Even(grid, 0, 0) && is_Even(grid,1,1) && is_Even(grid, 2,2) && is_Even(grid, 3,3))
    score+=20;
  else if (!is_Even(grid, 0, 0) && !is_Even(grid,1,1) && !is_Even(grid, 2,2) && !is_Even(grid, 3,3))
    score+=20;

  if (is_Even(grid, 0, 3) && is_Even(grid,1,2) && is_Even(grid, 2,1) && is_Even(grid, 3,0))
    score+=20;
  else if (!is_Even(grid, 0, 3) && !is_Even(grid,1,2) && !is_Even(grid, 2,1) && !is_Even(grid, 3,0))
    score+=20;

  for (int i = 0; i < 4; i++) 
  {
    for (int j =0; j < 4; j++) 
    {
      score+=grid[i][j];
    }
  }
  return score;
}

