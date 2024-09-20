#include <iostream> 
#include <unordered_map>
#include <string>

auto read_input() -> void {

    static std::unordered_map<char,std::string> special_chars = {
        {'&', "&amp;"}, 
        {'<', "&lt;"},
        {'>', "&gt;"},
        {'"', "&quot;"},
        {'\'', "&apos;"}
    };

    char data;
    while (std::cin >> data >> std::noskipws)  {
        std::unordered_map<char,std::string>::const_iterator it;
        if ((it = special_chars.find(data)) != special_chars.end()) {
            std::cout << it->second;
        } else {
            std::cout << data;
        }
    }
}

int main() {
    read_input();
    return 0;
}
    
