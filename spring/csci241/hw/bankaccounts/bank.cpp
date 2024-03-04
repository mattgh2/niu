//***************************************************************************
//
//  bank.cpp
//  CSCI 241 Assignment 9
//
//  Created by Matt Warner (z2004200)
//
//***************************************************************************
#include "bank.h"
#include <string>
#include <fstream>
#include <cstdlib>
#include <utility>
#include <iostream>
#include <iomanip>

using std::left;
using std::setw;

/**
 * Default constructor: Assigns default values.
 * 
 */
bank::bank() {
  bankName = "None";
  validAccounts = 0;
}
/**
 * Reads through a text file containing account information,
 * Stores each line of account information into an account object,
 * Then adds it to an array of accounts.
 *
 * @param: accountFile: the text file that contains all account information
 *
 * @note: After the array is filled with valid accounts, 
 * the array gets sorted in ascending order by account number.
 *
 * This function modifies all three class attributes.
 * 
 */
void bank::read_accounts(const std::string& accountFile) {

  std::ifstream infile(accountFile); // input file stream variable

  // checking to make sure the file opened successfully
  if (infile.fail()) {  
    std::cout << accountFile << " Failed to open" << std::endl;
    exit(-1);
  }

  std::getline(infile, bankName);

  // Temp storage for account information 
  std::string accountNumber;
  std::string Name;
  std::string tempBalance;

  std::getline(infile,accountNumber, ':');

  // Loop that reads each line of account information from file.
  // then assigns the information to a new account object, 
  // adding the account object to the array of accounts.
  while (infile) {

    std::getline(infile, Name, ':');
    std::getline(infile, tempBalance);

    double Balance = std::stod(tempBalance);

    account newAccount(accountNumber, Name, Balance);
    accounts[validAccounts] = newAccount;
    validAccounts++;

    std::getline(infile, accountNumber, ':'); // Secondary read
  }
  infile.close();

  // Implementation of the selection sort algorithm
  // that sorts the array of accounts in ascending order by account number
  for (int i = 0; i < validAccounts - 1; i++)
  {
    int minIndex = i;
    for (int j = i + 1; j < validAccounts; j++)
    {
      if (std::stol(accounts[j].get_account_number()) < (std::stol(accounts[minIndex].get_account_number())))
      {
        minIndex = j;
      }
    }
    std::swap(accounts[i], accounts[minIndex]);
  }
}
/**
 * Reads through a text file containing transaction data.
 * Then proccess transaction requests for the accounts
 * After the transactions are proccessed, they are printed out.
 * 
 * @param transactionFile: The file that contains transaction data.
 *
 * @note 
 * Uses binary search to search the array of accounts for the account number given in the transaction.
 * if the account number is found in the array, the transaction is processed.
 *
 * Modifies the currentBalance attribute of a account object if its account number is found in the array.
 * Otherwise, no data members are modified.
 */
void bank::process_transactions(const std::string& transactionFile) {
  std::ifstream infile(transactionFile);

  if (infile.fail()) {
    std::cout << transactionFile << " Failed to open" << std::endl;
    exit(-1);
  }
  std::cout << setw(48) << std::right << "Transaction Report\n\n"
            << std::setw(8) << left << "Date" << setw(22) << left << "Account" << setw(7) << left << "Type" << setw(11) << left << "Amount" << "New Balance\n\n";

  std::string date;
  std::string account;
  char type;
  double amount;

  infile >> date;
  while (infile) {
    infile >> account >> type >> amount;
    
    // index variables for search algorithm
    int start = 0;
    int end = validAccounts - 1;
    int mid = (start + end) / 2;

    bool accountFound = false; // determines whether a transaction should be processed.

    // Implementation of the binary search algorithm
    // that attempts to find the account number from the given transaction.
    while (start <= end) {

      mid = (start + end) / 2;

      if (std::stol(accounts[mid].get_account_number()) == std::stol(account)) {
        accountFound = true;
        break;
      }
      else if (std::stol(accounts[mid].get_account_number()) < std::stol(account)) {
        start = mid + 1;
      }
      else {
        end = mid - 1;
      }
    }
    // If the account was found, this section of code modifies the currentBalance data member of an account 
    // depending on what type of transaction is specified.
    bool hasFunds;
    if (accountFound) {
      switch(type) {
        case 'D':
          accounts[mid].process_deposit(amount);
          break;
        case 'W':
          hasFunds = accounts[mid].process_withdrawl(amount);
        default:
          break;
      }
    }
    // Prints transaction information to the screen
    std::cout << std::setprecision(2) << std::fixed;
    std::cout << setw(8) << left << date << left << setw(22) << account << type << setw(14) << std::right << amount << "   ";

    // determines which output for the New Balance column that should be printed.
    if (accountFound)
      if (type == 'D') {
        std::cout << std::right << setw(8) << accounts[mid].get_balance() << std::endl;
      }
      else if (type == 'W' && hasFunds == true) {
        std::cout << std::right << setw(8) << accounts[mid].get_balance() << std::endl;
      }
      else {
        std::cout << "*** Insufficient funds ***" << std::endl;
      }
    else {
      std::cout << "*** Invalid account number ***" << std::endl;
    }

  infile >> date; // secondary read
  }

  std::cout << std::endl; 
}
/**
 * prints the account listings for the bank.
 *
 * @note
 * Calls the prints function from the account class to display each accounts information
 */
void bank::print() {

  std::cout << "Account Listing for " << bankName << std::endl << std::endl;

  for (int i = 0; i < validAccounts; i++)
  {
    accounts[i].print(); 
    std::cout <<  std::endl;
  }
}

