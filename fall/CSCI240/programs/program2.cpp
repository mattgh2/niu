/***************************************************************
CSCI 240         Program 2     Fall 2023

Programmer: Matt Warner

Section: 240-001

Date Due: September 15, 2023

Purpose: This program calculates / outputs the users Wilks Score and Powerlifting total, using the values the user inputs into the program.
***************************************************************/

#include <iostream>
#include <iomanip>

using namespace std;

int main(){

  // initilizes variables that will hold the users inputs.
  int maxSquat, maxBenchPress, maxDeadlift;

  // Prompts user for specified values, stores results in the int variables declared above.
  cout << "What is your max squat? ";
  cin >> maxSquat;
  cout << "What is your max bench press? ";
  cin >> maxBenchPress;
  cout << "What is your max deadlift? ";
  cin >> maxDeadlift;
   

  // stores value used in calculation of users Wilks Coefficient
  const double wilksCoefficient = 0.5976;

  // values used in output formatting.
  const int leftColumnSpacing = 20;
  const int rightColumnSpacing = 8;

  // sums the total of user input values. This will be used as users powerlifting total, as well as calculating wilks score
  int sumOfValues = (maxSquat + maxBenchPress + maxDeadlift);

  // initilizes and assigns wilks score
  double wilksScore;
  wilksScore = (sumOfValues * wilksCoefficient);

  // Outputs all necessary data
  cout << fixed << setprecision(3);
  cout << endl << setw(leftColumnSpacing) << left << "Max squat: " <<  setw(rightColumnSpacing) << right << maxSquat << endl; 
  cout << setw(leftColumnSpacing) << left << "Max Bench press: " << setw(rightColumnSpacing) << right <<  maxBenchPress << endl; 
  cout << setw(leftColumnSpacing) << left << "Max Deadlift: " << setw(rightColumnSpacing) << right << maxDeadlift << endl << endl;
  cout << setw(leftColumnSpacing) << left << "Powerlifing Total:" << setw(rightColumnSpacing) << right << sumOfValues << endl;
  cout << setw(leftColumnSpacing) << left << "Wilks Score: " << setw(rightColumnSpacing) << right << wilksScore << endl;
  
  
  return 0;

}
