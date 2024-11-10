#include <iostream>
#include <utility>
auto quicksort(int array[], int start, int end) -> void;
auto partition(int array[], int start, int end) -> int;

auto quicksort(int array[], int len) -> void  {
    quicksort(array, 0, len -1);
}
auto quicksort(int array[], int start, int end) -> void {
    if (start < end) {
        
        int pivot_point = partition(array,start, end);

        quicksort(array, start, pivot_point - 1);
        quicksort(array, pivot_point + 1, end);
    }
}

auto partition(int array[], int start, int end) -> int {
    int mid = (start + end) / 2;
    std::swap(array[start], array[mid]);
    
    int pivot_index = start;
    int pivot_value = array[start];

    int scan = start + 1;
    
    while (scan <= end) {
        if (array[scan] < pivot_value) {
            ++pivot_index;
            std::swap(array[scan], array[pivot_index]);
        }
        ++scan;
    }
    std::swap(array[pivot_index], array[start]);
    return pivot_index;
}




int main(int argc, char **argv){

    int array[6] = {4,8,32,1,12,5};
    quicksort(array, 6);
    for (const auto &i:array) { std::cout << i << ' '; }


    return 0;
}
