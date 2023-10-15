/***************************************************************
CSCI 240         Program 6     Fall 2023

Programmer: Matt Warner

Section: 240-001

Date Due: October 20, 2023

Purpose: 
*/
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
/***************************************************************
Function: 

Use:

Arguments: 

Returns:

Notes:
***************************************************************/
int Menu(){

  int choice; 

  cout << "1) Calculate the sum of the first N squared numbers" << endl;
  cout << "2) Calculate the average of the first N cubed numbers" << endl;
  cout << "3) Calculate the sum of the ASCII value of the first N characters" << endl;
  cout << "4) Word iterations from the NIU school chant" << endl << endl;
  cout << "5) Quit" << endl << endl;

  cout << "Enter your choice: (1 - 5): ";
  cin >> choice;

  while (choice < 0 || choice > 5){

    cout << "Invalid choice. Please enter a valid number: ";
    cin >> choice;

  }

  return choice;
}
/***************************************************************
Function: 

Use:

Arguments: 

Returns:

Notes:
***************************************************************/
// gets a number. Purpose unkown
int getValue(string prompt, int lowerBound, int upperBound){

  int userValue;

  cout << prompt;
  cin >> userValue;
  while (userValue > upperBound || userValue < lowerBound)
  {
    cout << "Invalid value. Try again: ";
    cin >> userValue;
  }
  return userValue;
}
/***************************************************************
Function: 

Use:

Arguments: 

Returns:

Notes:
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
Function: 

Use:

Arguments: 

Returns:

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

Use: 

Arguments: int limit

Returns: sum

Notes:

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

Arguments: int iterations

Returns: Nothing

Notes:

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



int main(){

  choice = Menu();
  switch (choice){
    case 1:

  }
  return 0;

}
