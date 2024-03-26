#include <utility>
#include <vector>
bool windback(int a[], int b[], int len, int num_steps) {

  if (len < 1 || num_steps < 0)
    return false;

  std::vector<int> temp(len);
  for (int i = 0; i < len; i++) {temp[i] = a[i];}

  while (num_steps > 0) {
    for (int i = 0; i < len; i++) {
      std::swap(temp[i], temp[len - 1]);
    }
    num_steps--;
  }

  for (int i = 0; i < len; i++) {
    b[i] = temp[i];
  }
  return true;
}
