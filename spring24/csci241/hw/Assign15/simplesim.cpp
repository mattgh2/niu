//********************************************************************
//
// simplesim.cpp
// CSCI 241 Assignment 8
//
// Created by Matt Warner
//
//********************************************************************

#include <iostream>
#include <iomanip>
#include "simplesim.h"
#include "sml.h"

using std::cin;
using std::cout;
using std::endl;
using std::internal;
using std::left;
using std::noshowpos;
using std::right;
using std::setfill;
using std::setw;
using std::showpos;

// macros
#define MAX_MEMORY 100
#define REG_LABEL_FORMAT left << setw(24) << setfill(' ')
#define FOUR_DIGIT_SIGNED_FORMAT setw(5) << internal << setfill('0') << showpos
#define TWO_DIGIT_UNSIGNED_FORMAT setw(2) << right << setfill('0') << noshowpos
#define ROW_HEADER_FORMAT setw(2) << right << setfill(' ') << noshowpos
#define COL_HEADER_FORMAT setw(6) << right << setfill(' ') << noshowpos

/**
 * Initializes the Simplesim's memory to default values.
 */
simplesim::simplesim()
{
    // Assigns DEFAULT to all elements of the memory array.
    for (int i = 0; i < MAX_MEMORY; i++)
       memory[i] = DEFAULT;

    accumulator = 0;
    instruction_counter = 0;
    instruction_register = 0;
    operation_code = 0;
    operand = 0;
}

/**
 * Loads an SML program into the Simplesim's memory.
 *
 * @return Returns true if a valid program is successfully loaded into 
 *         memory; otherwise, false.
 */
bool simplesim::load_program()
{
    int count = 0;          // Instruction count.;
    int instruction = 0;    // Holds instruction read.

    // While not EOF and we have not encountered the sentinel value...
    while (cin >> instruction && instruction != -99999)
    {
        // Check for an invalid word. If invalid, print error message
        // and return false.
        if (instruction < -9999 || instruction > 9999)
        {
            cout << "*** ABEND: pgm load: invalid word ***" << endl;
            return false;
        }

        // Check for too large a program. If count is outside the 
        // boundaries of the memory array, print error message and
        // return false.
        if (count >= 100)
        {
            cout << "*** ABEND: pgm load: pgm too large ***" << endl;
            return false;
        }

        // Add the instruction to the memory array at subscript count.
        memory[count] = instruction;

        // Increment instruction count by 1.
        count++;
	}

    return true;
}

/**
 * Executes an SML program loaded into the Simplesim's memory.
 */
void simplesim::execute_program()
{
    bool done = false;

    while (!done)
    {
        // Check for an addressability error. If instruction_counter
        // is outside the boundaries of the memory array, print error
        // and return.
        if (instruction_counter < 0 || instruction_counter > 99)
        {
            cout << "*** ABEND: addressability error ***" << endl;
            return;
        }
        
        // Fetch the instruction and extract the operation code
        // and operand.
        instruction_register = memory[instruction_counter];
		operation_code = instruction_register / 100;
		operand = instruction_register % 100;
		
        // Execute the correct instruction.
		switch (operation_code)
		{
        case READ:
            // takes in the input
            int word;
            cin >> word; 
            // checks for illegal input
            if (word < -9999 || word > 9999)
            {
                cout << "*** ABEND: illegal input ***\n";
                return;
            }
            // stores input in memory
            memory[operand] = word;
            
            cout << "READ: " << FOUR_DIGIT_SIGNED_FORMAT << word << endl;
            break;

        case WRITE:
            cout << FOUR_DIGIT_SIGNED_FORMAT << memory[operand] << endl;
            break;

        case LOAD:
            // places the word in the memory location identified by operand into the accumulator
            accumulator = memory[operand];
            break;

        case STORE:
            // places the accumulator into the memory location identified by operand
            memory[operand] = accumulator;
            break;

        case ADD:
            // checks if arithmetic operation causes overflow/underflow
            if ((accumulator + memory[operand]) > 9999) 
            {
                cout << "*** ABEND: overflow ***" << endl;
                return;
            }
            else if ((accumulator + memory[operand]) < -9999)
            {
                cout << "*** ABEND: underflow ***" << endl;
                return;
            }
            else
                // Places the arithmetic operation in the accumulator
                accumulator = accumulator + memory[operand];

            break;

        case SUBTRACT:
            // checks if arithmetic operation causes overflow/underflow
            if ((accumulator - memory[operand]) > 9999) 
            {
                cout << "*** ABEND: overflow ***" << endl;
                return;
            }
            else if ((accumulator - memory[operand]) < -9999)
            {
                cout << "*** ABEND: underflow ***" << endl;
                return;
            }
            else
                // Places the arithmetic operation in the accumulator
                accumulator = accumulator - memory[operand];
            break;

        case MULTIPLY:
            // checks if arithmetic operation causes overflow/underflow
            if ((accumulator * memory[operand]) > 9999)
            {
                cout << "*** ABEND: overflow ***" << endl;
                return;
            }
            else if ((accumulator * memory[operand]) < -9999)
            {
                cout << "*** ABEND: underflow ***" << endl;
                return;
            }
            else
                // Places the arithmetic operation in the accumulator
                accumulator= accumulator * memory[operand];
            break;

        case DIVIDE:
            // checks for division by 0
            if (memory[operand] == 0)
            {
                cout <<"*** ABEND: attempted division by 0 ***" << endl;
                return;
            }
            else
                // Places the arithmetic operation in the accumulator
                accumulator/= memory[operand];
            break;

        case BRANCH:
            // Sets the instruction_counter to the value in operand
            instruction_counter = operand;
            break;
        case BRANCHNEG:
            if (accumulator < 0) 
            // Sets the instruction_counter to the value in operand
                instruction_counter = operand;
            else
                instruction_counter++;
            break;
        case BRANCHZERO:
            if (accumulator == 0)
             // Sets the instruction_counter to the value in operand
                instruction_counter = operand;
            else
                instruction_counter++;
            break;

        case HALT: // Stops the execution of the SML program
            done = true;
            break;

        default:
            cout << "*** ABEND: invalid opcode ***\n";
            return;
        }

		// If not done and current operation code is not one
        // of the BRANCH op codes, increment instruction_counter.
        if (operation_code != BRANCH && operation_code != BRANCHNEG && operation_code != BRANCHZERO && !done)
            instruction_counter++; 
    }
    
    // Print successful termination message.
	cout << "*** Simplesim execution terminated ***\n";
}

/**
 * Prints the contents of the Simplesim's registers and memory.
 */
void simplesim::dump() const
{
    // Print registers.
         cout 
         << "\nREGISTERS:\n"
         << REG_LABEL_FORMAT << "accumulator:" << FOUR_DIGIT_SIGNED_FORMAT << accumulator << endl
         << REG_LABEL_FORMAT << "instruction_counter:" << TWO_DIGIT_UNSIGNED_FORMAT << instruction_counter << endl
         << REG_LABEL_FORMAT << "instruction_register:" << FOUR_DIGIT_SIGNED_FORMAT << instruction_register << endl
         << REG_LABEL_FORMAT << "operation_code:" << TWO_DIGIT_UNSIGNED_FORMAT << operation_code << endl
         << REG_LABEL_FORMAT << "operand:" << TWO_DIGIT_UNSIGNED_FORMAT << operand << endl;

    // Print memory.
    cout << "\nMEMORY:\n";

    // prints the column headers
    for (int i = 0; i < 10; i++) (i == 0) ? cout << setw(8) << right << setfill(' ') << noshowpos << i : cout << COL_HEADER_FORMAT << i; // Gives sufficient allignment

    int rowHeaderNum = 0;
    // iterates through each word in memory
    for (int i = 0; i < MAX_MEMORY; i++)
    {
        if (i % 10 == 0) // starts a new row and prints the next row header after 10 iterations
        {
            cout << '\n' << ROW_HEADER_FORMAT << rowHeaderNum << ' ';
            rowHeaderNum+= 10; // adds 10 since row headers are in increments of 10
        }
        cout << FOUR_DIGIT_SIGNED_FORMAT << memory[i] << ' '; // prints word in memory
    }
    cout << endl;

}
