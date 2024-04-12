#include <string>
#include <utility>
#include <unordered_map>

std::string reverse(std::string hex) {
  for (int i = 0, j = (int)hex.length() -1; i <= j; i++, j--) {
    std::swap(hex[i], hex[j]);
  }
  return hex;
}

int reverse_hex(int n) {
  if (n < 0) { return -1;}

  int solution = 0;
  std::unordered_map<int, char> mp;
  mp[10] = 'A', mp[11] = 'B', mp[12] = 'C', mp[13] = 'D', mp[14] = 'E', mp[15] = 'F';
  std::string str = "";

  for (int i = n; i > 0; i/=16) {
    int temp = i % 16;
    if (temp < 10) {
      str+= (char)('0' + temp);
    } else {
        str+= mp[temp];
      }
  }

  std::string reversed_hex = reverse(str);

  for (char _char : reversed_hex) {
    if (isalpha(_char)) {
      std::unordered_map<int, char>::iterator it = mp.begin();
      while (it != mp.end()) {
        if (it->second == _char) {
          solution+= it->first;
          break;
        }
        it++;
      }
    }
    else {
      solution+= _char - '0';
    }
  }
  return solution; 
}
