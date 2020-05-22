//
// Created by Tensae Woldeslassie (tensaew) and Gabriel Oliver (gaog1999) on
// 3/3/2020.
//

#pragma once

#include "accounttree.h"
#include <queue>
#include <string>
#include <vector>

using namespace std;

class Bank {
  public:
    // Post: Creates instance of Bank class.
    Bank();

    // Post: Bank destructor.
    ~Bank();

    // Parameter: const string& fileName.
    // Post: Process the transactions from the file specified by fileName.
    void processTransactions(const string& fileName) const;

    // Post: Prints all the accounts and their funds to the out-file.
    void displayAllBankBalances() const;

    // Post: Returns AccountTree accounts with access to its binary search
    // tree.
    AccountTree* getAccounts() const;
    
    // Post: Returns queue<string> transactions with the order of transactions
    // they appeared in the in-file.
    queue<string>* getTransactions() const;

  private:
    // Instance of AccountTree, has a binary search tree to store Accounts
    // used to process the transactions.
    AccountTree* accounts;
    
    // Stores transactions from the in-file to be processed by this Bank
    // instance.
    queue<string>* transactions;

    // Parameters: vector<string> parsedStringVector
    // Post: Processes the transaction information passed by parsedStringVector
    // and opens an account.
    void open(vector<string> parsedStringVector) const;
    
    // Parameters: const string& transactionLine,
    // vector<string> parsedStringVector.
    // Post: Processes the transaction information passed by parsedStringVector
    // and deposits the amount specified.
    void deposit(const string& transactionLine,
                 vector<string> parsedStringVector) const;

    // Parameters: const string& transactionLine,
    // vector<string> parsedStringVector.
    // Post: Processes the transaction information passed by parsedStringVector
    // and withdraws the amount specified.
    void withdraw(const string& transactionLine,
                  vector<string> parsedStringVector) const;

    // Parameters: const string& transactionLine,
    // vector<string> parsedStringVector.
    // Post: Processes the transaction information passed by
    // parsedStringVector.
    // Withdraws the amount specified from the first fund and deposits it in
    // the second fund specified.
    void transfer(const string& transactionLine,
                  vector<string> parsedStringVector) const;

    // Parameter: vector<string> parsedStringVector.
    // Post: Processes the transaction information passed by parsedStringVector
    // and prints the history of account or a specified fund.
    void history(vector<string> parsedStringVector) const;

    // Parameters: bool transactionTypeIsOpen, const string& accountNumber.
    // Post: Prints to out-file if there was an error in a transaction passed
    // by the the in-file.
    void printError(bool transactionTypeIsOpen, const string& accountNumber)
    const;
};