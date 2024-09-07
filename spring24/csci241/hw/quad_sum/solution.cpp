#include <cstdlib>
#include <ctime>
#include <vector>

bool quad_sum_is_n(int a[], int len, int n) 
{
  // Edge cases
  if (len < 4)
    return false;

  if (len == 4)
  {
    int sum = a[0] + a[1] + a[2] + a[3];
    return (sum == n);
  }
int i = 0;
int j = i + 1;
int k = j + 1;
int l = k + 1;

while (i < len - 3)
{
  j = i + 1;
  while (j < len - 2)
  {
    k = j + 1;
    while (k < len - 1) 
    {
      l = k + 1; 
      while (l < len)
      {
        if ((a[i] + a[j] + a[k] + a[l]) == n)
          return true;
        else
          ++l;
      }
      k++;
    }
    j++;
  }
  i++;
}
  return false;
}
// 5 c 4 -> [1,2,3,4,5]
// [1,2,3,4],
// [1,2,3,5],
// [1,2,4,5],
// [2,3,4,5]
// Set i = index 0
// Set j = index 1
// Set k = index 2
// need a variable to point to all elements past k and increment up to the last element
// once we hit the end, we increment k
// when k == len - 2, we increment j
