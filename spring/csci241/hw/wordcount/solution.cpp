#include <string>
#include <fstream>
#include <sstream>
using std::string;

bool wc(const string& file_name, int &lines, int &words, int& characters) {

  lines = 0, words = 0, characters = 0;

  std::ifstream infile(file_name);
  if (infile.fail()) {
    return false;
  }
  string buffer;
  std::ifstream temp(file_name);
  char c; 
  while (temp.get(c)) {
    characters++;
  }

  while (std::getline(infile, buffer)) {
    lines++;
    string op;
    std::stringstream ss(buffer);
    while (ss >> op) {
      words++;
    }

  }
  return true;
}
