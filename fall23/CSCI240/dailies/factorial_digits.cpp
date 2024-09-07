#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main(){

  int N; 
  int factorial;
  //Get the value of N
  cout << "N value (must be greater than or equal to 0 )? ";
  cin >> N;
  
  if (N < 0 || N > 13)
  {
    cout << endl << "Invalid Input: " << N << endl;

    return 0;
  }

  if (N == 0){

    factorial = 1;
  }
  else{

    factorial = N;

    for (int i = (N - 1); i > 1; i--)
    {
      factorial *= i;
    }
  }

  string num = to_string(factorial);
  int digits = num.length();

  cout << endl << N << "! " << "is equal to " << factorial << ". There are " << digits << " digits." << endl;

  return 0;

}
