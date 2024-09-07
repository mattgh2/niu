//***************************************************************************
//
//  hanoi.cpp
//  CSCI 241 Assignment 4 
//
//  Created by Matt Warner (z2004200)
//
//***************************************************************************
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::stoi;

void move(int n, int src_peg, int dest_peg, int temp_peg);

/**
 * Program that uses recursion to solve the Towers of Hanoi problem 
 *
 * @param argc: count of command line arguments
 * @param argv[]: array of command line arguments
 * @return returns 0 upon completion
 */
int main(int argc, char *argv[]){
  
  int n_disks; 

  if (argc == 1)
  {
    cout << "Missing argument\n"
         << "Usage: hanoi number-of-disks\n";
    exit(1);
  }

  for (int i = 0; argv[1][i] != '\0'; i++)
  {
    if (!isdigit(argv[1][i]))
    {
      cout << "Argument must be a number\n"
           << "usage hanoi number-of-disks\n";
      exit(1);
    }
  }

  n_disks = stoi(argv[1]);

  move(n_disks, 1, 2, 3);

  
  return 0;
}
/**
 * Moves the disks from the source peg to the destination peg, using the third peg as temp storage
 *
 * @param Number of disks to move
 * @param The source peg
 * @param The destination peg
 * @param The temporary storage peg
 *
 */
void move(int n, int src_peg, int dest_peg, int temp_peg)
{
  if (n > 0) 
  {
    // Step 1: move n - 1 disks from src_peg to temp_peg, 
    // using dest_peg as a temporary holding peg
    move(n - 1 , src_peg, temp_peg, dest_peg);

    // Step 2: Move the last disk from src_peg to dest_peg
    cout << n << " "  << src_peg << "->" << dest_peg << '\n';

    // Step 3: Perform a recursive call to move n - 1 disks from temp_peg to dest_peg, 
    // using src_peg as a temporary holding peg
    move(n - 1, temp_peg, dest_peg, src_peg);
  }
}
