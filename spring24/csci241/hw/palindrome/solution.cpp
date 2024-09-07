#include <cctype>
#include <string>
using std::string;

bool ispalindrome(const string& s)
{
  string newstring = "";
  for (int i = 0; i < (int)(s.length());i++)
  {
    if (isalnum(s[i]))
      newstring+= tolower(s[i]);
  }

  int i = 0;
  int j = (int)(newstring.length()) - 1;

  while (i <= j)
  {
    if (newstring[i] != newstring[j])
      return false;

    i++;
    j--;
  }

  return true;
}

