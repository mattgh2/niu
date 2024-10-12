#include <iostream>
auto pentalpha(int place_order[]) -> bool {
    for (int const * i = place_order; i < place_order + 10; ++i) {
        std::cout << *i << '\n';
    }
    return false;
}
