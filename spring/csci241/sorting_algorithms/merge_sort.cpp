#include <vector>

int merge_sort(int array[], int n)
{
  merge_sort(array, 0, n - 1)
}

void merge_sort(int array[], int start, int end)
{
  if (start < end)
  {
    int mid = (low + high) / 2;
    merge_sort(array, start, mid);
    merge_sort(array, mid + 1, end);

    merge()
  }
}
void merge(int array[], int start, int mid, int end)
{
  //creates a temp vector
  std::vector<int> temp(end - start + 1);

  int i = start; // points to the beginning of the left array
  int j = mid + 1; // points to the beginning of the right array
  int k = 0; // indexs through temp
  
  while (i <= mid && j <= end)
  {
    // element in the left array is smaller
    if (array[i] < array[j])
    {
      temp[k] = array[i]; // add element from the left array to temp
      i++; // increment index
    }
    else // element on the right is smaller
    {
      temp[k] = array[j]; // add element to temp
      j++; // increment index
    }
    k++; // increment temp array index
  }
   /*
    * One of the arrays still has elements that need to be added
    * One of these while loops will be executed, depending on which pointer
    * has not reached the end of the array
   */ 
  while (i <= mid)
  {
    temp[k] = array[i];
    i++;
    k++;
  }
  while (j <= end)
  {
    temp[k] = array[j];
    j++;
    k++;
  }

  // copys the elements from temp array to main array.
  for (int i = 0; i < static_cast<int>(temp.size());i++)
    array[start + i] = temp[i];
}









void mergesort(int array[], int n) // Wrapper Func
{
  mergesort(array, 0, n - 1);
}
void mergesort(int array[], int start, int end)
{
  int mid = (start + end) / 2;

  mergesort(array, start, mid);
  mergesort(array, mid + 1, end);

  merge(array, start, mid, end);
}

void merge(int array[], int start, int mid, int end)
{
  std::vector<int> temp(end - start + 1)

  int i = start;
  int j = mid + 1;
  int k = 0;

  while (i <= mid && j <= end)
  {
    if array[i] < array[j]
    {
      temp[k] + array[i];
      i++;
    }
      
    else
    {
      temp[k] = array[j];
      j++;
    }
    k++
  }
  while (i <= mid)
  {
    temp[k] = array[i];
    i++
    k++
  }
  while (j <= end)
  {
    temp[k] = array[j];
    j++
    k++
  }
  for (int i = 0; i < static_cast<int>(temp.size());i++)
  {
    array[start + i] = temp[i];
  }
}

























void mergesort(int array[], int n)
{
  mergesort(array, n-1);
}
void mergesort(int array, int start,int end)
{
  int mid = (start + end) / 2;

  mergesort(array, start, mid);
  mergesort(array, mid + 1, end);

  merge(array, start, mid, end);
}
void merge(int array, int start, int mid, int end)
{
  std::vector<int> temp(end - start + 1);

  int i = start;
  int j = mid + 1;
  int k = 0;

  while (i <= mid && j <= end)
  {
    if (array[i] < array[j])
    {
      temp[k] = array[i];
      i++;
    }
    else
    {
      temp[k] = array[j];
      j++
    }
    k++
  }
  while (i <= mid)
  {
    temp[k] = array[i];
    i++;
    k++;
  }
  while (j <= end)
  {
    temp[k] = array[j];
    j++;
    k++;
  }
  for (int i = 0; i < static_cast<int>(temp.size());i++)
  {
    array[start + i] = temp[i];
  }
}


void mergesort(int array[], int n) {
  mergesort(array, 0, n - 1);
}
void mergesort(int array[],int start, int end) {
  if (start < end)
  {
    int mid = (start + end) / 2; 
    mergesort(array, start, mid);
    mergesort(array, mid + 1, end);

    merge(array, start, mid, end);
  }
}
void merge(int array, int start, int mid, int end);
{
  std::vector<int> temp(end - start + 1);

  int i = 0;
  int j = mid +1;
  int k = 0;

  while (i <= mid && j <= end)
  {
    if (array[i] < array[j])
    {
      temp[k] = array[i];
      i++
    }
    else
    {
      temp[k] = array[j];
      j++
    }
    k++
  }
  while (i <= mid)
  {
    temp[k] = array[i];
    i++;
    k++;
  }
  while (j <= end)
  {
    temp[k] = array[j];
    j++;
    k++;
  }
  for (int i = 0; i < static_cast<int>(temp.size()); i++)
  {
    array[start + i] = temp[i]
  }
}





