#include <cstring>

int index_of(const char* s, char c)
{
  int size = strlen(s);

  for (int i = 0; i <= size; i++)
    if (s[i] == c)
      return i;
  return -1;
}
