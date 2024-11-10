#include <cstddef>
#include <iostream>

auto mintimesteps(int a[], int len, int n) -> int {
    std::size_t time_machines_used = 0, current_tm = 0;

    int max_year = 0;

    while (n > 0) {
        max_year = 0;
        if (current_tm == static_cast<size_t>(len - 1)) {
            if (a[current_tm] >= n) return time_machines_used + 1;
            else return -1;
        }

        for (int i = a[current_tm]; i > 0; --i) {
            if (a[current_tm +i] < len && a[current_tm +i] > max_year) {
                max_year = i;
            }
        }
        current_tm+=max_year;
        n = n - max_year; ++time_machines_used;
    }
    return time_machines_used;
}
// int main () {
//     int a[4] = {1,1,1,1};
//     std::cout << mintimesteps(a, 4, 3);
// }
