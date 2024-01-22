/***************************************************************
CSCI 240         Program 1     Fall 2023

Programmer: Matt Warner

Section: 240-001

Date Due: Friday, September 8, 2023

Purpose: This program calculates and displays the profit per value
  of harvested crops as done in farming simulation video games.
***************************************************************/

#include <iostream>
#include <iomanip>

using namespace std;


int main(){

  // initilizes variables that will be used to store the values input from the user.
  int goldCost, numberOfDays;
  double resaleValue;

  // prompts user for specific values, stores values in variables declared above
  cout << "Enter the gold cost for your seeds: ";
  cin >> goldCost;
  cout << "Enter the number of days required for the crop to mature: ";
  cin >> numberOfDays;
  cout << "Enter the expected resale value of the mature crops: ";
  cin >> resaleValue;


  // calculates how much gold user earns from each day spent watering/waiting for the crop to mature. assigns results to variable.
  double profitPerDay = (resaleValue - goldCost) / numberOfDays;

  // outputs amount of gold earned per day.
  cout << endl <<  "The projected profit per day value of this crop is: "<< profitPerDay << endl;
  

  return 0;
}
