//***************************************************************************
//
//  insertion_sort.cpp
//  CSCI 241 Assignment 1
//
//  Created by Matt Warner (z2004200)
//
//***************************************************************************
#include <iostream>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::setprecision;
using std::setw;
using std::fixed;

/**
 * fills the array with elements using input from the user
 *
 * @param array: An array of doubles
 * 
 * @return count: The number of elements passed into the array
 */
int build_array(double array[])
{
  int count = 0;

  while (cin >> array[count])
  {
    count++;
  }
  return count;
}
/**
 * prints the elements in the array
 * 
 * @param array: An array of doubles
 * @param n: The number of elements in the array
 *
 */
void print_array(double array[], int n)
{
  int i;

  for (i = 0; i < n; i++)
  {
    cout << setw(8) << fixed << setprecision(2) << array[i];

    if ((i+1) % 8 == 0)
    {
      cout << endl;
    }
  }
  if (i % 8 != 0){
    cout << endl;
  }
}
/**
 * Sorts array in acending order
 *
 * @param array: An arary of doubles
 * @param n: The size of the array
 *
 * @Note: Uses insertion_sort to sort the array
 */
void insertion_sort(double array[], int n)
{
  for (int i = 1; i < n; i++)
  {
    for (int j = i; j > 0 && array[j-1] > array[j]; j--)
    {
      // swap elements
      double temp = array[j];
      array[j] = array[j-1];
      array[j-1] = temp;
    }
  }
}
