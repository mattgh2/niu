#include <iostream>
#include <utility>
void bubblesort(int[], int);
int main(int argc, char* argv[])
{
  int array[8] = {2,7,5,3,6,8,1,4};

  for (const auto& num : array) std::cout << num << " ";
  std::cout << '\n';
  bubblesort(array, 8);
  for (const auto& num : array) std::cout << num << " ";

}

void bubblesort(int array[], int n)
{
  bool swapped;
  do {
    swapped = false;
    int i = 1;
    while (i < n)
    {
      if (array[i - 1] > array[i])
      {
        std::swap(array[i-1], array[i]);
        swapped = true;
      }
      i++;
    }
    n--;
  } while (swapped);
}
