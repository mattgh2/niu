#include <map>

bool same_digits(int a, int b) {
  std::map<int,int> map_a, map_b;

  for (int i = a; i > 0; i/=10) {
    map_a[i%10]++;
  }
  for (int i = b; i > 0; i/=10) {
    map_b[i%10]++;
  }

  std::map<int,int>::iterator it_a = map_a.begin();
  std::map<int,int>::iterator it_b = map_b.begin();
  // if (map_a.size() != map_b.size()) {
  //   return false;
  // } &&se {

    while (it_a != map_a.end() && it_b != map_b.end()) {
      if (it_a-> first != it_b->first)  {
        return false;
    }
      it_a++;
      it_b++;
  // }
  }
  return true;
}
