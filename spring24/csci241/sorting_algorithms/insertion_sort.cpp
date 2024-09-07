#include <utility>

void insertion_sort(int array[], int n)
{
  for (int i = 1; i < n; i++)
  {
    for (int j = i; j >= 0 && array[j -1] > array[j]; j--)
    {
      std::swap(array[j-1], array[j]);
    }
      
  }
}
