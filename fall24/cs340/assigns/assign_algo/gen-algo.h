
#ifndef NIU_CSCI340_GEN_ALGO_IMPL_H
#define NIU_CSCI340_GEN_ALGO_IMPL_H

#include "gen-algo.decl.h"

#include <algorithm>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <numeric>

/**
 * Reads lines from an input stream, 
 * proccessing each line using a custom function object.
 *
 * @param instream The input stream.
 * @param linecb. The custom function object.
 *
 * @return The number of lines read from the input stream.
 */
template <typename FN>
size_t read_lines(std::istream &instream, FN linecb) {
    
    std::string line;
    std::size_t count{0};

    // Proccess each string from the input stream.
    while (std::getline(instream, line)) {
        linecb(line);
        ++count;
    }
    return count;
}
/**
 * Splits a string into N tokens.
 * Strict version: Each delimiter marks the end of a token,
 * The next token will begin at the next character found after the delimter.
 *
 * @param instring String object to tokenize.
 * @param tokencb A function object.
 * @param delim The strings delimiter.
 *
 * @return The number of tokens.
 */
template <typename FN>
size_t split_string_strict(const std::string &instring, FN tokencb, char delim) {
    size_t tkn_count = 0;

    // Initialize range.
    auto first = instring.begin();
    auto last = instring.begin();
    
    // Loop through all tokens
    while (last != instring.end()) {

        // Find the next delimiter.
        last = std::find(first, instring.end(), delim);

        // Construct current token from range.
        std::string token(first,last);

        // Process the token.
        tokencb(token);

        // Update first to the start of the next token.
        first = (last == instring.end()) ? last : last + 1;
        
        ++tkn_count;
    }
    return tkn_count;
    
}
/**
 * Splits a string into N tokens.
 * Greedy version: Each delimeter marks the end of a token,
 * The next token will begin at the first character that is not a delimeter.
 *
 * @param instring String object to tokenize.
 * @param tokencb A function object.
 * @param delim The strings delimiter.
 *
 *
 * @return The number of tokens.
 */
template <typename FN>
size_t split_string_greedy(const std::string &instring, FN tokencb, char delim) {
    size_t tkn_count = 0;
    // Get the position of the first token.
    size_t pos = instring.find_first_not_of(delim);

    // Get the initial range.
    auto first = instring.begin() + pos;

    // Iterator through the string, finding each token,
    // Once a token is found, process the token.
    while (first != instring.end()) {


    auto last = instring.end();

    // Find the next delim.
    last = std::find(first,last, delim);

    // Process the token.
    std::string token(first,last);
    tokencb(token);

    // Get the start of the next token.
    first = std::find_if_not(last, instring.end(), [delim](const auto a) {
                return (a == delim);
    });
    ++tkn_count;
    }

    return tkn_count;
}
/**
 * Prints table in a tidy format.
 *
 * @param ost The output stream to output to.
 * @param table The STR_TABLE containing the data.
 * @param widths widths of the table.
 * @param maxcol The maximum number of columns to print.
 * @param pre A string object printed at the start of each row.
 * @param sep String to print between columns.
 * @param post String to print at the end of each row.
 * @param leftalign A boolean which determines the alignment.
 *
 */
 template <typename TABLE, typename ARRLIKE>
 void print_table(std::ostream & ost, 
                  const TABLE & table, 
                  const ARRLIKE & widths, 
                  unsigned int maxcol, 
                  const std::string &pre, 
                  const std::string &sep,
                  const std::string &post,
                  bool leftalign) 
 {

     auto first = table.begin();
     // Iterate through rows in the table in range [0, maxcols).
     while (first != table.end()) {
        ost << pre;

        size_t col_width = 0, col_count = 0;

        // Loop through row, printing each column entry.
        std::for_each((*first).begin(), (*first).begin() + maxcol, [&](const auto &a) {
                    ost << (leftalign ? std::left : std::right) 
                        << std::setw(widths[col_width]) 
                        << a 
                        << (col_count == maxcol - 1 ? "" : sep);
                        ++col_count; ++col_width;
                });
        ost << post << '\n';
        ++first;
        col_count = 0;
     }
 }

/**
 * Gets the table row with the smallest column width.
 *
 * @param table the STR_TABLE that holds the data.
 *
 * @return The minimum row size.
 */
 inline int table_min_cols(const STR_TABLE &table) {

    // If the table is empty, the below algorithm will 
    // return size_t::max() instead of the intented result (0).
    if (table.empty()) {return 0; }

    // Checks each row width to see if it is less than the current running minimum.
    // If the current min is less than the min stored in the accumulator, 
    // the accumulators value changes to the new min.
    size_t min_size = std::accumulate(table.begin(), table.end(), std::numeric_limits<size_t>::max(), [](size_t acc, const auto & a) {
                auto min_size = a.size();
                if (min_size < acc) {
                    acc = min_size;
                } return acc;
    });
    return min_size;
 }

/**
 * Fills a vector with the longest strings in each column of an STR_TABLE.
 *
 * @param table An STR_TABLE.
 *
 * @return A vector object that contains the widths.
 */
template <typename STR_TABLE>
std::vector <int> calc_widths(const STR_TABLE & table) {

    auto max_cols = table_min_cols(table);
    std::vector<int> longest_strings(max_cols);
    auto it = longest_strings.begin();


    // Iterate through each column, find the string with the maximum size.
    for (int col = 0; col < max_cols; ++col) {
        int acc = std::numeric_limits<int>::min(); 
        for (size_t row = 0; row < table.size(); ++row) {
            int value = static_cast<int>(table[row][col].length());
            if (value > acc) {
                acc = value;
            }
        }
        *it++ = acc;
    }

    return longest_strings;
}

/**
 * loads data from a tsv file into a STR_TABLE.
 *
 * @param filename The name of the file to pull data from.
 *
 * @return An STR_TABLE containing the data from the file.
 */
 inline STR_TABLE load_tsv(const std::string & filename) {
     STR_TABLE table;

     // Open file.
     std::ifstream input_file(filename);

     // Check for failure.
     if (input_file.fail()) {
         std::cerr << "Error: failed to open " << filename;
         return {};
     }

     size_t row = 0;

     // Adds a token in the current row.
     auto add_to_table = [&table, &row](std::string &token) -> void {

        // Check if table needs another row. 
        if (table.size() <= row) {
            table.push_back({});
        }
        // push token to end of current row.
        table[row].push_back(token);
     };

     // Read and process lines from the file.
     read_lines(input_file,[&add_to_table, &row](std::string &string){ 
                split_string_strict(string, add_to_table, '\t');
                ++row;
    });
     return table;
 }

/**
 * Orders the rows in the table so that column number col is sorted in ascending order, alphabetically.
 *
 * @param table A STR_TABLE
 * @param col The column to order by.
 *
 */
 inline void table_sort_alpha(STR_TABLE & table, unsigned int col) {
     std::ranges::sort(table,[&col](const auto &a, const auto &b) {
                return a[col] < b[col];
             });
 }
/**
 * Orders the rows in the table so that column number col is sorted in ascending order, numerically.
 *
 * @param table A STR_TABLE
 * @param col The column to order by.
 *
 */
 inline void table_sort_numer(STR_TABLE & table, unsigned int col) {
     std::ranges::sort(table, [&col](const auto &a, const auto &b){
                return (std::strtod(a[col].c_str(), nullptr) < std::strtod(b[col].c_str(), nullptr));
             });

 }
#endif
