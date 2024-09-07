/***************************************************************
CSCI 240         Program 9      Fall 2023

Programmer: Matt Warner

Section: 240-001 

Date Due: December 1, 2023

Purpose: implements a class that creates objects that represent a 3D vector
****************************************************************/
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#define LINE_BREAK cout << endl; for (int i = 0; i < 75; i++) cout << "-"; cout << endl;

//class definition
class Vector {

private:

  // data member
  int coefficients[3];

public: 

  // Method prototypes
  Vector();
  Vector(int[]);
  void set(int[]);
  Vector add(int[]);
  Vector add(Vector);
  Vector multiply(int);
  Vector multiply(int[]);
  Vector multiply(Vector);
  Vector subtract(int[]);
  Vector subtract(Vector);
  bool isEqual(int[]);
  bool isEqual(Vector);
  bool isSimilar(int[]);
  bool isSimilar(Vector);
  string to_string();

};


int main(){
//Test the both constructors and the to_string method
  Vector alpha;

  cout << "Test #1: Testing default constructor and to_string(): alpha == " << alpha.to_string() << endl;

  int slacker[3] = {1, 2, 3};

  Vector beta(slacker);

  cout << "\nTest #2: Testing alternate constructor: beta == " << beta.to_string() << endl;

  LINE_BREAK


  //Test the add method
  cout << "\nTest #3: Testing add functionality." << endl;
  cout << alpha.to_string() << " + " << beta.to_string() << " == " << alpha.add(beta).to_string() << endl;

  slacker[0] = 14;
  slacker[1] = 2;
  slacker[2] = -9;


  //Test the set and subtract methods
  cout << "\nTest #4: Testing set and subtract functionality." << endl;
  alpha.set(slacker);
  cout << alpha.to_string() << " - " << beta.to_string() << " == " << alpha.subtract(beta).to_string() << endl;

  LINE_BREAK


  //Test the multiply methods
  cout << "\nTest #5: Testing scalar multiplication." << endl;
  cout << alpha.to_string() << " * 4 == " << alpha.multiply(4).to_string() << endl;

  cout << "\nTest #6a: Testing cross-product multiplication with a Vector argument." << endl;
  cout << alpha.to_string() << " X " << beta.to_string() << " == " << alpha.multiply(beta).to_string() << endl;

  for (int i = 0; i < 3; i++)
    slacker[i] = (i + 1);

  cout << "\nTest #6b: Testing cross-product multiplication with an integer-array argument." << endl;
  cout << alpha.to_string() << " X <1, 2, 3> == " << alpha.multiply(slacker).to_string() << endl;

  for (int i = 0; i < 3; i++)
    slacker[i] = (i * i);

  alpha.set(slacker);

  LINE_BREAK


  //Test the isEqual method
  cout << "\nTest #7a: Testing for equality (failure)." << endl;
  cout << "Is " << alpha.to_string() << " equal to " << beta.to_string() << "?" << endl;
  if (alpha.isEqual(beta))
    cout << "Yes (this is wrong)." << endl;
  else
    cout << "No (this is correct)." << endl;

  for (int i = 0; i < 3; i++)
    slacker[i] = (i + 1);

  alpha.set(slacker);

  cout << "\nTest #7b: Testing for equality (success)." << endl;
  cout << "Is " << alpha.to_string() << " equal to " << beta.to_string() << "?" << endl;
  if (alpha.isEqual(beta))
    cout << "Yes (this is correct)." << endl;
  else
    cout << "No (this is wrong)." << endl;

  LINE_BREAK


  //Test the isSimilar methods
  cout << "\nTest #8a: Testing for similarity (equal vectors)." << endl;
  cout << "Is " << alpha.to_string() << " similar to " << beta.to_string() << "?" << endl;

  if (alpha.isSimilar(beta))
    cout << "Yes (this is correct)." << endl;
  else
    cout << "No (this is wrong)." << endl;

  for (int i = 0; i < 3; i++)
    slacker[i] = (i + 1) * 6;

  beta.set(slacker);

  cout << "\nTest #8b: Testing for similarity (scalar vectors)." << endl;
  cout << "Is " << alpha.to_string() << " similar to " << beta.to_string() << "?" << endl;

  if (alpha.isSimilar(beta))
    cout << "Yes (this is correct)." << endl;
  else
    cout << "No (this is wrong)." << endl;

  cout << "\nTest #8c: Testing for similarity (scalar vectors)." << endl;
  cout << "Is " << beta.to_string() << " similar to " << alpha.to_string() << "?" << endl;

  if (beta.isSimilar(alpha))
    cout << "Yes (this is correct)." << endl;
  else
    cout << "No (this is wrong)." << endl;

  for (int i = 0; i < 3; i++)
    slacker[i] = (i * i * i) + (10 - i);

  beta.set(slacker);

  cout << "\nTest #8d: Testing for similarity (failure)." << endl;
  cout << "Is " << alpha.to_string() << " similar to " << beta.to_string() << "?" << endl;

  if (alpha.isSimilar(beta))
    cout << "Yes (this is wrong)." << endl;
  else
    cout << "No (this is correct)." << endl;

  return 0;
}


/***************************************************************
Method: Vector

Use: Default constructor that sets the values of the Vector object to 0

Arguments: None


Returns: Nothing

Notes: Simply fills the coefficients array with zeros
***************************************************************/


Vector::Vector(){
  for (int i = 0; i<3;i++){
    coefficients[i] = 0;
  }
}


/***************************************************************
Method: Vector

Use: Alternate constructor used to fill vector object with specific values

Arguments: int _values[]: an array of values that represent the Vector objects coefficients.


Returns: Nothing

Notes: calls the set function so we dont repeat code
***************************************************************/


Vector::Vector(int _values[]){
 set(_values);
}


/***************************************************************
Method: set

Use: sets the coefficients for the Vector object
 
Arguments: int _values[]: an array of values that are to be set as the Vector objects coefficients


Returns: nothing

Notes: Simply copies the values from the array passed in into the data member array 
***************************************************************/


void Vector::set(int _values[]){
  for (int i = 0;i < 3; i++){
    coefficients[i] = _values[i];
  }
}


/***************************************************************
Method: add

Use: Sums the values from the private array and the array of integers passed into the function

Arguments: int _values[]: an array of integers 


Returns: A Vector object that contains the sum of the corresponding values

Notes: 
***************************************************************/


Vector Vector::add(int _values[]){
  Vector Sum; // Creates sum object
  for (int i = 0; i < 3; i++){
    Sum.coefficients[i] = coefficients[i] + _values[i];
  }
  return Sum;
}


/***************************************************************
Method: add (overloaded method)

Use: Same Use as previous add() function

Arguments: Vector _other: A Vector object that contains the second set of values to sum


Returns: A Vector Object that contains the sum

Notes: Simply utilizes the already created add method since it has an identical purpose.
***************************************************************/


Vector Vector::add(Vector _other){
  Vector Sum = add(_other.coefficients);
  return Sum;
}


/***************************************************************
Method: multiply

Use: multiplys the private arrays coefficients by some constant

Arguments: int scalar: the constant used in the multiplication


Returns: A Vector object that contains our result

Notes:
***************************************************************/


Vector Vector::multiply(int scalar){
  Vector Prod; 
  for (int i = 0; i < 3;i++){
    Prod.coefficients[i] = coefficients[i] * scalar;
  }
  return Prod;
}


/***************************************************************
Method: multiply

Use: Performs calculation that gets the cross product of two vectors

Arguments: int _values[]: contains the second vectors values


Returns: A Vector object that is the result of the calculations

Notes:
***************************************************************/


Vector Vector::multiply(int _values[]){
  Vector CrossProd; 
  CrossProd.coefficients[0] = (coefficients[1] * _values[2]) - (coefficients[2] * _values[1]);
  CrossProd.coefficients[1] = (coefficients[2] * _values[0]) - (coefficients[0] * _values[2]);
  CrossProd.coefficients[2] = (coefficients[0] * _values[1]) - (coefficients[1] * _values[0]);
  return CrossProd;
}


/***************************************************************
Method: multiply

Use: identical use as the above multiply() method

Arguments: Vector _other: a Vector object that contains the second vector's values used in the calculations


Returns: A vector object that is the result of the calculations

Notes: calls the already created function, since re-implementing this method again is not neccessary
***************************************************************/


Vector Vector::multiply(Vector _other){
 Vector CrossProd = multiply(_other.coefficients);
 return CrossProd;
}


/***************************************************************
Method: subtract 

Use: Performs calculation that gets the difference of two vector's coefficients

Arguments: int _values: array of integers that represent the second Vector objects coefficients


Returns: A Vector object that contains the difference of values

Notes: simply subtracts the corresponding values to get the difference
***************************************************************/


Vector Vector::subtract(int _values[]){
  Vector Diff;
  for (int i = 0; i <3;i++){
    Diff.coefficients[i] = coefficients[i] - _values[i];
  }
  return Diff;
}


/***************************************************************
Method: subtract

Use: Same exact use as the above subtract() method

Arguments: Vector _other: A Vector object that contains the second vector's coefficients used in calculations


Returns: A Vector object that contains the differences

Notes: 
***************************************************************/


Vector Vector::subtract(Vector _other){
  Vector Diff;
  for (int i =0; i<3;i++){
    Diff.coefficients[i] = coefficients[i] - _other.coefficients[i];
  }
  return Diff;
}


/***************************************************************
Method: isEqual

Use: compares two Vector objects to conclude if they hold identical values

Arguments:  int _values: an array of integers that represent the second vector's values


Returns: bool IsSame: a booleon that holds true or false depending on if the values are identical or not

Notes: compares both array of coefficients, if values differ, loop breaks and returns false
***************************************************************/


bool Vector::isEqual(int _values[]){
  bool IsSame = false;
  for (int i=0;i<3;i++){
    if (coefficients[i] == _values[i]){
      IsSame = true;
    }
    else{
      IsSame = false;
      break;
    }
  }
  return IsSame;
}


/***************************************************************
Method: isEqual

Use: Same use as above isEqual() method

Arguments: Vector _other: A vector object that contains values of second vector used in comparison


Returns: IsSame: A booleon that holds a value of true or false depending on the result of the comparison

Notes: calls the previous method to avoid redundencyh
***************************************************************/


bool Vector::isEqual(Vector _other){
  bool IsSame = isEqual(_other.coefficients);
  return IsSame;
}


/***************************************************************
Method: isSimilar

Use: compares two vector objects to determine if the direction of the vectors are the same

Arguments:  int _values: an array of values that contain the second vectors coefficients


Returns: bool Similar: a booleon that holds a value of true if similar and false if not

Notes: 
***************************************************************/


bool Vector::isSimilar(int _values[]){
  bool Similar; // variable to be returned
  
  double TestValue = ((double)coefficients[0] / _values[0]);
  double Comparison;
  for (int i = 0; i < 3; i++){   
    if (_values[i] == 0){ // makes sure we dont divide by zero
      Similar = false;
      break;
    }
    Comparison = ((double)coefficients[i] / _values[i]);
    if (Comparison == TestValue){
      Similar = true;
    }else{
      Similar = false;
      break;
    }
  }
  return Similar;
}


/***************************************************************
Method: isSimilar

Use: Same use as above isSimilar() method

Arguments: Vector _other: a vector object that holds the coefficients for the second vector


Returns: a booleon is true if similar, and false if not

Notes: 
***************************************************************/


bool Vector::isSimilar(Vector _other){
  bool Similar = isSimilar(_other.coefficients);
  return Similar;
}


/***************************************************************
Method: to_string

Use: Creates a Mathmatical representation of the vector objects

Arguments: None


Returns: A string that is the representation of the vectors

Notes:
***************************************************************/


string Vector::to_string(){
  string representation = "<" + std::to_string(coefficients[0]) + ", " + std::to_string(coefficients[1]) + ", " + std::to_string(coefficients[2]) + ">";
  return representation;
}



