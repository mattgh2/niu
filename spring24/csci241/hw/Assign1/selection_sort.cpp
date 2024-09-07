//***************************************************************************
//
//  selection_sort.cpp
//  CSCI 241 Assignment 1
//
//  Created by Matt Warner (z2004200)
//
//***************************************************************************
#include <iostream>
#include <iomanip>

/**
 * Fills an array with input from the user
 *
 * @param an integer array
 *
 * @return the number of elements added to the array
 */
int build_array(int array[]){

    int count = 0;

    while (std::cin >> array[count])
    {
        count++;
    }

    return count;
}
/**
 * Prints the elements in the array
 *
 * @param an integer array
 * @param the number of elements in the array
 *
 */
void print_array(int array[], int n){
    int i;
    for (i = 0; i < n; i++)
    {
        if (i != 0 && i % 8 == 0)   // prints newline ever 8th iteration
        {
            std::cout << std::endl;
        }

        std::cout << std::right << std::setw(8) << array[i];    // Printing elements in array

    }
    if (i % 8 != 0){
        std::cout << std::endl;    // final newline
    }
}
/**
 * Implements selection sort to sort the array in acending order
 *
 * @param array: an array of integers
 * @param n: the number of elements in the array
 */
void selection_sort(int array[], int n){

    int min_index;
    int temp;

    for (int i = 0; i < n - 1; i++)
    {
        min_index = i;

        for (int j = i + 1; j < n; j++)
        {
            if (array[j] < array[min_index])
            {
                min_index = j;
            }
        }
        // swap 
        temp = array[i];
        array[i] = array[min_index];
        array[min_index] = temp;
        
    }
}
