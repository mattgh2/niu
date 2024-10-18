#include <vector>
#include <numeric>
// combinations of that sum to c. (with repeats)
auto _r(int c, int a[], int start, std::vector<int> &cur, std::vector<std::vector<int>> &sol, int N) {
    if (c == 0) { sol.push_back(cur); }
    if (c < 0) { return; }
    for (int i = start; i < N; ++i) {
        cur.push_back(a[i]);
        _r(c - a[i], a, i, cur, sol, N);
        cur.pop_back();
    }
}
auto mintokens(int c, int a[], int len) -> int {
    if (len < 1 || c < 1)  {return -1; }
    std::vector<int> h;
    std::vector<std::vector<int>> k;
    _r(c, a, 0, h,k, len);
    if (k.size() == 0) {return -1 ;}
    return std::accumulate(k.begin() + 1, k.end(), (*k.begin()).size(), [](auto a, const auto &b) {
                if (b.size() < a)  { return b.size(); }
                return a; }); 
}
