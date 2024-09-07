//***************************************************************************
//
//  bubble_sort.cpp
//  CSCI 241 Assignment 3
//
//  Created by Matt Warner (z2004200)
//
//***************************************************************************
#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::string;
/**
 * Fills the array with strings from user input
 *
 * @param array: an array of strings
 *
 * @return count: the number of elements added to the array
 */
int build_array(string array[])
{
  int count = 0;

  while (cin >> array[count])
  {
    count++;
  }
  return count;
}
/**
 * Prints each element in the array
 *
 * @param array: an array of strings
 * @parma n: The number of elements in the array
 *
 */
void print_array(string array[], int n)
{
  int i;

  for (i = 0; i < n; i++)
  {
    cout << std::setw(8) << std::left << array[i]; 

    if ((i+1) % 8 == 0)
    {
      cout << endl;
    }
  }
  if (i % 8 != 0)
    cout << endl;
}
/**
 * Sorts the array in accending order
 *
 * @param array: An array of strings
 * @param n: The amount of elements in the array
 *
 * Note: Created a while loop that checks if the two characters being compared are the same, while true, we move to the next character in the strings.
 */
void bubble_sort(string array[], int n)
{
  int i;
  bool swapped; 

  do {

    swapped = false;
    i = 1;

    while (i < n)
    {
      string currentString = array[i];
      string leftString = array[i-1];
      int chartocompare = 0; // index of the strings

      while (leftString[chartocompare] == currentString[chartocompare]) 
      {
        chartocompare++; // moves to next index
      }
      if ((int)leftString[chartocompare] > (int)currentString[chartocompare])
      {
        // swap
        string temp = array[i];
        array[i] = array[i-1];
        array[i-1] = temp;
        swapped = true;
      }
      i++;
    }
    n--;

  } while (swapped);
}
