#include <vector>
#include <iostream>
std::vector<int> diamondsequence(std::vector<std::vector<int>> &m) {

    if (m[0].size() != m.size() || m.size() / 2 == 0) { return {}; }

    auto first_row_middle = ((m[0]).size() / 2);
    size_t row_count = m.size();
    size_t edge = m.size() - 1;

    std::vector<int> diamond;
    bool hit_edge = false;

    
    auto process_row = [&](size_t &row, size_t &pos1, size_t &pos2) -> void {
        if (pos2 == edge) {
            hit_edge = true;
        }
        if (pos1 == pos2) {
            diamond.push_back((m[row])[pos1]);
        } else { 
            diamond.push_back((m[row])[pos1]);
            diamond.push_back((m[row])[pos2]);
        }

        if (hit_edge) {
            ++pos1; --pos2;
        } else {
            --pos1; ++pos2;
        }

    };

    size_t i = first_row_middle, j = first_row_middle;
    for (size_t current_row = 0;  current_row < row_count; ++current_row) {
        
        process_row(current_row, i, j);
    }

    return diamond;
}
int main() {
    std::vector<std::vector<int>> v = {{1,2,3},{4,5,6},{7,8,9}};
    std::vector<int> diamond = diamondsequence(v);

    for (auto it = diamond.begin(); it != diamond.end(); ++it) {
        std::cout << *it;
    }
}
// Current problems:
// Looks terrible.
// We can set diamonds vector to ((2 * size) - 2) to avoid unecessary allocations.
// Output is not in the correct order.
// I think we can still do one pass. instead of 2.
// Can we rotate?
