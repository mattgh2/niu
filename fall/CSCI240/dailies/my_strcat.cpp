//my_strcat daily

#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

void my_strcat(char [], const char []);


int main()
  {
  int test_num;

  char alpha[100] = "Bob";
  char expected_alpha[100] = "Bob";
  
  cout << "Test number? ";
  cin >> test_num;

  //test the my_strcat function with different string based on the test number
  if( test_num == 1 )
    {
    char one[32] = " is going home for the weekend.";

    //add string one to the alpha strings
    my_strcat(alpha, one);
    strcat(expected_alpha, one);
  
    //display the results
    cout << "The string should be \"" << expected_alpha << "\"." << endl;
    cout << "Your my_strcat function created \"" << alpha << "\"." << endl;
    cout << ((strcmp(alpha, expected_alpha) == 0) ? "SUCCESS" : "FAILURE");
    }
  else if( test_num == 2 )
    {
    char two[9] = "CSCI 240";

    //Set the alpha strings to an empty string
    strcpy(alpha, "");
    strcpy(expected_alpha, "");

    //add string two to the end of the alpha strings
    my_strcat(alpha, two);
    strcat(expected_alpha, two);
  
    //display the results
    cout << "The string should be \"" << expected_alpha << "\"." << endl;
    cout << "Your my_strcat function created \"" << alpha << "\"." << endl;
    cout << ((strcmp(alpha, expected_alpha) == 0) ? "SUCCESS" : "FAILURE");
    }
  else if( test_num == 3 )
    {
    char three[32] = " Ross painted";

    //add string three to the alpha strings
    my_strcat(alpha, three);
    strcat(expected_alpha, three);
  
    //display the results
    cout << "The string should be \"" << expected_alpha << "\"." << endl;
    cout << "Your my_strcat function created \"" << alpha << "\"." << endl;
    cout << ((strcmp(alpha, expected_alpha) == 0) ? "SUCCESS" : "FAILURE") << endl << endl;

    //add string two to the end of the alpha strings
    my_strcat(alpha, " happy trees.");
    strcat(expected_alpha, " happy trees.");
  
    //display the results
    cout << "The string should be \"" << expected_alpha << "\"." << endl;
    cout << "Your my_strcat function created \"" << alpha << "\"." << endl;
    cout << ((strcmp(alpha, expected_alpha) == 0) ? "SUCCESS" : "FAILURE");
    }
  else if( test_num == 4 )
    {
    char four[8] = "Pebbles";

    //Set the alpha strings to "Flintstone"
    strcpy(alpha, "Flintstone");
    strcpy(expected_alpha, "Flintstone");

    //add a string literal of ", " to the end of the alpha strings
    my_strcat(alpha, ", ");
    strcat(expected_alpha, ", ");
  
    //display the results
    cout << "The string should be \"" << expected_alpha << "\"." << endl;
    cout << "Your my_strcat function created \"" << alpha << "\"." << endl;
    cout << ((strcmp(alpha, expected_alpha) == 0) ? "SUCCESS" : "FAILURE") << endl << endl;

    //add string two to the end of the alpha strings
    my_strcat(alpha, four);
    strcat(expected_alpha, four);
  
    //display the results
    cout << "The string should be \"" << expected_alpha << "\"." << endl;
    cout << "Your my_strcat function created \"" << alpha << "\"." << endl;
    cout << ((strcmp(alpha, expected_alpha) == 0) ? "SUCCESS" : "FAILURE");
    }
  else if( test_num == 5 )
    {
    char five[5] = "";

    //add an empty string to the end of the alpha strings
    my_strcat(alpha, five);
    strcat(expected_alpha, five);
  
    //display the results
    cout << "The string should be \"" << expected_alpha << "\"." << endl;
    cout << "Your my_strcat function created \"" << alpha << "\"." << endl;
    cout << ((strcmp(alpha, expected_alpha) == 0) ? "SUCCESS" : "FAILURE");
    }

  cout << endl;
  return 0;
  }

int get_length(char array[]){

  int len = 0;
  for (int i=0;array[i]!='\0';i++){
    len++;
  }
  return len;

}

void my_strcat(char destination[], char const source[]){
  
  int sub = get_length(destination);

  for (int j=0;source[j]!='\0';j++){
    destination[sub] = source[j];
    sub++;
  }

  destination[sub] = '\0';

}
  

