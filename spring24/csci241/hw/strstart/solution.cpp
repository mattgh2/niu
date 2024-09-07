#include <sstream>
#include<cstring>
bool starts_with(const char* s, const char* prefix) {

  std::stringstream ss(s);
  std::string first;
  ss >> first;

  if (strlen(prefix) > first.length()) {
    return false;
  }
  else {
    int dif = first.length() - strlen(prefix);
    for (size_t i = 0; i < first.length() - dif; i++) {
      if (first[i] != prefix[i]) {
        return false;
      }
    }
  }

  return true;
}
