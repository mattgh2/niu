#include <vector>

typedef std::vector<std::vector<int>> twod_int_vector;

std::vector<int> diamondsequence(twod_int_vector &m) {
    auto [N, M] = std::make_pair(m.size(), m[0].size());

    if (N % 2 == 0 || N != M) { return {}; }

    std::vector<int>  diamond((2 * N) - 2);
    auto front_inserter = diamond.begin();
    auto back_inserter = diamond.rbegin();

    bool hit_the_edge = false;  

    auto update_positions = [&m, &hit_the_edge](const size_t &row, auto&& it1, auto&& it2) -> std::pair<ptrdiff_t,ptrdiff_t> {
        if (it2 == (m[row].end() - 1)) {hit_the_edge = true; } 
        if (hit_the_edge) { 
            ++it1; --it2; 
        } else { --it1; ++it2; }

        return std::make_pair((it1 - m[row].begin()), (it2 - m[row].begin()));
    };

    auto left_traversal = (m[0].cbegin() + N / 2);
    auto right_traversal = left_traversal;

    for (size_t row = 0; row < N; ++row) {

            *(front_inserter++) = *right_traversal;

            if (left_traversal != right_traversal) {
                *(back_inserter++) = *left_traversal;
            }

            auto offsets = update_positions(row, left_traversal, right_traversal);

            left_traversal = m[row + 1].cbegin() + std::get<0>(offsets);
            right_traversal = m[row + 1].cbegin() + std::get<1>(offsets);

    }

    return diamond;
}
