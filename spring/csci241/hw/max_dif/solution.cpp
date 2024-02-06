#include <climits>

int max_diff_seq(int a[], int len)
{
  if (len <= 1) // Edge Case
    return -1; 
  
  int max_diff = INT_MIN;
  
  for (int i = 0; i < len - 1; i++)
  {
    for (int j = i + 1 ; j < len; j++)
      if (a[j] - a[i] > max_diff) 
        max_diff = a[j] - a[i];
  }
  return max_diff;
}
