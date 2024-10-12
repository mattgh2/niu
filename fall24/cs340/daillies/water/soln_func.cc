#include <algorithm>

auto howmuchwater(unsigned int a[], int n) -> int {
    size_t water = 0;
    if (n == 0) {return -1; }

    unsigned int * right_wall = nullptr, * left_wall = nullptr;
    while (right_wall != a) {

        for (unsigned int * r = a + (n - 1); r != (a); --r) {
            if (*r > *(r - 1)) {
                right_wall = r;
                for (r = r - 1;  r != (a - 1); --r) {
                    if (*(r - 1) < *r) {
                        left_wall = r;
                        break;
                    }
                }
                break;
            }
        }
        if (right_wall && left_wall) {
            auto s = std::min(*right_wall, *left_wall);
            std::for_each(left_wall + 1, right_wall, [s, &water](unsigned int i){
                    water+=s - i;
                    });

        } right_wall = left_wall - 1;
    }

    
    



    return water;
}
