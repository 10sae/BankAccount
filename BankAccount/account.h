//
// Created by Tensae Woldeselassie (tensaew) and Gabriel Oliver (gaog1999) on
// 3/3/2020.
//

#pragma once

#include "fund.h"
#include <iostream>
#include <string>

using namespace std;

class Account {
    // Parameters: ostream& out, Account acc.
    // Post: Used when displaying final balance in phase 3.
    // Prints the name and id of the account followed by
    // the name and balance of each fund. 
    friend ostream& operator<<(ostream& out, const Account& acc);

  public:
    // Parameters: string name, int accountNumber.
    // Post: Constructs instance of Account class.
    Account(string name, int accountNumber);

    // Post: Account destructor.
    ~Account();
    
    // Parameters: int fundIndex, int amount, const string& transactionLine.
    // Post: Add amount of money to the Fund defined by the fundIndex.
    // TransactionLine records this transaction in the specified Fund.
    bool deposit(int fundIndex, int amount, const string& transactionLine)
    const;
    
    // Parameters: int fundIndex, int amount, const string& transactionLine.
    // Post: Subtracts amount of money from the Fund defined by the fundIndex.
    // TransactionLine records this transaction in the specified Fund.
    bool withdraw(int fundIndex, int amount, const string& transactionLine)
    const;
    
    // Parameter: int fundIndex.
    // Post: Prints the history if the specified Fund by the fundIndex.
    void history(int fundIndex) const;
    
    // Post: Prints the history of all of the funds in this Account.
    void history() const;
   
    // Returns accountNumber.
    int getId() const;

    // Parameter: int fundIndex.
    // Returns amount of money in Fund specified by the fundIndex.
    int getFundBalance(int fundIndex) const;

private:
    // Pointer to an array of Fund pointers (all funds of the account).
    Fund** funds; 

    // Size of the Fund** funds array.
    const int fundsArraySize = 10;

    // Stores the account's identification number.
    int accountNumber;

    // Stores the owner's name of this Account.
    string owner;
};
