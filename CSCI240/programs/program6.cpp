/***************************************************************
CSCI 240         Program 6     Fall 2023

Programmer: Matt Warner

Section: 240-001 Date Due: October 20, 2023
Purpose: completes a series of computations. Menu is given to the user for what computation they would like to do.
*/
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// function prototypes
int Menu();
int getValue(string, int, int);
int sumOfSquares(int);
double averageOfCubes(int);
int sumOfASCII(int);
void NIUchant(int);

// main
int main(){
  // prompts for the user
  int userChoice = Menu();
  string sumOfSquaresPrompt = "How many squares will we summate? ";
  string sumOfAsciiPrompt = "How many ASCII values will we summate? ";
  string numberOfCubesPrompt = "How many cubes will we average? ";
  string numberOfChantsPrompt = "How many words will be iterated from the NIU Chant? ";

  //initilizing varibles used in the switch statement
  int numberOfSquares;
  int numberOfAscii;
  int numberOfCubes;
  int numberOfChants;
  int sum;


  while (userChoice != 5){ // keeps running through the program untill user decides to quit
     
    switch (userChoice){ // executes the function corresponding to the users choice
      case 1: // sumOfASCII
        numberOfSquares = getValue(sumOfSquaresPrompt, 2, 20);
        cout << "The sum of the first " << numberOfSquares << " positive numbers squared is " << sumOfSquares(numberOfSquares) << endl;
        break;

      case 2: // averageOfCubes
        numberOfCubes = getValue(numberOfCubesPrompt, 2, 20);
        cout << "The average of the first " << numberOfCubes << " positive numbers cubed is " << averageOfCubes(numberOfCubes) << endl;
        break;

      case 3: // sumOfASCII
        numberOfAscii  = getValue(sumOfAsciiPrompt, 1, 26);
        sum = sumOfASCII(numberOfAscii);
        cout << "The sum of the first " << numberOfAscii << " ASCII character is " << sum << endl;
        break;

      case 4: // NIUchant
        numberOfChants = getValue(numberOfChantsPrompt, 3, 50);
        NIUchant(numberOfChants);
        break;
    }
    cout << endl;
    userChoice = Menu(); // re prompts the user to chose a menu option
  }
  return 0;

}
/***************************************************************
Function:  Menu

Use: - displays the programs menu for user, then prompts the user to decide which computation they want to do.

Arguments: None

Returns: the users menu choice

Notes: 
- users choice get validated before it gets returned
***************************************************************/
int Menu(){

  int choice;

  cout << "Objectives" << endl << endl;

  cout << "1) Calculate the sum of the first N squared numbers" << endl;
  cout << "2) Calculate the average of the first N cubed numbers" << endl;
  cout << "3) Calculate the sum of the ASCII value of the first N characters" << endl;
  cout << "4) Word iterations from the NIU school chant" << endl << endl;
  cout << "5) Quit" << endl << endl;

  cout << "Enter your choice: (1 - 5): ";

  cin >> choice;
  cout << endl;
  while (choice < 0 || choice > 5){ // validates users choice

    cout << "Invalid choice. Please enter a valid number: ";
    cin >> choice;
  }
  

  return choice;
}
/***************************************************************
Function: getValue

Use: gets an integer value from the user that is within a specified range. This value is passed into the function corresponds to the users choice in computation

Arguments: a string that holds the prompt that is displayed to the user, an integer that holds the lower bound for the specified range, 
and an integer that holds the upper bound for the specifed range.

Returns: an integer, that is the users chosen value.

Notes:
***************************************************************/
int getValue(string prompt, int lowerBound, int upperBound){

  int userValue;

  cout << prompt << "( " << lowerBound << " - " << upperBound << "): ";
  cin >> userValue;
  while (userValue > upperBound || userValue < lowerBound) // validation
  {
    cout << userValue << " is an invalid value. Try again: "; // reprompts user to enter a number since last number was not a good value
    cin >> userValue; //
  }
  return userValue;
}
/***************************************************************
Function: sumOfSquares

Use: sums all the squares of positive integers between 1 and functions argument, that is the value grabbed from the user

Arguments: an integer that holds the number of iterations for the functions loop 

Returns: an integer: the sum of each positive number squared

Notes: uses a for loop to iterate through values starting at 1, ending at the value in limit
***************************************************************/
int sumOfSquares(int limit){
  int sum = 0;
  for (int i = 1; i <= limit; i++)
  {
    sum += (i * i); 
  }

  return sum;
}
/***************************************************************
Function: averageOfCubes

Use: calculates the average of cubes, starting with 0, ending at the value stored in the argument

Arguments: an integer that holds the number of integers to use in the calculation.

Returns: a double variable that holds the calculated average of cubes.

Notes: 
***************************************************************/
double averageOfCubes(int limit){
  int sum = 0;
  double average;
  for (int i = 0; i < limit; i++){
    sum += (i * i * i);
  }
  average = (double) sum / limit;
  return average;
}

/***************************************************************
Function: sumOfASCII

Use: calculates the sum of the ASCII values of the first N characters starting with 'a' or 'A'

Arguments: integer value that hold the limit for the number of characters to sum.

Returns: an integer, which is the sum of the ASCII values.

Notes: loops through each character starting with a, adding its integer value to sum.
Loop stops when it reaches the limit.

***************************************************************/
int sumOfASCII(int limit){
  char choice;
  int sum = 0;
  cout << "Would you like to summate (L)owercase or (U)ppercase characters?";
  cin >> choice;

  if (choice == 'L'){ 
    for (char i = 'a'; i < 'a' + limit; i++){
      sum += (int)i;
    }
  }
  else if (choice == 'U'){
    for (char i = 'A'; i < 'A' + limit; i++){
      sum+= (int)i;
    }
  }
  return sum;
}
/***************************************************************
Function: NIUchant

Use: iterates through each word in the niu chant a specific number of times

Arguments: an integer value that is the number of iterations used in the loop that outputs the chant

Returns: Nothing

Notes: -->

Method for outputting chant:
---------------------------------------------
initilizing the variable 'i' to 1 in the for loop, gives us the pattern:
123 - 456 - 789, and so on.
'i' has odd values For the first 3 iterations and outputs "Forward!" when i is not even, and "Together, " when i is even"
After every 3 iterations of i, the pattern reverses its behavior.
So, to  use this logic for our output, a counter is used.
The counter increments by 1 for every 3 iterations, so,
when the counter is holding an even value, i has odd values for "forward" and even values for "together"
when the counter has an odd value, i has even values for "forward" and odd values for "together",
***************************************************************/
void NIUchant(int iterations){
  int counter = 0;
  for (int i = 1; i <= iterations; i++){

    if (counter % 2 == 0){ 
      if (i % 2 != 0){
        cout << "Forward! ";
      }
      else{
        cout << "Together, ";
      }
    }
    else if (counter % 2 != 0){
      if (i % 2 == 0){
      cout << "Forward! ";
      }
      else{
      cout << "Together, ";
      }
    }
    if (i % 3 == 0){
      counter++;
    }
  }
  cout << endl << endl;
}
