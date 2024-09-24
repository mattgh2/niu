#include <vector>
#include <numeric>
#include<algorithm>

int findmiddle(std::vector<std::vector<int>> &vecs, int &p) {
    
    std::size_t s = std::accumulate(vecs.cbegin(), vecs.cend(), 0 ,[](std::size_t init, const std::vector<int> &vec) {
                return init + vec.size();
            });

    if (s % 2 == 0) { return 0; } 

    std::vector<int> result(s);

    auto it = result.begin();
    for (const auto &vec : vecs ) {
        it = std::copy(vec.cbegin(), vec.cend(), it);
    }
    std::ptrdiff_t mid = (std::distance(result.cbegin(), result.cend()) / 2);

    std::partial_sort(result.begin(),result.begin() + mid + 1, result.end());
    p = *(result.cbegin() + mid);

    return 1;
}
