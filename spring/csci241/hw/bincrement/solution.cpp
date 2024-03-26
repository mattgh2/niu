#include <cstdlib>

void binary_increment(int a[], int len) {
  (a[len -1] == 0) ? (a[len-1] = 1) : ((a[len - 1] = 0), (a[len - 2] = 1));
}
