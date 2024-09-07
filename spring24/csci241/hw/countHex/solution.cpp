#include <string>

char getHex(int n) {
  switch (n) {
    case 10:
      return 'A';
      break;
    case 11:
      return 'B';
      break;
    case 12:
      return 'C';
      break;
    case 13:
      return 'D';
      break;
    case 14:
      return 'E';
    case 15:
      return 'F';
    default:
      return 'R';
      break;
  }
}

int count_hex_a(int n) {
  if (n < 0)
    return -1;

  int count{0};
  std::string str = "";

  for (int i = n; i > 0; i/=16) {
    int temp = i % 16;
    if (temp < 10) {
      str+= (char)temp;
    } else {
        str+= getHex(temp);
      }
  }

  for (int i = 0; i < (int)str.length(); i++) {
    if (str[i] == 'A')
      count++;
  }

  return count;
}
