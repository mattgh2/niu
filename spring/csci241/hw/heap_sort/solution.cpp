#include <utility>

void sift_down(int[], int, int);
void heapify(int[], int);
void heap_sort(int[], int);


void heap_sort(int array[], int n)
{
  heapify(array,n);

  int end = n - 1;

  while (end > 0)
  {
    std::swap(array[end], array[0]);

    end--;

    sift_down(array,0, end);
  }
}

void heapify(int array[], int n)
{
  int start = (n - 2) / 2;    // Find parent of last element
 
  while (start >= 0)
  {
    sift_down(array, start, n - 1);

    start--;
  }
}

void sift_down(int array[], int start, int end)
{
  int root = start;

  while ((2 * root + 1) <= end)
  {
    int child = 2 * root + 1; 
    int largest = root;

    if (array[largest] < array[child])
    {
      largest = child;
    }
    if ((child + 1) <= end && (array[largest] < array[child + 1]))
    {
      largest = child + 1;
    }
    if (largest == root)
    {
      return;
    }
    else
    {
      std::swap(array[root], array[largest]);
      root = largest;
    }
  }
}
