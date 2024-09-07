//***************************************************************************
//
//  account.cpp
//  CSCI 241 Assignment 9
//
//  Created by Matt Warner (z2004200)
//
//***************************************************************************
#include "account.h"
#include <iostream>
#include <iomanip>
/**
 * Default Constructor
 * Assigns all string types to "None" and numeric types to 0.
 *
 */
account::account() {
  accountNum = "None";
  name = "None";
  currentBalance = 0;
}
/**
 * Alternate Constructor for an account object
 *
 * @param accountNum: Accounts identification number
 * @param name: Name of account holder
 * @param currentBalance: The current balance of the account
 *
 */
account::account(std::string accountNum, std::string name, double currentBalance)
{
  this->accountNum = accountNum;
  this->name = name;
  this->currentBalance = currentBalance;
}
/**
 * Accessor Method for the account number data member
 *
 * @return The accounts identification number
 */
std::string account::get_account_number() const
{
  return accountNum;
}
/**
 * Accessor member function for the currentBalance data member
 *
 * @return The accounts current balance
 */
double account::get_balance() const
{
  return currentBalance; 
}
/**
 * Adds a deposit amount to the current balance of the account.
 *
 * @param depositAmount: The amount of money being deposited into the account
 *
 */
void account::process_deposit(const double& depositAmount) {

  this->currentBalance+= depositAmount;
}
/**
 * Withdrawls a specified amount of money from the accounts current balance.
 *
 * @param withdrawlAmount: The amount of money that should be withdrew from the accounts current balance.
 * 
 * @return true if the withdrawl was a success, otherwise the function returns false
 * 
 * @note Needs to perform a check before withdrawl
 * that ensures there is enough money in the account to successfully process the withdrawl.
 */
bool account::process_withdrawl(const double& withdrawlAmount) {

  if (currentBalance >= withdrawlAmount)
  {
    currentBalance-= withdrawlAmount;
    return true;
  }
  else
  {
    return false;
  }
}
/**
 * Prints an account objects data members
 *
 */
void account::print() {
  std::cout << std::setprecision(2) << std::fixed;
  std::cout << "Account Number: " << accountNum
            << "\nName: " << name
            << "\nBalance: $" << currentBalance 
            << std::endl;
}

