/************************************************************************************
* NIU CSCI 340 Section 3
* Assignment # 2
* Matt Warner - z2004200
* *
* I certify that everything I am submitting is either provided by the professor for use in *
* the assignment, or work done by me personally. I understand that if I am caught submitting *
* the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic *
* Misconduct and will be punished as such. *
* *
* Provides various templated algorithms that are designed around iterators to perform simple computing tasks.
* 
************************************************************************************/
#ifndef NIUCSCI340ASSIGN2_ALGOS_H
#define NIUCSCI340ASSIGN2_ALGOS_H


#include <iomanip>
#include "assign2-algos.decl.h"
// Implement your algorithms for assignment 2 here.

#include <iostream>
#include <string>
/**
 * Basic implementation of accumulate from the numerics library.
 * Can only sum the iterators in range [first, last).
 *
 * @param first Start of range.
 * @param last End of range.
 * @param init The initial value for the accumulator.
 *
 * @return the sum of all elements in the provided range.
 */
template <typename ITERATOR, typename Tp>
[[nodiscard]] auto accumulate(ITERATOR first, ITERATOR last, Tp init = 0) -> Tp {
    while (first != last) {
        init = init + *first;
        ++first;
    }
    return init;
}
/**
 * Basic implementation of for_each from the STL.
 * Iterates through range [first, last), applying a unary function object to each element.
 *
 * @param first Start of range.
 * @param last End of range.
 * @param f A unary function object.
 *
 */
template <typename ITERATOR, typename op>
void step_through_range(ITERATOR first, ITERATOR last, op f) {
    while (first != last) {
         f(*first);
         ++first;
    }
}
/**
 * Sets the members of the struct token_info.
 * Iterates through range [begin, last).
 * Strict implementation, empty tokens will be formed.
 *
 * @param begin Start of range.
 * @param end End of range.
 * @param delim A delimeter.
 *
 * @Note: Made to support forward iterators (or better).
 */
template <typename ITERATOR, typename T>
token_info<ITERATOR> get_next_token_strict(ITERATOR begin, ITERATOR end, T delim) {
  token_info<ITERATOR> token;

  token.t_begin = begin;

  auto scan = begin;

  while ((scan != end) && (*scan != delim)) {
      ++scan;
  }

  token.t_end = scan;
  token.t_next = (scan == end) ? end : ++scan;

  return token;
}
 /* Sets the members of the struct token_info.
 * Iterates through range [begin, last).
 * Greedy implementation, empty tokens will be thrown away.
 *
 * @param begin Start of range.
 * @param end End of range.
 * @param delim A delimeter.
 *
 * @Note: Made to support forward iterators (or better).
 */
template <typename ITERATOR, typename T>
token_info<ITERATOR> get_next_token_greedy(ITERATOR begin, ITERATOR end, T delim) {

    token_info<ITERATOR> token;

    // Starting token at the beginning. 
    while (*begin == delim && begin != end) {
        ++begin;
    }
    token.t_begin = begin;

    auto scan = begin;

    // Find where the token ends.
    while ((scan != end) && (*scan != delim)) {
        ++scan;
    }
    
    token.t_end = scan;

    // Find where the next token begins. 
    while ((*scan == delim) && (scan != end)) {
        ++scan;
    }

    token.t_next = scan;

    return token;


}
/**
 * Iterates through range [begin, end). 
 * Each element in range will be added to its corresponding bin, assuming it can be placed in one.
 *
 *
 * @param begin Start of range.
 * @param end End of range.
 * @param bin_counts An object that stores bin counts.
 * @param N The total number of bins.
 * @param width The width of each bin.
 *
 */
template<typename ITERATOR, typename RANDOM_ACCESS>
void histogram(ITERATOR begin, ITERATOR end, RANDOM_ACCESS & bin_counts, int N, double width) {
  
    // Reset all bins to 0
    for (int i = 0; i < N; ++i) {
        bin_counts[i] = 0;
    }
    // Defines the boundaries of the bins.
    auto [bin_start, upperbound] = std::make_pair(0, N*width);

    // Check if element can fit into one of the bins.
    auto fits_in_bin = [&bin_start, &upperbound](const auto& elem) -> bool {
        return (elem >= bin_start && elem < upperbound);
    };
    // For each element in range, check if element fits in a bin, 
    // incrementing its bin if it fits.
    step_through_range(begin,end, [&](const auto& elem) {
        if (fits_in_bin(elem)) {
            int bin = elem / width;
            ++bin_counts[bin];
        }
    });
    
}

/**
 * Prints elements in a range with formatting.
 *
 * @param ost The output stream.
 * @param begin Start of range.
 * @param end End of range.
 * @param pre Initial output before elements are output.
 * @param sep Seperator value printed after each element.
 * @param post Final element after all elements are printed.
 * @param width The width, in characters, of the column in which the values are printed.
 *
 */
template <typename ITERATOR>
void print_range(std::ostream & ost, ITERATOR begin, ITERATOR end, const std::string &pre, const std::string &sep, const std::string &post, int width) {
  // Print message before elements.
  ost << pre;

  // Structured binding for tracking the elements printed against the number of elements.
  auto [elements_printed, element_count] = std::make_pair(0, (range_count(begin,end) - 1));

  // Prints an element from the container.
  auto print_element = [&](const auto& elem) -> void {
    ost <<  std::setw(width) << elem << ((elements_printed < (element_count)) ? sep : "");
    ++elements_printed;
  };
    
  step_through_range(begin,end, print_element);

  // Print final message.
  ost << post;
};

/**
 * Sums the values in the range given.
 *
 * @param begin Start of range.
 * @param end End of range.
 *
 * @return The accumulated sum.
 */
template <typename ITERATOR>
double range_sum(ITERATOR begin, ITERATOR end) {
  return accumulate(begin, end, 0.0);
}
/**
 * Computes the average of values in a given range.
 *
 * @param begin The start of range.
 * @param end End of range.
 *
 * @return The computed average.
 */
template <typename ITERATOR>
double range_avg(ITERATOR begin, ITERATOR end) {

    size_t n_size = 0;
    double sum = 0.0;
    
    // For each element in range, add to sum, and increment size.
    step_through_range(begin,end, [&n_size,&sum](const auto& elem){
            sum = sum + elem;
            ++n_size;
    });
    double average = sum / n_size;

    return average;

}
/**
 * Finds the maximum value in the range of elements.
 *
 * @param begin Start of range.
 * @param end End of range.
 *
 * @return The largest value in the range of values.
 */
template <typename ITERATOR>
auto range_maxval(ITERATOR begin, ITERATOR end) {

    // Initial max value.
    auto max_val = *begin; 

    // Checks is current maximum is less than element in container.
    auto find_max_elem = [&max_val](const auto &elem) {
        if (elem > max_val) { max_val = elem; }
    };

    // Finds the minimum element from range.
    step_through_range(std::next(begin), end, find_max_elem);

    return max_val;
}

/**
 * Finds the minimum value in the range of elements.
 *
 * @param begin Start of range.
 * @param end End of range.
 *
 * @return The smallest value in the range of values.
 */
template <typename ITERATOR>
auto range_minval(ITERATOR begin, ITERATOR end) {

    // Initial min value.
    auto min_val = *begin;

    // Checks is current minimum is greater than element in container.
    auto find_min_elem = [&min_val](const auto &elem) {
        if (elem < min_val) { min_val = elem; }
    };

    // Finds the minimum element from range.
    step_through_range(std::next(begin),end, find_min_elem);

    return min_val;
}

/**
 * Counts the number of elements in the given range of elements.
 *
 * @param begin Start of range.
 * @param end End of range.
 *
 * @return The number of elements in the range.
 */
template <typename ITERATOR>
int range_count(ITERATOR begin, ITERATOR end) {

  int count = 0;
  // Add to count for each element in range.
  while (begin != end) {
      ++count; ++begin;
  }
  return count;
}

#endif /*NIUCSCI340ASSIGN2_ALGOS_H*/
