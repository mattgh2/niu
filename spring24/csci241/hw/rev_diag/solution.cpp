#include <utility>


void reverse_diagonal(int array[][4])
{
  int i = 0, j = 0, k = 3, l = 3;
  while (i < k && j < l)
  {
    std::swap(array[i][j], array[k][l]);
    i++,j++,k--,l--;
  }

  i = 3, j = 0, k = 0, l = 3;
  while (i > k && j < l)
  {
    std::swap(array[i][j],array[k][l]);
    i--, j++, k++, l--;
  }
}
