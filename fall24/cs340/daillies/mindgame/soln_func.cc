#include <string>

auto mm_score(std::string k, std::string g, int &b, int &w) -> int {
    b = w = 0;
    if (k.length() != g.length()) {
        return 0;
    }
    
    for (size_t i = 0; i < k.length(); ++i) {
        if (g[i] == k[i]) {
            ++b;
        }
        else if (k.find_first_of(g[i]) != std::string::npos) {
            ++w;
        }
    }

    return 1;
}
