#include <cstdlib>
int last_int_standing(size_t n, size_t step) {
  size_t j = 1;

  for (int i = n; i > 0; i--) {

    if (j + step > n) {

      int steps_remaining = step;

      while (steps_remaining > 0) {
        if (j == n) {
          j = 1;
          steps_remaining--;
        }
        while (j < n && steps_remaining > 0) {
          steps_remaining--;
          j++;
        }
      }
    }

    else {
      j+= step;
    }

  }

 return j;
}

