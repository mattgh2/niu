#include <iostream>
#include <utility>

int partition(int array[], int start, int end)
{
  int mid = (start + end) / 2;

  std::swap(array[start], array[mid]);

  int pivot_index = start;
  int pivot_value = array[start];

  int scan = start + 1;

  while (scan <= end)
  {
    if (array[scan] < pivot_value)
    {
      pivot_index++;
      std::swap(array[pivot_index], array[scan]);
    }
    scan++;
  }
  std::swap(array[start], array[pivot_index]);
  
  return pivot_index;

}
void quicksort(int array[], int start, int end)
{
  if (start < end)
  {
    int pivot_point = partition(array, start, end); // gets the pivot point

    quicksort(array, start, pivot_point - 1);
    quicksort(array, pivot_point + 1, end);
  }
}


void quicksort(int array[], int len) // called in main
{
  quicksort(array, 0, len - 1);
}


int main(int argc, char* argv[])
{
  int array[6] = {2,4,5,6,1,9};
  for (int i : array) {std::cout << i << " ";}
  std::cout << "\n" << "\n";

  quicksort(array, 6);
  for (int i : array) {std::cout << i << " ";}
}

























void quicksort(int array[], int n)
{
  quicksort(array, 0, n - 1);
}
void quicksort(int array[], int start, int end)
{
  if (start < end)
  {
    int pivot_point = partition(array, start, end);

    quicksort(array, start, pivot_point - 1);
    quicksort(array, pivot_point + 1, end);
  }
}
int partition(int array[], int start, int end)
{
  int mid = (start + end) / 2;

  std::swap(array[start], array[mid]);

  int pivot_value = array[start];
  int pivot_index = start;
  int scan = start + 1;

  while (scan <= end)
  {
    if (array[scan] < pivot_value)
    {
      pivot_index++;
      std::swap(array[pivot_index], array[scan]);
    }
    scan++;
  }
  std::swap(array[start], array[pivot_index]);
  return pivot_index;
}
