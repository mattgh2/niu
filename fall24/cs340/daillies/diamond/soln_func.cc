#include <vector>

std::vector<int> diamondsequence(std::vector<std::vector<int>> &m) {

    if (m[0].size() != m.size()) {
        return {};
    }
    size_t row_mid = m[0].size() / 2;
    size_t col_mid = m.size() / 2;
    
    std::vector<int> diamond(4);

    auto get_pos = [&diamond](const size_t offset) {
        return diamond.begin() + offset;
    };
    
    while (diamond.size() != diamond.capacity()) {
        auto it = diamond.begin() + row_mid;
        
    }
    
    return {};
}
