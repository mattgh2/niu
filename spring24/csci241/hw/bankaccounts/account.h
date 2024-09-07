//***************************************************************************
//
//  account.h
//  CSCI 241 Assignment 9
//
//  Created by Matt Warner (z2004200)
//
//***************************************************************************
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class account {

private:

  // Data members
  std::string accountNum;
  std::string name;
  double currentBalance;

public:

  // Constructors
  account();
  account(std::string accountNum, std::string name, double currentBalance);

  // Accessor methods
  std::string get_account_number() const; 
  double get_balance() const;

  // Mutator methods
  void process_deposit(const double& depositAmount);
  bool process_withdrawl(const double& withdrawlAmount);
    
  
  void print();

};

#endif
