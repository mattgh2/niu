#include <vector>
using std::size_t;

bool is_stepnum(int x) {
  std::vector<int> vec;
  if (x < 0) 
    x*=-1;
  for (int i = x; i > 0; i/=10) {
    vec.push_back(i % 10);
  }
  for (int i = 0; i < (int)(vec.size()) - 1; i++) {
    if (!((vec[i] + 1 == vec[i+1]) || (vec[i] - 1 == vec[i+1]))) {
      return false;
    }
  }
  return true;
}

int max_stepnum(int n) { 
  int max_step = 0;
  if (n >= 0) {
    for (int i = 0; i <= n; i++) {
      if (is_stepnum(i) && i > max_step) {
        max_step = i;
      }
    } 
  } else {
      for (int i = n - 1; ; i--) {
        if (is_stepnum(i)) {
          return i;
        }
      }
    }
  return max_step;
}
