

#include <iostream>
#include <iomanip>

int build_array(int array[]){

    int count = 0;

    for (int i = 0; i < 1000; i++)
    {
        if (std::cin >> array[i])
        {
            std::cin >> array[i];
            count++;
        }
        else
        {
            break;
        }

    }

    return count;
}

void print_array(int array[], int n){

    for (int i = 0; i < n; i++)
    {
        if (i != 0 && i % 8 == 0)   // prints newline in intervals of 8
        {
            std::cout << std::endl;
        }

        std::cout << std::right << std::setw(8) << array[i];    // Printing elements in array

    }

    std::cout << std::endl;    //final newline
}

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
        
        temp = array[i];
        array[i] = array[min_index];
        array[min_index] = temp;
        
    }
}
