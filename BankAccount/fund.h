//
// Created by Tensae Woldeselassie (tensaew) and Gabriel Oliver (gaog1999) on
// 3/3/2020.
//

#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Fund {
    // Parameters: ostream& out, Fund fund.
    // Post: prints the history of transactions for fund to ostream& out.
    friend ostream& operator<<(ostream& out, const Fund& fund);

public:
    // Parameters: int fundNumber, string fundName.
    // Post: Constructs instance of Fund class.
    Fund(int fundNumber, string fundName);

    // Post: Fund Destructor.
    ~Fund();

    // Parameters: int amount, const string& transactionLine.
    // Post: Adds or Subtracts amount from this Fund's balance, depending if
    // amount is positive or negative.
    void addOrSubtract(int amount, const string& transactionLine);

    // Parameter: const string& transactionLine.
    // Post: Marks the transaction as failed, due to insufficient amount of
    // money in this Fund or combined this Fund and friendly Fund.
    void failedToSubtract(const string& transactionLine);

    // Post: Return int amount of money in this Fund.
    int getBalance() const;

    // Post: Return string name of this Fund.
    string getName() const;

    // Parameter: const string& transactionLine.
    // Post: Adds the transaction to the list<string>* transactions.
    void addToTransactions(const string& transactionLine) const;

    // Post: Returns list<string>* transactions.
    vector<string>* getTransactions() const;
private:
    // Stores amount of money in this Fund.
    int balance;

    // Stores what number the Fund is in the Account's funds array.
    int fundNumber;

    // Stores the name of this Fund.
    string fundName;

    // Stores the history of transactions with this Fund.
    vector<string>* transactions;
};