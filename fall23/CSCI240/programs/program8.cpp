/***************************************************************
CSCI 240         Program 8    Fall 2023

Programmer: Matt Warner

Section: 240-001 

Date Due:November, 10th 2023

Purpose: implements a date class that is used to create calander dates.
****************************************************************/
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
using namespace std;

// Global Arrays
string MONTH_NAMES[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
int DAY_COUNT[12] = {31, 28, 31,30,31,30,31,31,30,31,30,31};


class Date {

  private:
    // data members
    int day;
    string month;
    int year;

  public:
    // method prototypes
    Date();
    Date(int, string, int);
    void set_date(int, string, int);
    string get_day_name();
    string get_day();
    string get_month();
    int get_year();
    string get_date();
};

int main(){
  srand(17); // setting seed
  
  // creating objects
  Date date1 = Date(); // Default Constructor
  Date date2 = Date(); // Default Constructor
  Date date3 = Date(10, "December", 1815); // Alternate Constructor
  
  // test 1
  cout  << "Test 1: Constructors and get_date method" << endl << endl;
  cout << "The first date is " << date1.get_date() << endl << endl;
  cout << "The second date is " << date2.get_date() << endl << endl;
  cout <<"The third date is " << date3.get_date() << endl << endl;
  
  // test 2
  cout << "\nTest 2: set_date method" << endl <<endl;

  date2.set_date(9, "December", 1906);
  cout << "Grace Hopper's birthday is " << date2.get_date() << endl << endl;

  // test 3a
  cout << "\nTest 3a: set_date method with invalid values" << endl << endl;

  date2.set_date(29, "February", 2023);
  cout << "This should print as Feb. 1st: " << date2.get_date() << endl << endl;
    
  // test 3b
  cout << "\nTest 3b: set_date method that tests leap year recognition" << endl << endl;

  date2.set_date(29,"February", 2020);
  cout << "Leap Year! " << date2.get_date() << endl <<endl;
  
  // test 4
  cout << "\nTest 4: set_date method with a made-up month" << endl << endl;

  date3.set_date(14, "Jupiter", 1011);
  cout << "This should default to January: " << date3.get_date() << endl << endl;

  // test 5a
  cout  << "\nTest 5a: testing whether '12' comes back as '12th' and not '12nd'." << endl << endl;

  date1.set_date(12, "March", 1999);
  cout << "First date == " << date1.get_day() << endl <<endl;

  // test 5b
  cout << "\nTest 5b: testing whether '23' comes back as '23rd' and not '23th'." << endl << endl;

  date1.set_date(23, "March", 1999);
  cout << "First date == " << date1.get_day() <<endl << endl;

  // test 6
  cout << "\nTest 6: Testing for mapping the 26th day of the month to a Friday." << endl <<endl;

  date3.set_date(26, "February", 1982);
  cout << "There's a 1 in 7 chance this is the actual day Brian Shaw was born... " << date3.get_day_name() << endl;


  return 0;
}
/***************************************************************
Method: Default Constructor

Use: assigns random attributes to objects when used

Arguments: None


Returns: Nothing

Notes:
***************************************************************/
Date::Date(){

  year = 1000 + rand() % (2024 - 1000 + 1); // assigns random year 1000 - 2024
  int monthNum = rand() % 12; // generates a random month
  month = MONTH_NAMES[monthNum]; // assigns the random month to data member: month

  if (year % 4 ==0 && month == "February"){ // checks if leap year
    day = 1 + rand() % 29; // generates a random day, accounting for the extra day in February
  }
  else{ // non leap year case
    day = 1 + rand() % DAY_COUNT[monthNum];
  }
}

/***************************************************************
Method: Alternate Constructor

Use: Assgins values to the object passed in by the user

Arguments: 3 arguments that make up the date
           int Day: Objects day of the month
           string Month: The objects specific month
           int Year: The objects year


Returns: Nothing

Notes: calls the set_date method to validate, and set the class attributes
***************************************************************/
Date::Date(int Day, string Month, int Year){
  set_date(Day, Month, Year);
}
/***************************************************************
Method: set_date

Use: validates, and gives values to the data members of the class

Arguments: int newDay:
           string newMonth: 
           int newYear:

Returns: Nothing

Notes: Before value gets assigned to the object, the value gets validated, also handles special case for leap years
***************************************************************/
void Date::set_date (int newDay, string newMonth, int newYear){
  bool validMonth = false, validYear= false, leapYear = false, validDay = false;
  int index;
  for (int i = 0; i < 12; i++){ // iterates through the global array of months to check if the month passed into the method is valid
    if (newMonth == MONTH_NAMES[i]){ 
      month = newMonth;
      validMonth = true;
      index = i;
      break;
    }
  }
  if (validMonth == false){ // if month did not pass valildation, defaults to January
    month = "January";
    index = 0;
  }

  if (newYear >= 1000 && newYear <= 2024){ // checks if year is valid before assigning it to the data member
    year = newYear;
    validYear = true;
    if (newYear % 4 == 0){ // checks for leap year
      leapYear = true;
    }
    else{ 
      leapYear = false;
    }
  } 
  if (!validYear){
    year = 1999; // defauts to 1999 if a invalid year is entered
  }
  if (leapYear && month == "February"){ // special case for leap year dates
      if (newDay > 0 && newDay <= 29){
        day = newDay;
        validDay = true;
      }
  }
  else{ // case for not a leap year
    if (newDay > 0 && newDay <= DAY_COUNT[index]){
      day = newDay;
      validDay = true;
    }
  }
  if (!validDay){ // defaults to 1 if a valid day is not entered
    day = 1;
  }
}

/***************************************************************
Method: get_day_name

Use: finds the day that corresponds to the date

Arguments: None

Returns: The day corresponding to the date

Notes: logic for finding the day:
Performs mod arithmetic. Since the first week is 1 -7, performing this operation on any given valid date will result in a number 1 - 6, which directly corresponds to its correct day of the week.
If The day is a sunday, performing the mod arithmetic will result in a 0, since handeling a zero breaks the program, we need to handle it seperately.
***************************************************************/
string Date::get_day_name(){

  string Day;
  int dayNum;
  string dayNames[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
  dayNum = (day % 7); 
  if(dayNum == 0){
    Day = "Sunday";
  }
  else{
    Day = dayNames[dayNum - 1];
  }
  return Day;
}
/***************************************************************
Method: get_day

Use: finds the correct suffix for the given day of the month

Arguments: None


Returns: the day of the month with its corresponding suffix at the end

Notes: 
***************************************************************/
string Date::get_day(){ 
  string suffix;
  if (day > 3 && day <21){ // all of these will be 'th' suffix
   suffix = "th";
  }
  else { // performs mod arithmetic to get the last digit, then assigns it the corresponding suffix
    if (day % 10 == 1){
      suffix = "st";
    }
    else if (day % 10 == 2){
      suffix = "nd";
    }
    else if (day % 10 == 3){
      suffix = "rd";
    }
    else {
      suffix = "th";
    }
  }
     
  return to_string(day) + suffix;
}
/***************************************************************
Method:get_month

Use: creates and returns a copy of the month data member

Arguments: None


Returns: monthCopy: A copy of the month data member

Notes:
***************************************************************/
string Date::get_month(){
  string monthCopy = month; // creates a copy of the month
  return monthCopy;
}
/***************************************************************
Function: get_year

Use: creates and returns a copy of the year data member

Arguments: None

Returns: yearCopy: A copy of the year data member

Notes:
***************************************************************/
int Date::get_year(){
  int yearCopy = year; // creates a copy of the year
  return yearCopy;
}
/***************************************************************
Method: get_date

Use: Builds the string that is the compleate date of the given object

Arguments: None


Returns: The complete, formatted date

Notes:
***************************************************************/
string Date::get_date(){
  string fullDate = get_day_name() + " " + get_month() + " " + get_day() + ", " + to_string(get_year()); // builds the full date of an object
  return fullDate;
}

