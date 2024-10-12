#include <vector>
#include <algorithm>
#include <limits>
#include <numeric>
#include <iostream>
auto _f(const std::vector<std::pair<int,int>> &v, std::vector<std::pair<int,int>> &c, size_t start, size_t k, std::vector<std::pair<int,int>> &solution, int radius = 0, int height = 0) -> void {

    if (k == 0 ) {

        for (const auto &i : c) {std::cout << "{ " << i.first << ", " << i.second << " }"; }
        std::cout << "\n";

        size_t stack_height = std::accumulate(c.begin(),c.end(), 0, [](auto init, auto pair){
                    return init + pair.second;
                });
        solution.emplace_back(stack_height, start - 1);
    }

    for (size_t i = start; i < v.size(); ++i) {
        
        if (c.empty()) {
            k = v.size() - i ;
            radius = height = std::numeric_limits<int>::max();

        }
        bool added = false;
        if (v[i].first < radius && v[i].second < height) {
            c.push_back(v[i]);
            radius = v[i].first;
            height = v[i].second;
            added = true; 
        }
        
        _f(v, c, i + 1, k - 1, solution, radius, height);

        if (added) { c.pop_back(); added = false; }
    }
}

void buildHanoiTower(const std::vector<std::pair<int,int>> & v, int &height, int &index) {
     
    std::vector<std::pair<int,int>> sorted(v);
    std::sort(sorted.begin(), sorted.end(), [](const auto& i, const auto &j) {
                if (i.first == j.first) {
                    return i.second > j.second;
                } else {return i.first > j.first; } });

    std::vector<std::pair<int,int>> c;
    std::vector<std::pair<int,int>> solution;

    _f(sorted, c, 0, v.size(), solution);

    auto largest_stack = std::max_element(solution.begin(),solution.end(), [](const std::pair<int,int> &i, const std::pair<int,int> &j) {
               return i.first < j.first; 
    });
    
    height = (*largest_stack).first;
    auto it = std::find(v.begin(), v.end(), *largest_stack);
    index = std::distance(v.begin(), it);
}
int main(int argc, char **argv){

    std::vector<std::pair<int,int>> v = {{2,5},{1,6},{7,9},{3,1}};

    int height, index;
    height = index = 0;
    buildHanoiTower(v, height, index);
    std::cout << height << " " << index;


    return 0;
}
