#include <map>
#include <string>
std::string decimal_to_roman(int decimal_value) {

    static std::map<int,std::string> mp = {{1,"I"}, {4, "IV"}, {5, "V"}, {9, "IX"},{10,"X"}, {40, "XL"}, {50, "L"}, {90, "XC"},{100, "C"}, {400, "CD"},{500, "D"}, {900, "CM"}, {1000, "M"}};

    std::string solution_string;
    std::map<int,std::string>::iterator it;

    auto get_solution = [&](auto&& ff, auto num, auto&& it) -> void {
        if ((it = mp.find(num)) != mp.end()) {
            solution_string+= it->second; 
            num-=it->first;
        }
        else {
            it = (mp.lower_bound(num)); --it;
            solution_string+=it->second;
            num-=it->first;
        }
        if (num > 0) {
            ff(ff, num, it);
        }
    };
    
    get_solution(get_solution, decimal_value, it);

    return solution_string;
 
}
