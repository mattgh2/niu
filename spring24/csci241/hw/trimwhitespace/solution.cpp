#include <cctype>

char* trim(char* destination, const char* source)
{
  int i = 0, k = 0;
  while (source[i] != '\0')
  {
    if (isalpha(source[i])) {
      destination[k] = source[i];
      i++;
      k++;
    }
    else if (i > 0 && (isspace(source[i]) && (isalpha(source[i - 1]) && isalpha(source[i+1])))) {
      destination[k] = source[i];
      i++;
      k++;
    }
    else
      i++;
  }
  destination[k] = '\0';
  return destination;
}
