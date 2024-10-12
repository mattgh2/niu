#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>

[[nodiscard]]
auto next(const std::vector<std::pair<int,int>> &v) -> std::vector<std::pair<int,int>> {
    return std::vector<std::pair<int,int>>(v.begin() + 1, v.end());
}
[[nodiscard]]
auto insert(std::vector<std::pair<int,int>> v, const std::pair<int,int> pair) -> std::vector<std::pair<int,int>> {
    v.push_back(pair);
    return v;
}
auto validate_stack(std::vector<std::pair<int,int>> stack) -> bool {
    if (stack.empty()) { return false; }
    else if (stack.size() == 1) { return true; }

    auto acc = *(stack.begin());
    for (auto it = stack.begin() + 1; it < stack.end(); ++it) {
        if (acc.first <= it->first || acc.second <= it->second) {
            return false;
        }
        acc = *it;
    }
    return true;
}

auto _r(std::vector<std::pair<int,int>> up, std::vector<std::pair<int,int>> p, std::vector<std::pair<size_t,std::pair<int,int>>> &solution) { 
    
    if (up.empty()) { 
        if (validate_stack(p)) {
            size_t _stack_height = std::accumulate(p.begin(), p.end(), 0, [](size_t init, std::pair<int,int> pair){ return init + pair.second; });
            solution.emplace_back(_stack_height, p.back());
        }
        return;
    }

    _r(next(up), insert(p, up[0]), solution);
    _r(next(up), p, solution);

}
auto buildHanoiTower(const std::vector<std::pair<int,int>> &v, int &height, int &index) {
    std::vector<std::pair<int,int>> sorted(v);
    std::sort(sorted.begin(), sorted.end(), [](const auto &i, const auto& j) {
                if (i.first == j.first) {
                    return i.second > j.second;
                } else { return i.first > j.first; }
            });
    std::vector<std::pair<size_t,std::pair<int,int>>> all_stacks;
    _r(sorted, {}, all_stacks);

    auto largest_stack = *(std::max_element(all_stacks.begin(),all_stacks.end(), [](const auto &i, const auto &j) {
               return i.first < j.first; }));

    height = largest_stack.first;
    auto it = std::find(v.begin(), v.end(), largest_stack.second);
    index = std::distance(v.begin(), it);
}
