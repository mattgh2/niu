#include <iostream>
#include <iomanip>

using namespace std;

int main(){

  int N, remainder;

  cout << "N value (must be positive)? ";
  cin >> N;

  while (N <= 0){
    
    cout << "Error: the N-value must be positive. Try again: ";
    cin >> N;

  }
  cout << endl << "Original: " << N << endl;

  cout << "Reversed: ";
  while (N > 0){
    remainder = N % 10;
    cout << remainder;
    N = N / 10;
  }
  cout << endl;


  return 0;
}


