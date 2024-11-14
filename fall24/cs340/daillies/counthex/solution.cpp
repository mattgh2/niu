#include <iostream>
auto count_hex_a(int n) -> int {
    if (n == 0) return 0; 
    if (n < 0) return -1;
    return ((((n / 16.0) - static_cast<int>((n / 16))) * 16) == 10) ? 1 + count_hex_a(n/16) : count_hex_a(n/16);
}
