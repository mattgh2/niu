#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <cstdlib>

using namespace std;

// Macros for formatting the output
#define FLSPACE  right << setw(18)            // Width of 18 for First / Last name
#define TITLESPACE right << setw(37) << " "   // width of 37 for title
#define NUMSPACE right << setw(10)            // width of 10 for numeric values
#define LINE_BREAK cout << endl; for (int i = 0; i < 96; i++) cout << "-"; cout << endl;    // long line of "-"


class
PowerLifter {

private:
  // Data Members
  char firstName[15], lastName[15];
  int maxSquat, maxBench, maxDeadlift;
  float wilksCoeff;
  
public:

// Method Prototypes
PowerLifter();
void setFirst(const char[]);
void setLast(const char[]);
void setCoef(float);
int getSquat();
void setSquat(int);
int getBench();
void setBench(int);
int getDeadlift();
void setDeadlift(int);
int getTotal();
int wilksScore();
int compare(PowerLifter);
void display();

};  

              // Function Prototypes
void sortby(PowerLifter[], int, const char[]);
void swap(PowerLifter&, PowerLifter&);
int readFile(PowerLifter[], const char[]);
void printPowerLifters(PowerLifter[], int, const char[]);


int main(){

  PowerLifter powerlifters[30];       // initilizing  array of powerlifters
  char fileName[15] = "lifters.txt";  // declaring filename passed into readFile()
  int lifterCount;                    // initilzing variable for storing amount of lifters 


  lifterCount = readFile(powerlifters, fileName);         // gets lifter count and fills array of powerlifters
                                                          
  cout << 
      "File processing has been complete. We have " <<
      lifterCount << 
      " powerlifters recorded." << 
      endl << endl;


  printPowerLifters(powerlifters, lifterCount, "Default List of PowerLifters");        // Default list
  

  sortby(powerlifters, lifterCount, "Total");                                          // Sorted by "Total"
  printPowerLifters(powerlifters, lifterCount, "PowerLifters Ranked by Total");       
   

  sortby(powerlifters, lifterCount, "Wilks");                                         // Sorted by "Wilks"
  printPowerLifters(powerlifters, lifterCount, "PowerLifters Ranked by Wilks");        


  sortby(powerlifters, lifterCount, "Squat");                                         // Sorted by "Squat"
  printPowerLifters(powerlifters, lifterCount, "PowerLifters Ranked by Squat");        


  sortby(powerlifters, lifterCount, "Bench");                                         // Sorted by "Bench"
  printPowerLifters(powerlifters, lifterCount, "PowerLifters Ranked by Bench");        


  sortby(powerlifters, lifterCount, "Deadlift");                                         // Sorted by "Bench"
  printPowerLifters(powerlifters, lifterCount, "PowerLifters Ranked by Deadlift");        


  return 0;
} 
//---------------------------------------Methods-------------------------------------------------

/***************************************************************
Method: PowerLifter (Default Constructor)

Use: Assigns default values to class attributes

Arguments: None


Returns: Nothing

Notes:
***************************************************************/
PowerLifter::PowerLifter(){
  strcpy(this->firstName, "No");
  this->wilksCoeff = 1.0;
  this->maxSquat = -1, this->maxBench = -1, this->maxDeadlift = -1;
}
/***************************************************************
Method: setFirst

Use: Sets a value to the firstName attributes

Arguments: char const newFirst[]: a char array that holds the value to be assigned to the firstName attribute


Returns: Nothing

Notes:
***************************************************************/
void PowerLifter::setFirst(char const newFirst[]){
  int i;
  for (i = 0; newFirst[i]!='\0';i++){
    this->firstName[i] = newFirst[i];
  }
  firstName[i] = '\0';    // finishes string by adding null terminator
}
/***************************************************************
Method: SetLast

Use: takes in a character array that holds a last name and sets it as the last name attribute for the class

Arguments: char const newLast[]: a character array that holds a last name


Returns: Nothing

Notes:
***************************************************************/
void PowerLifter::setLast(char const newLast[]){
  int i;
  for (i=0;newLast[i]!='\0';i++){
    this->lastName[i] = newLast[i];
  }
  lastName[i] = '\0';      // adds null terminator
}
/***************************************************************
Method: setCoef

Use: assings a Wilkscoefficent to the wilksCoeff data member

Arguments: float newCoef: a float variable that holds a wilks coefficent


Returns: Nothing

Notes:
***************************************************************/
void PowerLifter::setCoef(float newCoef){
 this->wilksCoeff = newCoef; 
}
/***************************************************************
Method: getSquat 

Use: returns an objects  maxSquat attribute
 
Arguments: None


Returns: MaxSquat

Notes: 
***************************************************************/
int PowerLifter::getSquat(){ return maxSquat;}
/***************************************************************
Method: setSquat

Use: assings a maxSquat value to the maxSquat class attribute

Arguments: int newBench: the value that will be set to the maxSquat attribute

Returns: Nothing
 
Notes: Validates the value passed in before assigining it the objects data member
***************************************************************/
void PowerLifter::setSquat(int newSquat) {

  if (newSquat>-1){         // validation
    this->maxSquat=newSquat;
  }
}
/***************************************************************
Method: getBench

Use: returns the value of an objects maxBench attribute

Arguments: None

Returns: maxBench: the objects maxBench attribute

Notes:
***************************************************************/
int PowerLifter::getBench(){ return maxBench; }
/***************************************************************
Method: setBench

Use: sets a value to the maxBench class attribute

Arguments: int newBench: the value that will be set to the maxBench attribute


Returns: Nothing

Notes: Validates before returning
***************************************************************/
void PowerLifter::setBench(int newBench){
  if (newBench > -1){
    this->maxBench = newBench;
  }
}
/***************************************************************
Method: getDeadlift

Use: returns the objects maxDeadlift attribute

Argumens: None


Returns: maxDeadlift: the class attribute maxDeadlift

Notes:
***************************************************************/
int PowerLifter::getDeadlift(){
  return this->maxDeadlift;
}
/***************************************************************
Method: setDeadlift
 
Use: sets a value to the maxDeadlift class attribute

Arguments: int newDeadlift: the value that will be set to the attribute

Returns: Nothing

Notes: validates
***************************************************************/
void PowerLifter::setDeadlift(int newDeadlift){
  if (newDeadlift>-1){
    this->maxDeadlift = newDeadlift;
  }
}
/***************************************************************
Method: getTotal

Use: calculates the total of the three integer data members

Arguments: None

Returns: LiftingSum: The calculated total

Notes:
***************************************************************/
int PowerLifter::getTotal(){
  int LiftingSum = this->maxSquat+this->maxBench+this->maxDeadlift;
  return LiftingSum;
}
/***************************************************************
Method: wilksScore

Use: Performs calculating to get the objects wilks score

Arguments: None

Returns: the calculated wilks score

Notes: calculation being performed -> total * wilksCoeff
***************************************************************/
int PowerLifter::wilksScore(){
  return (int)(getTotal() * this->wilksCoeff);
}
/***************************************************************
Method: compare

Use: compares the wilks score of an object invoked by the method against the object passed in.

Arguments: PowerLifter other: an object of the PowerLifter class, who's wilks score is being used in comparison

Returns: -1, 0, 1, depending on the outcome of the comparison

Notes:
***************************************************************/
int PowerLifter::compare(PowerLifter other){
  if (other.wilksScore() < wilksScore()){ 
    return -1;
  } else if (other.wilksScore() == wilksScore()){
      return 0;
    } else {
      return 1;
    }
}
/***************************************************************
Method: display

Use: displays a formatted PowerLifter object

Arguments: None


Returns: Nothing

Notes:
***************************************************************/
void PowerLifter::display(){
  cout <<  fixed << setprecision(4);
  cout << FLSPACE << this->firstName << FLSPACE << this->
    lastName << NUMSPACE << this->wilksCoeff << NUMSPACE << this->
    maxSquat << NUMSPACE << this->maxBench << NUMSPACE << this->
    maxDeadlift << NUMSPACE << getTotal () << NUMSPACE << wilksScore ();
}
//---------------------------------------FUNCTIONS-------------------------------------------------  


/***************************************************************
Function: sortby

Use: Uses selection sort to sort the array of objects in decending order

Arguments: PowerLifter array[]: an array of PowerLifter objects, 
           int size: the size of the array, 
           const char type[]: the type that determines which data member is used for sorting

Returns: Nothing

Notes: uses strcmp() to determine which member is used for sorting
***************************************************************/
void sortby(PowerLifter array[], int size, const char type[]){

  if (strcmp(type, "Squat") == 0){
    for (int i = 0;i<size-1;i++){
      int targetIndex = i;
      for (int j = i+1;j<size;j++){
        if (array[j].getSquat() > array[targetIndex].getSquat()){
          targetIndex = j;
        }
      }
      if (i != targetIndex){
        swap(array[i], array[targetIndex]);
      }
    }
  }

  else if (strcmp(type, "Bench") == 0){
    for (int i = 0;i<size-1;i++){
      int targetIndex = i;
      for (int j = i+1;j<size;j++){
        if (array[j].getBench() > array[targetIndex].getBench()){
          targetIndex = j;
        }
      }
      if (i != targetIndex){
        swap(array[i], array[targetIndex]);
      }
    }
  }

  else if (strcmp(type, "Deadlift") == 0){
    for (int i = 0;i<size-1;i++){
      int targetIndex = i;
      for (int j = i+1;j<size;j++){
        if (array[j].getDeadlift() > array[targetIndex].getDeadlift()){
          targetIndex = j;
        }
      }
      if (i != targetIndex){
        swap(array[i], array[targetIndex]);
      }
    }
  }

  else if (strcmp(type, "Total") == 0){
    for (int i = 0;i<size-1;i++){
      int targetIndex = i;
      for (int j = i+1;j<size;j++){
        if (array[j].getTotal() > array[targetIndex].getTotal()){
          targetIndex = j;
        }
      }
      if (i != targetIndex){
        swap(array[i], array[targetIndex]);
      }
    }
  }

  else if (strcmp(type, "Wilks") == 0){
    for (int i = 0;i<size-1;i++){
      int targetIndex = i;
      for (int j = i+1;j<size;j++){
        if (array[j].wilksScore() > array[targetIndex].wilksScore()){
          targetIndex = j;
        }
      }
      if (i != targetIndex){
        swap(array[i], array[targetIndex]);
      }
    }
  }

  else {
    cout << "Invalid Input" << endl;
  }
}
/***************************************************************
Function: swap

Use: a helper function for the sortby function that is called when two array elements need to be swapped

Arguments: PowerLifter &val1, PowerLifter &val2: two refereneces to PowerLifter objects

Returns: Nothing

Notes: uses pass-by-reference to directly modify the values passed into the function
***************************************************************/
void swap(PowerLifter &val1, PowerLifter &val2){
  PowerLifter temp = val1;
  val1 = val2;
  val2 = temp;
}

/***************************************************************
Function: readFile

Use: Fills array of objects initilized in int main(), also counts the total number of lifters from the file

Arguments:  PowerLifter array[]: an array of PowerLifter objects, char const fileName: the name of the file containing the powerlifter data.

Returns: The total number of powerlifters

Notes:
***************************************************************/
int readFile( PowerLifter array[], char const fileName[]){

  ifstream myFile; 
  myFile.open( fileName );

  if (myFile.fail()){                                 // checks if file actually opened
    cout << "Could not open / find " << fileName;     // error message
    exit(-1);
  }

  char firstName[15], lastName[15];     //  temp data storage
  int Squat, Bench, Deadlift;
  float wilks;

  int index = 0, objectCount;;     // counters 

  myFile >> firstName;      // primary Read
                            
  while (myFile){

    // grabs data from file
    myFile >> lastName >> wilks >> Squat >> Bench >> Deadlift;

    // moving data to objects
    array[index].setFirst(firstName);
    array[index].setLast(lastName);
    array[index].setCoef(wilks);
    array[index].setSquat(Squat);
    array[index].setBench(Bench);
    array[index].setDeadlift(Deadlift);

    index++; 
    objectCount++;

    myFile >> firstName;      // Secondary Read
  }

  myFile.close();

  objectCount = index; // gets object count

  return objectCount;
}

/***************************************************************
Function: printPowerLifters

Use: Outputs the full array of Powerlifters

Arguments: PowerLifter array[]: an array of powerlifters, int size: the number of powerlifters, char const title[]: an character array that holds the output title

Returns: Nothing

Notes: // makes use of macros defined at the top of the program
***************************************************************/
void printPowerLifters(PowerLifter array[], int size, char const title[]){

  cout << TITLESPACE << title << endl;
  cout << FLSPACE << "First Name" << FLSPACE << "Last Name" 
       << NUMSPACE << "Wilks" << NUMSPACE << "Squat" << NUMSPACE 
       << "Bench" << NUMSPACE << "DL" << NUMSPACE 
       << "Total" << NUMSPACE << "W. Score";
  LINE_BREAK;

  for (int i=0; i < size; i++){
   array[i].display();
   cout << endl;
  }
  cout << endl;
}


