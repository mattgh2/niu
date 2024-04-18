//*******************************************************************
//
//  scc.cpp
//  CSCI 241 Assignment 15
//  Created by your-name (your-zid)
//
//********************************************************************

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "sml.h"
#include "scc.h"
#include "inpost.h"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::internal;
using std::istringstream;
using std::noshowpos;
using std::setfill;
using std::setw;
using std::showpos;
using std::string;

/**
 * Constructor - initializes memory and flags arrays.
 */
scc::scc()
{
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        memory[i] = DEFAULT;
        flags[i] = -1;
    }
}

/**
 * Performs first pass of compilation.
 */
void scc::first_pass()
{
    string buffer, command;
    int line_number;

    while (getline(cin, buffer))
    {
        istringstream iss(buffer);

        // Read the line number.
        iss >> line_number;

        // Add line number to the symbol table.
        symbol_table[next_symbol_table_idx].symbol = line_number;
        symbol_table[next_symbol_table_idx].type = 'L';
        symbol_table[next_symbol_table_idx].location = next_instruction_addr;
        next_symbol_table_idx++;

        // Read the command.
        iss >> command;

        if (command == "input")
        {
            // Code to process "input" command.
            handle_input(iss);
        }
        else if (command == "data")
        {
            // Code to process "data" command.
            handle_data(iss);
        }
        else if (command == "let")
        {
            // Code to process "let" command.
            handle_let(iss, buffer);
        }
        else if (command == "goto")
        {
            // Code to process "goto" command.
            handle_goto(iss);
        }
        else if (command == "if")
        {
            // Code to process "if" command.
            handle_if(iss);
        }
        else if (command == "print")
        {
            // Code to process "print" command.
            handle_print(iss);
        }
        else if (command == "rem")
        {
            // Code to process "rem" command.
        }
        else
        {
            // Code to process "end" command.
            handle_end();
        }
    }
}

/**
 * Performs second pass of compilation.
 */
void scc::second_pass()
{
    int index;

    // Compute address of first element of the stack.
    int stack_start = next_const_or_var_addr - 1;

    // Loop through flags and memory array.
    for (int i = 0; i < next_instruction_addr; i++)
    {
        // If an instruction is marked incomplete in the flags
        // array, complete it.
        if (flags[i] != -1)
        {
            if (flags[i] > 0)
            {
                // Line number for goto instruction.
                int line_number = flags[i];
                int location;

                // Scan the table for the line number
                // If we find a match, get the address and complete the instruction
                location = search_symbol_table(line_number, 'L');

                // If we found a match, complete the address
                if (location != -1) {
                    int address = symbol_table[location].location;
                    memory[i] += address;
                }

            }
            else if (flags[i] == -2)
            {
                // Right operand location for DIVIDE and SUBTRACT.
                memory_check();
                memory[i]+= next_const_or_var_addr;
            }
            else if (flags[i] < -2)
            {
                // Calculate the stack index
                index = -3 - flags[i];

                // Get the corresponding memory location
                int stack_location = stack_start - index;

                // Check stack_space and complete the instruction
                stack_space_check(stack_location);
                memory[i]+= stack_location;
            }
        }
    }
}

/**
 * Prints memory and data for the compiled SML program.
 */
void scc::print_program() const
{
    cout << showpos << internal << setfill('0');

    // Print memory.
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        cout << setw(5) << memory[i] << endl;
    }

    cout << noshowpos << "-99999\n";

    // Print data.

    for (int i = 0; i < ndata; i++)
    {
        cout << data[i] << endl;
    }
}

/**
 * Generates code for an "input" instruction.
 *
 * @param iss Input stringstream used to read the remainder of
 *            the instruction.
 */
void scc::handle_input(istringstream& iss)
{
    string symbol;

    iss >> symbol;
    int location = get_symbol_location(symbol);
    memory_check();
    memory[next_instruction_addr] = READ * 100 + location;
    next_instruction_addr++;
}

/**
 * Generates code for a "data" instruction.
 *
 * @param iss Input stringstream used to read the remainder of
 *            the instruction.
 */
void scc::handle_data(std::istringstream& iss)
{
    int number;

    iss >> number;
    data_check();
    data[ndata] = number;
    ndata++;
}

/**
 * Generates code for a "let" instruction.
 *
 * @param iss Input stringstream used to read the remainder of
 *            the instruction.
 * @param buffer Input buffer from which to extract an infix
 *               expression so it can be converted to postfix.
 */
void scc::handle_let(istringstream& iss, const string& buffer)
{
    // Search for "=" in buffer that contains infix string.
    size_t index = buffer.find_first_of("=");

    // Extract the infix string that follows the '=' operator.
    string infix = buffer.substr(index + 2, string::npos);

    // Get the symbol
    string symbol;
    iss >> symbol;

    // Search the symbol table for the variable being assigned 
    int symbol_location = get_symbol_location(symbol);
    // Convert infix to postfix
    string postfix = convert(infix);
    // initialize a stack index integer to 0
    int next_stack_idx = 0;

    std::stringstream ss(postfix);
    string op;

    // proccess the postfix expression
    while (ss >> op) {

        // Processing operands
        if (isdigit(op[0]) || isalpha(op[0])) {

            // get the address of the operand;
            int op_address = get_symbol_location(op);

            // Write a LOAD instruction using the operands address
            memory_check();
            memory[next_instruction_addr] = LOAD * 100 + op_address;
            next_instruction_addr++;

            // Write a partial STORE instruction
            memory_check();
            memory[next_instruction_addr] = STORE * 100;

            // Use the flags array to flag this STORE instruction
            flags[next_instruction_addr] = -3 - next_stack_idx;
            next_instruction_addr++;
            next_stack_idx++;

        }
        // Processing Operators
        else {
            if (op == "+") {
                memory_check();
                memory[next_instruction_addr]  = LOAD * 100; // omitting address
                next_stack_idx--; 
                flags[next_instruction_addr] = -3 - next_stack_idx;
                next_instruction_addr++;

                memory_check(); 
                memory[next_instruction_addr] = ADD * 100;
                next_stack_idx--;
                flags[next_instruction_addr] = -3 - next_stack_idx;
                next_instruction_addr++;
    
                memory_check();
                memory[next_instruction_addr] = STORE * 100;
                flags[next_instruction_addr] = -3 - next_stack_idx;
                next_stack_idx++;
                next_instruction_addr++;
            }

            else if (op == "*") {
                memory_check();
                memory[next_instruction_addr]  = LOAD * 100; // omitting address
                next_stack_idx--; 
                flags[next_instruction_addr] = -3 - next_stack_idx;
                next_instruction_addr++;

                memory_check(); 
                memory[next_instruction_addr] = MULTIPLY * 100;
                next_stack_idx--;
                flags[next_instruction_addr] = -3 - next_stack_idx;
                next_instruction_addr++;
    
                memory_check();
                memory[next_instruction_addr] = STORE * 100;
                flags[next_instruction_addr] = -3 - next_stack_idx;
                next_stack_idx++;
                next_instruction_addr++;
            }
            else if (op == "-") {

                memory_check();
                memory[next_instruction_addr] = LOAD * 100; // omit address
                next_stack_idx--;
                flags[next_instruction_addr] = -3 - next_stack_idx;
                next_instruction_addr++;

                memory_check();
                memory[next_instruction_addr] = STORE * 100; // omit address
                flags[next_instruction_addr] = -2;
                next_instruction_addr++;

                memory_check();
                memory[next_instruction_addr] = LOAD * 100; // omit address
                next_stack_idx--;
                flags[next_instruction_addr] = -3 - next_stack_idx;
                next_instruction_addr++;

                memory_check();
                memory[next_instruction_addr] = SUBTRACT * 100;
                flags[next_instruction_addr] = -2;
                next_instruction_addr++;

                memory_check();
                memory[next_instruction_addr] = STORE * 100;
                flags[next_instruction_addr] = -3 - next_stack_idx;
                next_stack_idx++;
                next_instruction_addr++;
            }

            else if (op == "/") {

                memory_check();
                memory[next_instruction_addr] = LOAD * 100; // omit address
                next_stack_idx--;
                flags[next_instruction_addr] = -3 - next_stack_idx;
                next_instruction_addr++;

                memory_check();
                memory[next_instruction_addr] = STORE * 100; // omit address
                flags[next_instruction_addr] = -2;
                next_instruction_addr++;

                memory_check();
                memory[next_instruction_addr] = LOAD * 100; // omit address
                next_stack_idx--;
                flags[next_instruction_addr] = -3 - next_stack_idx;
                next_instruction_addr++;

                memory_check();
                memory[next_instruction_addr] = DIVIDE * 100;
                flags[next_instruction_addr] = -2;
                next_instruction_addr++;

                memory_check();
                memory[next_instruction_addr] = STORE * 100;
                flags[next_instruction_addr] = -3 - next_stack_idx;
                next_stack_idx++;
                next_instruction_addr++;
            }
        }
    }

    // Get the results: remove and place into the
    // memory location of the variable of the let command
    memory_check();
    memory[next_instruction_addr] = LOAD * 100; // Partial load
        
    /* 
        set the element of the flags array that corresponds 
        to the partial LOAD instruction back to -3
    */
    flags[next_instruction_addr] = -3;
    
    next_instruction_addr++;

    // Place the result into the mem location of the var of the let command.
    memory_check();
    memory[next_instruction_addr] = STORE * 100 + symbol_location;
    next_instruction_addr++;
}

/**
 * Generates code for a "goto" instruction.
 *
 * @param iss Input stringstream used to read the remainder of
 *            the instruction.
 */
void scc::handle_goto(istringstream& iss)
{
    int line_number;
    int mem_location;  
    int index;

    iss >> line_number;

    // Search the symbol table for the line number

        // If we get a match, extract the line number's memory location, 
        // then place a BRANCH instruction at the next instructor address in memory
        index = search_symbol_table(line_number, 'L');

        if (index != -1) {
            mem_location = symbol_table[index].location;
            memory_check();
            memory[next_instruction_addr] = BRANCH * 100 + mem_location;
            next_instruction_addr++;
        } else {
            // line number not found in table, place a partial BRANCH instruction
            memory_check();
            memory[next_instruction_addr] = BRANCH * 100;

            // flag the instruction and increment to the next instruction address
            flags[next_instruction_addr] = line_number;
            next_instruction_addr++;
        }
}
/**
 * Generates a BRANCHNEG instruction for the line number
 *
 * @param index of line_number in symbol_table, the line_number and its address.
 *
 * @note location with value -1 means it is not yet in the symbol_table,
 * so we need to generate a partial instruction
 */
void scc::branchneg_to_linenum(const int &index, const int &line_number, const int &location) {

    // If line number was not found, generate a partial instruction
    if (index == -1) {
        memory_check();
        memory[next_instruction_addr] = BRANCHNEG * 100;
        flags[next_instruction_addr] = line_number;
        next_instruction_addr++;

        // Line number was found, generate a full instruction
        } else {
            memory_check();
            memory[next_instruction_addr] = BRANCHNEG * 100 + location;
            next_instruction_addr++;
        }
}
/**
 * Generates a BRANCHZERO instruction for a line number
 *
 * @param index of line number in symbol table, the line_number and its location
 *
 * @note location with value -1 means it is not yet in the symbol_table,
 * so we need to generate a partial instruction
 */
void scc::branchzero_to_linenum(const int &index, const int &line_number, const int &location) {

    if (index == -1) {

        memory[next_instruction_addr] = BRANCHZERO * 100;
        flags[next_instruction_addr] = line_number;
        next_instruction_addr++;

    // Line number was found, generate a full instruction
    } else {
        memory_check();
        memory[next_instruction_addr] = BRANCHZERO * 100 + location;
        next_instruction_addr++;
    }
}
/**
 * Generates code for an "if" instruction.
 *
 * @param iss Input stringstream used to read the remainder of
 *            the instruction.
 */
void scc::handle_if(istringstream& iss)
{
    string left_operand, op, right_operand, goto_statement, line_number;
    int left_operand_location;
    int right_operand_location;
    int line_number_location;

    int index;

    // grab the line
    iss >> left_operand >> op >> right_operand >> goto_statement >> line_number;

    /* 
        Gets the locations of the operands and line number.
    */
    left_operand_location = get_symbol_location(left_operand);
    right_operand_location = get_symbol_location(right_operand);
    index = search_symbol_table(stoi(line_number), 'L');
    if (index != -1)
        line_number_location = symbol_table[index].location;

    // Less than case
    if (op == ">") {

        // LOAD from <rop> location
        memory_check();
        memory[next_instruction_addr] = LOAD * 100 + right_operand_location;
        next_instruction_addr++;

        // SUBTRACT from <lop> location
        memory_check();
        memory[next_instruction_addr] = SUBTRACT * 100 + left_operand_location;
        next_instruction_addr++;

        // BRANCHNEG to <linenum> location
        branchneg_to_linenum(index, stoi(line_number), line_number_location);
    } 
    else if (op == "<") {

        // LOAD from <lop> location 
        memory_check();
        memory[next_instruction_addr] = LOAD * 100 + left_operand_location;
        next_instruction_addr++;

        // SUBTRACT from <rop> location
        memory_check();
        memory[next_instruction_addr] = SUBTRACT * 100 + right_operand_location;
        next_instruction_addr++;

        // BRANCHNEG to <linenum> location
        branchneg_to_linenum(index, stoi(line_number), line_number_location);
    }
    else if (op == "==") {

        // LOAD from <lop> location
        memory_check();
        memory[next_instruction_addr] = LOAD * 100 + left_operand_location;
        next_instruction_addr++;

        // SUBTRACT from <rop> location
        memory_check();
        memory[next_instruction_addr] = SUBTRACT * 100 + right_operand_location;
        next_instruction_addr++;
     
        // BRANCHZERO to <linenum> location
        branchzero_to_linenum(index, stoi(line_number), line_number_location);
    }
    else if (op == ">=") {

        // LOAD from <rop> location
        memory_check();
        memory[next_instruction_addr] = LOAD * 100 + right_operand_location;
        next_instruction_addr++;

        // SUBTRACT from <lop> location
        memory_check();
        memory[next_instruction_addr] = SUBTRACT * 100 + left_operand_location;
        next_instruction_addr++;
        
        branchneg_to_linenum(index, stoi(line_number), line_number_location);
        branchzero_to_linenum(index, stoi(line_number), line_number_location);
    }
    else if (op == "<=") {

        // LOAD from <lop> location
        memory_check();
        memory[next_instruction_addr] = LOAD * 100 + left_operand_location;
        next_instruction_addr++;

        // SUBTRACT from <rop> location
        memory_check();
        memory[next_instruction_addr] = SUBTRACT * 100 + right_operand_location;
        next_instruction_addr++;

        branchneg_to_linenum(index, stoi(line_number), line_number_location);
        branchzero_to_linenum(index, stoi(line_number), line_number_location);
    }
    else if (op == "!=") {

        // LOAD from <lop> location
        memory[next_instruction_addr] = LOAD * 100 + left_operand_location;
        next_instruction_addr++;

        // SUBTRACT from <rop> location
        memory[next_instruction_addr] = SUBTRACT * 100 + right_operand_location;
        next_instruction_addr++;
        
        memory_check();
        memory[next_instruction_addr] = BRANCHZERO * 100 + (next_instruction_addr + 2);
        next_instruction_addr++;

        if (index == -1) {
            memory_check();
            memory[next_instruction_addr] = BRANCH * 100;
            flags[next_instruction_addr] = stoi(line_number);
            next_instruction_addr++;
        } else {
            memory_check();
            memory[next_instruction_addr] = BRANCH * 100 + line_number_location;
            next_instruction_addr++;
        }
    }
}

/**
 * Generates code for a "print" instruction.
 *
 * @param iss Input stringstream used to read the remainder of
 *            the instruction.
 */
void scc::handle_print(istringstream& iss)
{
    string symbol;

    iss >> symbol;
    int location = get_symbol_location(symbol);
    memory_check();
    memory[next_instruction_addr] = WRITE * 100 + location;
    next_instruction_addr++;
}

/**
 * Generates code for an "end" instruction.
 */
void scc::handle_end()
{
    memory_check();
    memory[next_instruction_addr] = HALT * 100;
    next_instruction_addr++;
}

/**
 * Checks to make sure there is room in the memory array
 * to add another instruction.
 */
void scc::memory_check() const
{
    // If the number of instructions plus constants and variables
    // exceeds the number of elements in the memory array, print an 
    // error message and exit.
    if (next_instruction_addr >= MEMORY_SIZE ||
        next_instruction_addr > next_const_or_var_addr)
    {
        cout << "*** ERROR: ran out of Simplesim memory ***\n";
        exit(1);
    }
}

/**
 * Checks to make sure there is room in the data array
 * to add another data value.
 */
void scc::data_check() const
{
    // If the number of data items exceeds the number of 
    // elements in the data array, print an error message and
    // exit.
    if (ndata >= MEMORY_SIZE)
    {
        cout << "*** ERROR: too many data lines ***\n";
        exit(1);
    }
}

/**
 * Checks whether the top of the stack has crossed into the region
 * of the memory array that contains instructions.
 *
 * @param location Location of the top of the stack.
 */
void scc::stack_space_check(int location) const
{
    // If the top of the stack has hit the instructions in
    // the memory array, print an error message and exit.
    if (location < next_instruction_addr)
    {
        cout << "*** ERROR: insufficient stack space ***\n";
        exit(1);
    }
}

/**
 * Gets the location of a constant or variable, adding it to the 
 * symbol table and memory if necessary.
 *
 * @param token The symbol to locate.
 *
 * @return The symbol's location.
 */
int scc::get_symbol_location(const string& token)
{
    int location, symbol;
    char type;

    if (islower(token[0]))
    {
        // This is a variable.
        symbol = token[0];
        type = 'V';
    }
    else
    {
        // This is an integer constant.
        symbol = stoi(token);
        type = 'C';
    }

    int index = search_symbol_table(symbol, type);

    if (index == -1)
    {
        // This symbol is not in the symbol table. Add it to
        // the symbol table.
        location = next_const_or_var_addr;

        symbol_table[next_symbol_table_idx].symbol = symbol;
        symbol_table[next_symbol_table_idx].type = type;
        symbol_table[next_symbol_table_idx].location = location;
        next_symbol_table_idx++;

        memory_check();
        if (type == 'V')
            memory[location] = 0;
        else
            memory[location] = symbol;

        next_const_or_var_addr--;
    }
    else
    {
        // This symbol is in the symbol table at array element
        // index.
        location = symbol_table[index].location;
    }

    return location;
}

/**
 * Searches the symbol table for a symbol with the specified type.
 * 
 * @param symbol The symbol to search for.
 * @param type The type of the symbol to search for.
 *
 * @return The index of the symbol table entry where the symbol'
 *         was found or -1 if the search fails.
 *
 * @note Uses the linear search algorithm.
 */
int scc::search_symbol_table(int symbol, char type) const
{
    for (int i = 0; i < next_symbol_table_idx; i++)
    {
        if (symbol == symbol_table[i].symbol && type == 
            symbol_table[i].type)
        {
            return i;
        }
    }

    return -1;
}
