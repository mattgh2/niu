#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_map>

class report {
private:
  std::string input_file;
  std::vector<std::string> words;

public:
  void validate_input(int argc, char** argv);
  void fill_word_list();
  void highest_occurance(std::unordered_map<int,int> &,int &, int &) const;
  void get_longest_words(std::unordered_map<std::string,int> &, int &,int &) const;
  void print(const int, const int, const std::unordered_map<std::string, int>, const int, int) const;
};

void report::validate_input(int argc, char** argv) {

  // Checks if input file exists
  if (argc != 2) {
    std::cout << "Please provide a single input file.\nUsage: ./z2004200 input.txt\n";
    exit(1);
  }
  // Grabs input file
  this->input_file = argv[1];

  // procceses input file
  std::ifstream infile(input_file);
  if (infile.fail()) {
    std::cout << "Error: File could not be opened";
    exit(1);
  }
}
void report::fill_word_list() {

  std::ifstream infile(this->input_file);
  std::string line;
 
  // Loop that reads each line of the input file, adding each word to an array of words found in the file.
  while (getline(infile, line)) {

    // ignores lines that start with #
    if (line[0] == '#')
      continue;

    else {
      int i = 0;
      // Loop that procceses each word in the given line.
      while (i < line.size()) {
        std::string word = "";

        // Loop that builds word
        for (; line[i] != ' ' && i < (int)line.size(); i++) {
          // ignores punctuation
          if (std::ispunct(line[i]))
            continue;
          else 
            word+=line[i]; // adds character to word
        }
        this-> words.push_back(word); // adds word to word list
        ++i; // moves to next char
      }
    }
  }
}

void report::highest_occurance(std::unordered_map<int,int> &mp, int &largest_frequency, int &word_size) const {
  // Loop that iterates through each word, adding the word_length as a map key, and adding one to its count value.
  for (int i = 0; i < this-> words.size(); i++) {
    int word_length = words[i].length(); // grabbing word length of current word
    mp[word_length]++; // storing in map
  }
  // loop that finds the key, value pair with the most number of occurances.
  for (const auto& pair : mp) {
    if (pair.second > largest_frequency) {
      largest_frequency = pair.second;
      word_size = pair.first;
    }
  }
}
void report::get_longest_words(std::unordered_map<std::string, int> &longest_words, int &longest_words_count, int &longest_word_length) const {
  // loop that iterates through each word in the array of words, to find the word with longest length
  for (int i = 0; i < this-> words.size(); i++) {
    if (words[i].length() > longest_word_length) {
      longest_word_length = words[i].length();
    }
  }
  // loop that creates a map of the longest words.
  // If the current word at index i has longest length, it gets added to the map
  for (int i = 0; i < this-> words.size(); i++) {
    if (words[i].length() == longest_word_length) {
      longest_words[words[i]]++; // stores word as key
      longest_words_count++; // stores count as value
    }
  }
}
void report::print(const int largest_frequency, const int word_size, const std::unordered_map<std::string, int> longest_words, const int longest_word_length, const int longest_words_count) const {
  // Printing word count 
  std::cout << this-> input_file << " contains " << this-> words.size() << " words" << std::endl;

  // Printing highest size occurance
  std::cout << "words of size " << word_size << " occur the most: " << largest_frequency << " times" << std::endl;

  // Printing longest words
  std::cout << "the longest words have " << longest_word_length << " letters and occur " << longest_words_count << " times" << std::endl;
  for (const auto& pair : longest_words) {
    std::cout << pair.first << std::endl;
  }

}

int main(int argc, char** argv) {

  report report1;

  report1.validate_input(argc, argv);
  report1.fill_word_list();


  int
    largest_frequency = 0,
    word_size,
    longest_words_count = 0,
    longest_word_length = 0;
  
  std::unordered_map<int,int> mp; // map for length frequency
  std::unordered_map<std::string, int> longest_words; // using map instead of vector to avoid duplicates

  report1.highest_occurance(mp,largest_frequency,word_size);
  report1.get_longest_words(longest_words, longest_words_count, longest_word_length);
  report1.print(largest_frequency, word_size, longest_words, longest_word_length, longest_words_count);

  return 0;
}
