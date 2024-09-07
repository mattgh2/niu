//***************************************************************************
//
//  bank.h
//  CSCI 241 Assignment 9
//
//  Created by Matt Warner (z2004200)
//
//***************************************************************************
#ifndef BANK_H
#define BANK_H

#include "account.h"
#include <string>

class bank {

private:
  
  // Data members
  std::string bankName; 
  account accounts[20];
  int validAccounts;

public:
  
  // Default constructor
  bank();

  // Member functions
  void read_accounts(const std::string& accountFile);
  void process_transactions(const std::string& transactionFile);
  void print();
  
};

#endif
