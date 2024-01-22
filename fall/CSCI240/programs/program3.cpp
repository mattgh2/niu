/***************************************************************
CSCI 240         Program 3     Fall 2023

Programmer: Matt Warner

Section: 240-001

Date Due: September 22, 2023

Purpose: This program calculates and outputs the users income tax based on their annual gross income.
***************************************************************/
#include <iostream>
#include <iomanip>

using namespace std;


int main () {

  // initilzes variables to store gross income and income tax
  double grossIncome;
  double incomeTax = 0;

  // prompts user for their gross income, stores input in variable declared above
  cout << "What is your gross income?" << setw(5) << right << " $";
  cin >> grossIncome;

  // condition statements that calculates the users income tax based on users gross income,
  if (grossIncome <= 11000) // lowest tax bracket
    {
      incomeTax += (grossIncome * .10);
    }

  else if (grossIncome > 11000 && grossIncome <= 44725)  // second tax bracket range
    {
      incomeTax += (11000 * 0.10) + ((grossIncome - 11000) * 0.12);
    }

  else if (grossIncome > 44725 && grossIncome <= 95375)   // third tax bracket range
    {
      incomeTax += (11000 * .10) + (33725 * .12) + ((grossIncome - (11000 + 33725)) * .22);
    }

  else // Highest tax bracket
    {
      incomeTax += (11000 * .10) + (33725 * .12) + (50650 * .22) + ((grossIncome - 95375) * .24);
    }
  

  // outputs users gross income as well as their income tax
  cout << endl << fixed << setprecision(2);
  cout << setw(20) << left << "Gross Income: " << "$" << setw(11) << right << grossIncome << endl;
  cout << setw(20) << left << "Income Tax: " << "$" << setw(11) << right << incomeTax << endl;

  return 0; 
}
