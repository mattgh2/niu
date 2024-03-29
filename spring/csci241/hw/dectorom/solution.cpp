#include <string>
#include <map>

std::string decimal_to_roman(int decimal_value) {

  std::string roman_value = "";

  // map to hold table
  std::map<int,std::string> mp;
  
  mp[1] = "I", mp[4] = "IV", mp[5] = "V"; mp[9] = "IX", mp[10] = "X", mp[40] = "XL", mp[50] = "L", 
  mp[90] = "XC", mp[100] = "C", mp[400] = "CD", mp[500] = "D", mp[900] = "CM", mp[1000] = "M";


    // check if decimal_value is key in map
    if (!(mp.find(decimal_value) == mp.end())) {
      roman_value+= mp[decimal_value];
    }
    // use map lowerbound function to get closest key 
    // and keep adding its value to the solution string untill we hit 0
    else { 
      int temp = decimal_value;
       
      while (temp > 0) {
        // check if new value is now a key
        if ((mp.find(temp) != mp.end())) {
          roman_value+= mp[temp];
          temp = 0;
        }
        else { // get the key closest to temp
          std::map<int, std::string>::iterator it= mp.lower_bound(temp);
          // go down a key
          --it;

          // add its value to solution string and subtract the key value from temp
          roman_value+= it->second;
          temp-= it->first;
        }
      }
    }

  return roman_value;
}


