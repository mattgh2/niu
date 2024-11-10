#include <string>
#include <cctype>
auto get_next_legal(std::string::const_iterator &it, bool fwrd) -> void {
    while (std::ispunct(*it) || std::isspace(*it)) { fwrd ? ++it : --it; }
}
auto ispalindrome(const std::string &s) -> bool {
    auto legal = [](const std::string::const_iterator &it) {
        if (std::ispunct(*it) || std::isspace(*it)) {return false; }
        return true;
    };
    auto front_iterator = s.cbegin(), back_iterator = s.cend() - 1;
    while (front_iterator < back_iterator) {
        if (!legal(front_iterator)) get_next_legal(front_iterator, true);
        if (!legal(back_iterator)) get_next_legal(back_iterator, false);
        if (std::tolower(*front_iterator++) != std::tolower(*back_iterator--)) {
            return false;
        }
    }
    return true;
}

