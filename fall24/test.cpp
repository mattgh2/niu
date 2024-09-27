#include <unordered_map>
#include <numeric>
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>


template <typename ForwardIt>
auto mixNumbers(ForwardIt start, ForwardIt end) -> void {

    std::unordered_map<int, std::decay_t<decltype(*start)>> mp;

    // offset of each element in the original order
    int offset = 0;

    // capturing the orginal state of the list.
    std::for_each(start, end, [&mp, &offset](auto elem){
                mp[offset] = elem;
                ++offset;
            });

    
    int pos = 0;
    ForwardIt aux1, aux2;
    aux1 = start;

    ForwardIt front = start;

    while (start != end) {

        auto original_value = mp[pos];
        auto num_swaps = mp[pos++];
        if ((num_swaps + pos) > offset) {
            num_swaps = offset - pos;
        }
               
        std::size_t count = 0;
        while (*aux1 != original_value) {
            ++aux1;
            ++count;
        }

        if (num_swaps < 0) {
            aux2 = front;
            num_swaps = count + num_swaps;
            int c = 0;
            while (c++ < num_swaps) {
                ++aux2;

            }
            while (aux2 != aux1) {
                std::swap(*aux1, *aux2);
                ++aux2;
            }
        }
        else {
            aux2 = aux1;

            for (int swaps = 0; (swaps < num_swaps); ++swaps) {
                std::swap(*(aux1++), *(++aux2));
            }
        }

        ++start;
        aux1 = aux2 = front;
    }
}

int main(int argc, char **argv){

    std::vector<int> v= {0,2,3,-1,1,6};
    

    mixNumbers(v.begin(), v.end());
    for (const auto &i : v) {
        std::cout << i << ' ';
    }

    return 0;
}
