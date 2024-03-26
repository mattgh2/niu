//
//  quiz5.cpp
//

#include <cstdlib>
#include <iostream>

using std::cin;
using std::cout;

const int ARRAY_SIZE = 30;

void fill(int[], int);
void shuffle(int[], int);

int main()
{
    int array[ARRAY_SIZE];
    int seed;
    
    cout << "Seed value? ";                 // Line 21
    cin >> seed;                            // Line 22
    srand(seed);                            // Line 23
    
    fill(array, ARRAY_SIZE);                // Line 25
    
    shuffle(array, ARRAY_SIZE);             // Line 27
    
    return 0;
}

void fill(int array[], int size)
{
  int index;

  // Place random values at random locations in the array
  for (int i = 0; i < 10 * size; i++)
    {
        index = rand() % size;              // Line 39
        array[index] = rand();              // Line 40
    }
}

void shuffle(int array[], int size)
{
    int* first, * second;
    
    for(int j = 0; j < 5 * size; j++)
    {
        // Pick a random pair of positions to swap
        first  = array + rand() % size;     // Line 51
        second = array + rand() % size;     // Line 52
        
        // Swap
        int temp = *first;                  // Line 55
        *first = *second;                   // Line 56
        *second = temp;                     // Line 57
    }
}
