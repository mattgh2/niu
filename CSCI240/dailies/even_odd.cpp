#include <iostream>
#include <iomanip>

using namespace std;

int main(){

 int num; 

 //get a number from the user
 cout << "Enter an integer value: ";
 cin >> num;

  // if the integer value is even, display a formatted "EVEN" message.
  // otherwise display a formatted "ODD" message.


  if (num % 2 == 0){
    cout << endl << "The value " << num << " is EVEN." << endl;
  }

  else{
    cout << endl << "The value " << num << " is ODD." << endl;
  }

  return 0;
}
