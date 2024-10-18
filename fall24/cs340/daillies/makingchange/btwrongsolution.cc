#include <algorithm>
auto r_mintokens(int c, int a[], int start, int len) -> int {
    int counter = 0;
    if (start == len && c != 0) {
        return -1;
    } 
    if (c == 0) { return counter; }
    for (int i = start; i < len; ++i) {
        int tmp = 0;
        if (c >= a[i]) {
            ++counter;
        if ((tmp = r_mintokens(c - a[i], a, i, len)) != -1) {
            return counter +tmp;
        } }
        (tmp == -1) ? --counter : tmp = 0;
    } return -1;
}
auto mintokens(int c, int a[], int len) -> int {
    if (len < 1 || c < 1)  {return -1; }
    std::sort(a, a + len, [](const auto& a, const auto &b) { return a > b; });
    return r_mintokens(c, a, 0, len);
}
int main() {
    int a[4] = {5,9,1,6};
    mintokens(11, a, 4);
}
