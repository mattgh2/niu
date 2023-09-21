#include <iostream>
#include <iomanip>

using namespace std;


int main(){

  // variables
  double _price;
  int _count;

  // allignment variable
  const int rightAlign = 5;

  // inputs
  cout << "What is the price for a single item? ";
  cin >> _price;
  cout << "How many items were purchased? "; 
  cin >> _count;

  double cost = (_price * _count);

 // output
  cout << fixed << setprecision(2);
  cout << endl << right << setw(rightAlign) << _count << " items at " << "$" <<  _price << " each will cost " << "$" << cost << endl;


  return 0;
}
