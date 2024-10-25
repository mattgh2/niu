#include <vector>
// #include <iostream>
#include <algorithm>

template <typename it>
auto next(std::vector<std::vector<int>> &m, it &iterator, size_t row) -> it {
    auto tmp(iterator);
    iterator = m[row].begin();
    return tmp;
}
template <typename it>
auto next_reverse(std::vector<std::vector<int>> &m, it &iterator, size_t row) -> it {
    auto tmp(iterator);
    iterator = m[row].rbegin();
    return tmp;
}
auto RotatingCornerSpiral(std::vector<std::vector<int>> &m) -> std::vector<int>{
    std::vector<int> v;
    if (m.size() != m.begin()->size()) {
        return {};
    }
    if (m.empty()) {
        return {};
    }
    if (m.size() == 1) {
        v.push_back(*m.begin()->begin());
        return v;
    }
    std::vector<int>::const_iterator top_row = m[0].begin();
    std::vector<int>::const_reverse_iterator bottom_row = (m.end() - 1)->rbegin();
    std::vector<int>::const_reverse_iterator right_col = m[0].rbegin();
    std::vector<int>::const_iterator left_col = (m.end()-1)->begin();

    int row = 1;
    while (top_row != m[0].end() - 1) {
        v.push_back(*top_row++);
        v.push_back(*next_reverse(m,right_col,row));
        v.push_back(*bottom_row++);
        v.push_back(*next(m, left_col, (m.size() -1) - row));
        ++row;
    }
    m.erase(m.begin());
    m.erase(m.end() - 1);
    std::for_each(m.begin(), m.end(), [](auto &a) { a.erase(a.begin()); a.erase(a.end() - 1); });
    std::vector<int> next_square_elements = RotatingCornerSpiral(m);
    v.insert(v.end(), next_square_elements.begin(), next_square_elements.end());

    return v;
}
// int main () {
//     // std::vector<std::vector<int>> m = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16}};
//     std::vector<std::vector<int>> m = {{1,2,3}, {4,5,6}, {7,8,9}};
//     
//     std::vector<int> v = RotatingCornerSpiral(m);
//     for (const auto &i : v) { std::cout << i << ' '; }
//
// }
