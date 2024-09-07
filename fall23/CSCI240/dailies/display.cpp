#include <iostream>
#include <iomanip>

using namespace std;

void displayValues(int,int);

int main(){
  int numValues, startValue;
  cout << "How many values should be displayed? ";
  cin >> numValues;
  cout << "What is the starting display value? ";
  cin >> startValue;
  
  for (int i = 1; i <= 4; i++){
    cout << endl << "Test " << i << ": " << numValues << " values starting from " << startValue;
    displayValues(numValues, startValue);
    numValues -= 3;
    startValue += 7;
  }
  return 0;
}

void displayValues(int x, int y){

  cout <<endl;
  if (x < 0){
    cout << "*** Invalid Number of Values *** ";
  }
  else{
    for (int i = y  ; i < y + x ; i++){
      cout << i << " ";
    }
  }
  cout <<endl;
}
