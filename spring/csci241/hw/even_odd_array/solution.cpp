#include <vector>

bool isEven(int x)
{
  return (x % 2 == 0) ? true : false;
}

void even_odd(int a[], int b[], int len)
{
  if (len == 1)
  { 
    b[0] = a[0];
    return;
  }

  int evenCount = 0; 
  int oddCount = 0;
  int j = 0;

  std::vector<int> evens;
  std::vector<int> odds;

  for (int i = 0; i < len; i++)
  {
    if (isEven(a[i]))
    {
      evens.push_back(a[i]);
      evenCount++;
    }
    else
    {
      odds.push_back(a[i]);
      ++oddCount;
    }
  }

  int count = 0;

  // fill b[] with even numbers
  while (count <= evenCount)
  {
      b[j] = evens[count];
      count++;
      if (j + 2 < len)
        j+=2;
      else
        j++;
  }
  // fill b[] with odds
  count = 0; 
  j = 1;
  while (count <= oddCount)
  {
    b[j] = odds[count];
    count++;
  if (j + 2 < len)
    j+=2;
  else
    j++;
  }
}
