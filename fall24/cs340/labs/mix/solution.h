#include <unordered_map>
#include <algorithm>
template <typename ForwardIterator>
void mixNumbers(ForwardIterator begin, ForwardIterator end)
{
    
    std::unordered_map<int,std::pair<std::decay_t<decltype(*begin)>, int>> mp;

    int offset = 0;

    // Key = pos, pair<0> = value, pair<1> = moved position
    std::for_each(begin,end,[&](const auto &elem){
                mp[offset] = std::make_pair(elem, offset);
                ++offset;
            });

    ForwardIterator aux1, aux2;
    aux1 = aux2 = begin;

    // Keep track of the current position. 
    int pos = 0;
    ForwardIterator front = begin;
    while (begin != end) {
    // For each element in range.
     
    // Find its original value.
    // Get the position of that value.
    // Calculate the number of swaps.
    
        bool reverse_swap =false;
        int aux1_pos, aux2_pos;

        int pos_in_container = std::get<1>(mp[pos]);

        auto get_number_of_swaps = [&]() -> int {

            // Could be negative, fine, or go past the bounds.
            int number_of_swaps = std::get<0>(mp[pos]);

            // Negative number_of_swaps will be the offset of the destination pos for theh reverse swap.
            if (number_of_swaps < 0) {
                reverse_swap = true;

                number_of_swaps = abs(std::get<0>(mp[pos]));
                aux2_pos = std::get<1>(mp[pos]) - number_of_swaps;

                // Make sure we are still in bounds.
                if (aux2_pos < 0) { aux2_pos = 0; }

            }

            // fix the swaps to be within the bounds of the container.
            else if ((number_of_swaps + pos) >= offset){

                // Nt. Should be Number of swaps till the last value.
                number_of_swaps = (offset - 1) - pos_in_container;

            }
            return number_of_swaps;
        };
    
    int number_of_swaps = get_number_of_swaps();

    // Position aux1.
    int c = 0;
    while (c < pos_in_container) {
        ++aux1;
        ++c;
    }

    // Step up for a reverse swap.
    if (reverse_swap) {
        for (int i = 0; i < aux2_pos; ++i) {
            ++aux2;
        }
    // Or just move aux2 to one past aux1.
    } else {
        aux2 = aux1;
        ++aux2;
    }

    aux1_pos = c;
    for (int swaps = 0; swaps < number_of_swaps; ++swaps) {

        // Need to update pos stored in my pair before swappage. 
        if (reverse_swap) {
            aux2_pos = number_of_swaps;
            --std::get<1>(mp[aux1_pos]);
            ++std::get<1>(mp[aux2_pos++]);
        
        } else{
            aux2_pos = aux1_pos + 1;
            ++std::get<1>(mp[aux1_pos++]);
            --std::get<1>(mp[aux2_pos++]);
        }

        // perfrom the swap
        std::swap(*aux1, *aux2);
        

        if (reverse_swap) {
            ++aux2;
        } else {
            ++aux1; ++aux2;
        }


    }

    ++pos;
    ++begin;
    aux1 = aux2 = front;
  }
    
}
