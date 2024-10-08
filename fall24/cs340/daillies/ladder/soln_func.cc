#include <string> 
#include <vector>
#include <iostream>

// auto nclimbs(int n) -> int {
//     
// }

auto permutation(std::string s, std::string p = "" ) -> void {
    if (s.empty()) {
        std::cout << p << "\n";
        return;
    }

    char ch = s[0];
    for (size_t i = 0; i <= p.length(); ++i) {
        std::string first = p.substr(0, i);
        std::string second = p.substr(i, p.length());
        permutation(s.substr(1), first + ch + second);
    }

}
int main(int argc, char **argv){

    permutation("abc") ;

    return 0;
}
