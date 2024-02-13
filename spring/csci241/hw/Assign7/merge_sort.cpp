#include <vector>
#include <iomanip>
#include <iostream>


void merge(double[], int, int, int);
void merge_sort(double array[], int start, int end);

/**
 * Reads a series of doubles from the standard input stream using cin.
 * Adds to the array untill the end of input is reached.
 *
 * @param array: an double array
 *
 * @return The number of elements in the array
 */
int build_array(double array[])
{
  int i = 0;  
  
  while (std::cin >> array[i++]) // loops untill the end of input is reached
                                 // Also increments i after read.
    ;

  return i - 1;
}
/**
 * Prints the elements in the array using the setw function to allign the output
 *
 * @param array: an array of doubles
 * @param n: the number of elements stored in the array
 *
 */
void print_array(double array[], int n)
{
  int i;
  for (i = 0; i < n; i++)
  {
    std::cout << std::setw(8) << std::fixed << std::setprecision(2) << array[i];

    if ((i + 1) % 8 == 0) // prints mewline after 8 numbers are printed
      std::cout << '\n';
  }
  if (i % 8 != 0) // checks if we need a final newline
    std::cout << '\n';
}
/**
 * Wrapper function that calls the function merge_sort to begin the sorting process
 *
 * @param array: an array of doubles
 * @param n: the size of the array
 */
void merge_sort(double array[], int n)
{
  merge_sort(array, 0, n - 1); // call to recursive function
}
/**
 * Recursivly calls itself in order to divide the array into smaller subarrays, 
 * It then calls the merge function which merges the arrays into its sorted form.
 * 
 * @param array: the array of doubles
 * @param start: the beginning of the array
 * @param end: the end of the array
 *
 */
void merge_sort(double array[], int start, int end)
{
  if (start < end) // Base case
  {

    int mid = (start + end) / 2; // Calculates the middle index
    
    merge_sort(array, start, mid); // divides the left portion
    merge_sort(array, mid + 1, end); // divides the right portion

    merge(array, start, mid, end); // merges arrays
  }
}
/**
 * Merges the arrays in a sorted fashion.
 *
 * @param array: the array of doubles
 * @param start: the beginning of the array
 * @param mid: the middle index, used as the end of the left array
 * @param end: the end of the array
 *
 */
void merge(double array[], int start, int mid, int end)
{
  // Creates a temp array
  std::vector<double> temp(end - start + 1);

  int i = start; // Points to the beginning of the left array
  int j = mid + 1; // points to the beginning of the right array
  int k = 0; // Indexs through the temp array

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
  for (int i = 0; i < (int)temp.size(); i++)
    array[start + i] = temp[i];
}
