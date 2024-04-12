#include <cstdlib>
#include <vector>
int last_int_standing(size_t n, size_t step) {
std::vector<int> vec;

for (size_t i = 1; i <= n; i++) {vec.push_back(i);}

int last_int = vec[0];
int index = 0;
bool dont_move;
for (size_t j = n; j > 0; j--) {
  if ((last_int - 1 + step) > (size_t)vec.size()) {

    size_t steps_remaining = step;

    while (steps_remaining > 0) {
      if (index == (int)vec.size() - 1) { // if index at end of vector
        index = 0; // reset back to first number
        steps_remaining--;
      }
      while (index < (int)vec.size() - 1 && steps_remaining > 0) {
        if (dont_move) {
          steps_remaining--;
          dont_move = false;
        }
        else {
        index++;
        steps_remaining--;
        }
      }
    }
    last_int = vec[index];
    vec.erase(vec.begin() + index);
    if ((int)vec.size() == 1) { return vec[0];}
    (index == 0) ? dont_move = true : index--;

  }
  else {
    index += step;
    last_int = vec[index];
    vec.erase(vec.begin() + index);
    if ((int)vec.size() == 1) { return vec[0];}
    (index == 0) ? dont_move = true : index--;
  }
}
return last_int;
}
