#include <cstring>
#include <iostream>

int last_index_of(const char* s, char c)
{
  int n = strlen(s), i;

  for (i = n - 1; i >= 0; i--)
  {
    if (s[i] == c)
      return i;
  }
  return -1;
}
