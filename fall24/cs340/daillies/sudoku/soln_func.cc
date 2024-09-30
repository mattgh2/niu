#include <vector>
#include <set>
#include <algorithm>

bool valid_sudoku(std::vector<std::vector<int>> &s ) {

    auto check_row = [&s](auto begin, auto end) -> bool {
        std::set<int> ss;
        while (begin != end) {
            ss.insert(*begin);
            ++begin;
        }
        return (ss.size() == s.size());
    };
    auto check_col = [&s](size_t col) {
        std::set<int> ss; 
        for (size_t i = 0; i < s.size(); ++i) {
            ss.insert(s[i][col]);
        }
        return (ss.size() == s.size());
    };
    auto check_grid = [&s](size_t grid) -> bool{

        std::vector<std::set<int>> vs;
        auto vector_iterator = s.begin() + grid;
        auto element_iterator = (*vector_iterator).begin();

        int i = 0, j = 0;
        std::set<int> ss;  
        while (i < 3) {
            if (j == 3) {
                ++i; 
                vector_iterator = s.begin() + grid; 
                element_iterator = (*vector_iterator).begin() + (3 * i);
                vs.push_back(ss);
                ss.clear(); 
            }

            for (int i = 0; i < 3; ++i) {
                ss.insert(*element_iterator);
                ++element_iterator;
            }
            ++vector_iterator;
            element_iterator = (*vector_iterator).begin() + (3 * i);
            ++j;
        }

       bool size_diff = false;
       std::for_each(vs.begin(), vs.end(),[&s, &size_diff](const auto& set) {
                    if (set.size() != s.size()) {
                        size_diff = true;
                    } 

                });
       return (size_diff);

    };

    for (size_t i = 0; i < s.size(); ++i) {
        if (!check_row(s[i].begin(), s[i].end())) {return false; }
        if (!check_col(i)) {return false; }
        if (i % 3 == 0) {
            if (check_grid(i)) {return false; }
        }
    }
     

    return true;
}

