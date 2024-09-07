#include <string>

using std::string;

int roman_to_decimal(const string& roman_value)
{
  int value = 0;
  for (int i = 0; i < (int) roman_value.length(); i++)
  {
    switch (roman_value[i])
    {
      case ('I'):
        value+=1;
        break;
      case ('V'):
        if (i > 0 && roman_value[i - 1] == 'I')
        value+= 3;
        else
          value+= 5;
        break;
      case ('X'):
        if (i > 0 && roman_value[i-1] == 'I')
          value+= 8; 
        else
          value+=10;
        break;
      case ('L'):
        if (i > 0 && roman_value[i-1] == 'X')
          value+= 30;
        else
          value+= 50;
        break;
      case ('C'):
        if (i > 0 && roman_value[i-1] == 'X')
          value+=80;
        else
          value+=100;
        break;
      case ('D'):
        if (i > 0 && roman_value[i-1] == 'C')
          value+= 300;
        else
          value+= 500;
        break;
      case ('M'):
        if (i > 0 && roman_value[i-1] == 'C')
          value+= 800;
        else
          value+= 1000;
        break;
    }
  }
  return value;
  }

// subtraction notation: IX (9) | IV(4) | XL (40), XC (90 ) | CD (400) | CM (900)
