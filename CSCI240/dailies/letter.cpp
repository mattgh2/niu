//Letter Grade daily - main

#include <iostream>
#include <iomanip>

using namespace std;


int main()
{
  int score;
  char letter_grade = 'X';
  
  //Get the score from the user1
  cout << "What is the test score? ";
  cin >> score;
  
  //Determine the letter grade (write your code after this line)
  
  if (score <= 67){
    letter_grade = 'F';

  }
  else if (score > 67 && score <=75 ){
    letter_grade = 'D';
  }

  else if (score > 75 && score <=83 ){
    letter_grade = 'C'; 
  }

  else if (score > 83 && score <= 91 ){
    letter_grade = 'B';
  }
  else{
    letter_grade = 'A';
  }

  //Display the score and letter grade
  cout << endl << "The score " << score << " earns the grade " << letter_grade << endl;
  
  return 0;
}
