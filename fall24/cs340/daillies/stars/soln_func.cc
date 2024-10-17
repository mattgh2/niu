#include <unordered_map>
#include <algorithm>

auto place_stone(std::pair<int,int> const &stone_paths, int a[], size_t count) -> bool{

    if (std::find(a, a + count, std::min(stone_paths.first, stone_paths.second)) == a + count) {
        *(a + count) = std::min(stone_paths.first, stone_paths.second);
        return true;
    } 
    if (std::find(a, a + count, std::max(stone_paths.first, stone_paths.second)) == a + count) {
        *(a + count) = std::max(stone_paths.first, stone_paths.second);
        return true;
    }
    return false;
}

auto pentalpha(int place_order[]) -> bool {
        
    static std::unordered_map<int, std::pair<int,int>> paths = 
    {{0, {5,6}}, {1, {7,3}}, {2,{8,4}},{3,{1,9}}, {4,{2,7}},
    {5,{0,9}}, {6, {0,8}}, {7,{4,1}},{8,{2,6}}, {9,{5,3}}};

    size_t placements = 1;
    int stone = place_order[0];
    while (placements < 10 && place_stone(paths[stone], place_order, placements)) {
        stone = place_order[placements];
        ++placements;
    }

    return (placements == 10);
}

