void rotate_matrix(int destination[][8], int source[][8])
{
  for (int j = 0; j < 8; j++)
  {
    for (int i = 0, k = 7; i < 8 && k >= 0; i++, k--)
      destination[j][k] = source[i][j];
  }
}
