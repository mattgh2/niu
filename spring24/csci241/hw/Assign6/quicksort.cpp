#include <iostream>
#include <iomanip>
#include <utility> // has the swap function 

// For the compiler
int partition(int[], int, int);
void quicksort(int[], int, int);

/**
 * Reads a series of integers from the standard input stream using cin.
 * Adds to the array untill the end of input is reached.
 *
 * @param array: an integer array
 *
 * @return The number of elements in the array
 */
int build_array(int array[])
{
  int i = 0;
  
  while (std::cin >> array[i++]) // loops until the end of input is reached, 
  ;                              // also increments i after read
  return i - 1; // element count
}
/**
 * Prints the elements in the array using the setw function to allign the output
 *
 * @param array: an array of integers
 * @param n: the number of elements stored in the array
 *
 */
void print_array(int array[], int n)
{
  int i;
  for (i = 0; i < n; i++)
  {
    std::cout << std::setw(8) << array[i];

    if ((i+1) % 8 == 0) // prints newline after 8 numbers are printed
      std::cout << std::endl;
  }
  if (i % 8 != 0) // checks if we need a final newline
    std::cout << std::endl;
}
/**
 * wrapper function that calls the recursive function that begins to sort the array.
 * 
 * @param array: our array of integers
 * @param n: the number of elements in the array
 *
 */
void quicksort(int array[], int n)
{
  quicksort(array, 0, n - 1);
}
/**
 *  Functions that recursivly calls itself to partition the array into smaller subsets, 
 *  rearranging the array untill the array is full fully sorted
 *
 *  @param array: an array of integers
 *  @param start: the arrays starting point
 *  @param end: the arrays ending point
 *
 */
void quicksort(int array[], int start, int end)
{
  if (start < end) // base case
  {
  // Partitions the array and returns the pivot point
  int pivot_point = partition(array, start, end); 
  
  // Recursive calls to rearrange the smaller subsets of the array
  quicksort(array, start, pivot_point - 1);
  quicksort(array, pivot_point + 1, end);
  }
}
/**
 * Choose a pivot point and rearranges the array such that the pivot point
 * is in its final sorted position. Array gets split into smaller subsets based on the position
 * of the pivot point
 *
 *
 * @param array: an array of integers
 * @param start: the arrays starting point
 * @param end: the arrays ending point
 *
 * @return pivot_point, the point that is in its final sorted position.
 */
int partition(int array[], int start, int end)
{
  int mid = (start + end) / 2; // middle of the array
 
  // swap array[start] and array[mid]
  std::swap(array[start], array[mid]);

  int pivot_index = start;
  int pivot_value = array[start];

  int scan = start + 1; // runs through the array, comparing each element to the pivot

  while (scan <= end)
  {
    if (array[scan] < pivot_value)
    {
      // increments pivot_index then swap array[pivot_index] with array[scan]
      pivot_index++;
      std::swap(array[pivot_index], array[scan]);
    }
    scan++;
  }
  // swap array[pivot_index] with array[start]
  std::swap(array[pivot_index], array[start]);

  return pivot_index;
}
