//DrawSquare daily
#include <iostream>
#include <iomanip>
using namespace std;

//prototype for the draw_square function
void draw_square(int, char, bool);

int main()
  {
  int square_size;
  char square_color, fill_choice;
  bool fill_square;

  //get the size of the square to be drawn
  cout << "What is the size of the square? ";
  cin >> square_size;

  //get the "color" to draw the square
  cout << "What character should be used to draw the square? ";
  cin >> square_color;
  
  //should the square be filled in or empty?
  cout << "Should the square be filled (F) or empty (E)? ";
  cin >> fill_choice;
  
  //set the boolean variable 
  fill_square = ((fill_choice == 'F') ? true : false);

  cout << endl << "Original Square:" << endl;
  //Draw the square with user input values
  draw_square(square_size, square_color, fill_square);

  cout << endl << "Square with the Opposite Fill Choice:" << endl;
  //draw the square with the opposite fill choice
  draw_square(square_size, square_color, !fill_square);
  

  return 0;
  }

//Code your function below this line
void draw_square(int size, char color, bool fill)
{
  if (size <= 0) // invalid size output
  {
    cout << endl << "Error: invalid size input. The square cannot be drawn." << endl;
  }

  else{
  if (fill){ // prints filled square
    cout << endl;
    for (int i = 0; i < (size * size); i++){ // iterates thorugh an n x n square, print
      if (i != 0 && i % size == 0){ // handles new lines
        cout << endl;
      }
      cout << color;
    }
    cout << endl << endl;
  } // end of filled square drawing
    
  else{ // prints border square
    cout << endl;
    for (int j = 0; j < size; j++){ // iterates through size n rows
      if (j == 0 || j == (size - 1)){ // if j is top or bottom row, fills entire row 
        for (int h = 0; h < size; h++){ // iterating through number of symbols per row to fill
        
          if (h == (size - 1)){ // row needs one more symbol, needs to print symbol and end line.
            cout << color << endl;
          }
          else{ // keeps filling row
            cout << color;
          }
        }
      }
         
      else { // middle section
        for (int l = 0; l < size; l++){ // iterates through each space in middle section rows
          if (l == 0){ // on border, print symbol
            cout << color;
          }
          else if (l == size - 1){ // on border and last slot of row
            cout << color << endl;
          }
          else{ // empty spaces
            cout << " "; // not on border
          }
        }
      }
    }
    cout << endl;
  } // end of border square

  } // end of square drawing

} // end of function

