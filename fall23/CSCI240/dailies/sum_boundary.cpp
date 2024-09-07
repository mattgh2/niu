#include <iostream>
#include <iomanip>

using namespace std;


int main(){

  int lower, upper, sum = 0;

  cout << "What is the lower bound? ";
  cin >> lower; 

  cout << "What is the upper bound? ";
  cin >> upper;

  if (lower > upper){

    int tmp = lower;
    lower = upper;
    upper = tmp;

    cout << endl << "*** boundary values have been swapped *** " << endl;
  }

  for (int i = lower; i <= upper; i++)
  {
    sum += i;
  }

  cout << endl << "The sum of the values between " << lower << " and " << upper << " is " << sum << endl;
  

  return 0;
}

// Goal -- > 
// need to sum the values between lower and upper
// let lower = 0 
// let upper = 10
// sum = 0 + 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10
//
