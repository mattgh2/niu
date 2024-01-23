#include <iostream>

void print_primes(int limit , int d)
{
  int lastDigit;

  for (int i = 2; i < limit; i++)
  {
    bool prime = true;

    for (int j = 2; j < i; j++)
    {
      if (i % j == 0)
      {
        prime = false;
        break;
      }
    }
    if (prime)
    {
      lastDigit = i % 10;
      if (lastDigit != d)
      {
        std::cout << i << " ";
      }
    }
  }
  std::cout << std::endl;
}
