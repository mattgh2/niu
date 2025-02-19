#include <vector>
#include <set>

struct size_comp {
    bool operator()(const std::vector<int> &a, const std::vector<int> &b) const {
        return a.size() < b.size();
    }
};
auto _r(int c, int a[], int start, std::vector<int> cur, int N) -> std::set<std::vector<int>, size_comp> {
    std::set<std::vector<int>, size_comp> s;
    if (c == 0) { s.insert(cur); return s; }
    if (c < 0) { return {}; }

    for (int i = start; i < N; ++i) {
        cur.push_back(a[i]);
        auto below = _r(c - a[i], a, i, cur, N);
        s.insert(below.begin(), below.end());
        cur.pop_back();
    }
    return s;
}

auto mintokens(int c, int a[], int len) -> int {
    if (len < 1 || c < 1)  { return -1; }
    auto solution = _r(c, a, 0, {}, len);
    if (solution.empty()) { return -1 ;}
    int _size =  (*solution.begin()).size();
    return _size;
}
