#include <iostream>
[[nodiscard]]
auto nclimbs(int n) -> int {

    if (n <= 3)
        return (n == 3) ? 4 : n ;

    return nclimbs(n-1) + nclimbs(n-2) + nclimbs(n-3);
}
