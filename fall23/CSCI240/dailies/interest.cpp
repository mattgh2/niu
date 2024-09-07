#include <iostream>
#include <iomanip>

using namespace std;

int main(){

double initialInvestment;
double interestRate;

cout << "How much is the initial investment amount? ";
cin >> initialInvestment;

cout << "What is the annual interest rate? ";
cin >> interestRate;

double year1 = initialInvestment + (initialInvestment * (interestRate / 100));
double year2 = year1 + (year1 * (interestRate / 100));
double year3 = year2 + (year2 * (interestRate / 100));
double year4 = year3 + (year3 * (interestRate / 100));

double year1Increase = year1 - initialInvestment;
double year2Increase = year2 - year1;
double year3Increase = year3 - year2;
double year4Increase = year4 - year3;

// output 
cout << fixed << setprecision(2);
cout << endl << endl <<  "Investment Results" << endl <<endl;
cout << "Initial Investment" << right << setw(15) << initialInvestment << endl;

cout << fixed << setprecision(1);
cout <<  "Annual Interest Rate" << right << setw(13) << interestRate << endl << endl;

cout << fixed << setprecision(2);
cout << "Year 1 account value " << "$" << year1 << "  --  " "increase of " << "$" << year1Increase << endl;
cout << "Year 2 account value " << "$" << year2 << "  --  " "increase of " << "$" << year2Increase << endl;
cout << "Year 3 account value " << "$" << year3  << "  --  " "increase of " << "$" << year3Increase << endl;
cout << "Year 4 account value " << "$" << year4 << "  --  " "increase of " << "$" << year4Increase << endl;


  return 0;
}
