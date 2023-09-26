/***************************************************************
CSCI 240         Program 4     Fall 2023

Programmer: Matt Warner

Section: 240-001

Date Due: September 29, 2023

Purpose: This program uses a random number generator to generate three sets of random numbers.
***************************************************************/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

// constants
const int SEED_VALUE = 17;
const int SET_ONE_MAX = 52;
const int SET_TWO_MAX = 80;
const int SET_THREE_MAX = 100;

// constants for random doubles
const double RAND_MIN = 0;
const double RANDOM_MAX = 200;

// output variables
const int LINE_MAX = 6;
const int SPACING = 13;

int main(){
   
 // initilizing variables that will store random nums
  int randNum;
  double randDoubleNum;

  srand(SEED_VALUE); // sets seed value for rand()
 
  // first set (for loop)
  cout << "Set 1 has exactly " << SET_ONE_MAX << " values";
  for (int i = 0; i < SET_ONE_MAX; i++)
  {
    randNum = rand(); // generates random value for each iteration

    if (i % LINE_MAX ==  0) // creates initial new line and a new line after 6 values printed 
    { 
      cout << endl;
    } 

    cout << right << setw(SPACING) << randNum; // prints random num to console

  }

  // second set (while loop)
  int numOfIterations = rand() % SET_TWO_MAX + 1; // stores number of iterations for the while loop, set to a random number between 1 and 80
  int _count = 0; // loop control variable

  cout << endl << endl <<  "Set 2 has exactly " << numOfIterations << " values";
  while (_count < numOfIterations){ 

    randNum = rand(); 

    //  same method used in for loop for creating new line after 6 values are printed
    if (_count % LINE_MAX == 0)
    {
      cout << endl;
    }

    // prints random number to console
    cout << right << setw(SPACING) << randNum;

    _count++; // increments loop control variable
  }
  
  // third set (do-while loop)
  _count = 0; // loop control variable
  numOfIterations = rand() % SET_THREE_MAX + 1; // generates the number of iterations for the loop (1-100)

  cout << endl << endl << "Set 3 has exactly " << numOfIterations << " values";
  do 
  {
   // generates random double value
   randDoubleNum = RAND_MIN + (rand() / (RAND_MAX / (RANDOM_MAX - RAND_MIN)));

   if (_count % LINE_MAX == 0)
   {
     cout << endl;
   }
   cout << fixed << setprecision(4); // sets amount of decimal places displayed to exactly 4
   cout << right << setw(SPACING) << randDoubleNum;

   _count++;
  } while(_count < numOfIterations);


  return 0;
}
