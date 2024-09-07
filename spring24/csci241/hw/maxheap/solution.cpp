bool is_max_heap(int a[], int n) {

  int child_left, child_right;

  for (int i = 0; i < n; i++) {

    child_left = (2 * i) + 1;
    child_right = (2 * i) + 2;

    if (child_left < n) {
      if (a[child_left] >= a[i]) {
        return false;
      }
    }
    if (child_right < n) {
      if (a[child_right] >= a[i]) {
        return false;
      }
    }
  }
  return true;
}
// int a2[] = {5, 3, 4, 2, 1}; // is a max heap
//
//
