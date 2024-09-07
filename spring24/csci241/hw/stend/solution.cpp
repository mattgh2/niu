#include <sstream>
#include <vector>
#include <cstring>
bool ends_with(const char* s, const char* suffix) {

  std::vector<std::string> vec; 
  std::stringstream ss(s);
  std::string word;

  while (ss >> word) {
    vec.push_back(word);
  }
  
  std::string back = vec[(int)vec.size() - 1];
  int b_size = back.length();
  int s_size = strlen(suffix);

  if (strlen(suffix) > back.length()) {
    return false;
  } else {
    int dif = b_size - s_size;
    for (int i = dif, j = 0; i < b_size; i++, j++) {
      if (back[i] != suffix[j]) {
        return false;
      }
  }
  }
  return true;
}

