//
// Created by Tensae Woldeselassie (tensaew) and Gabriel Oliver (gaog1999) on
// 3/3/2020.
//

#include "fund.h"

// Parameters: ostream& out, Fund fund.
// Post: Prints the history of transactions for fund to ostream& out.
ostream& operator<<(ostream& out, const Fund& fund) {
    out << fund.fundName << ": $" << fund.balance << "\n";
    for (const auto& transaction : *fund.getTransactions()) {
        out << "        " << transaction << "\n";
    }
    return out;
}

// Parameters: int fundNumber, string fundName.
// Post: Constructs instance of Fund class.
Fund::Fund(int fundNumber, string fundName) {
    this->fundNumber = fundNumber;
    this->fundName = std::move(fundName);
    this->balance = 0;
    this->transactions = new vector<string>();
}

void displayFlags(uint value) {
    cout << "Value is:\n";
    if (value == IS_ROOT) {
        cout << "  Root\n";
    } else {
        cout << "  Not Root\n";
    }

    if (value == IS_PARENT) {
        cout << "  PARENT\n";
    } else {
        cout << "  Not PARENT\n";
    }

    if (value == IS_BST) {
        cout << "  BST\n";
    } else {
        cout << "  Not BST\n";
    }

    if (value == IS_BALANCED) {
        cout << "  BALANCED\n";
    } else {
        cout << "  Not BALANCED\n";
    }
}

// Post: Fund Destructor.
Fund::~Fund() { delete transactions; }

// Parameters: int amount, const string& transactionLine.
// Post: Adds or Subtracts amount from this Fund's balance, depending if
// amount is positive or negative.
void Fund::addOrSubtract(int amount, const string& transactionLine) {
    this->balance += amount;
    this->addToTransactions(transactionLine);
}

// Parameter: const string& transactionLine.
// Post: Marks the transaction as failed, due to insufficient amount of
// money in this Fund or combined this Fund and friendly Fund.
void Fund::failedToSubtract(const string& transactionLine) {
    this->addToTransactions(transactionLine + " (Failed)");
}

// Post: Return int amount of money in this Fund.
int Fund::getBalance() const { return this->balance; }

// Post: Return string name of this Fund.
string Fund::getName() const { return this->fundName; }

// Parameter: const string& transactionLine.
// Post: Adds the transaction to the list<string>* transactions.
void Fund::addToTransactions(const string& transactionLine) const {
    this->getTransactions()->push_back(transactionLine);
}

// Post: Returns list<string>* transactions.
vector<string>* Fund::getTransactions() const { return this->transactions; }