//
// Created by Tensae Woldeselassie (tensaew) and Gabriel Oliver (gaog1999) on
// 3/3/2020.
//

#include "bank.h"
#include "account.h"
#include <fstream>

// Post: Creates instance of Bank class.
Bank::Bank() {
    this->accounts = new AccountTree;
    this->transactions = new queue<string>;
}

// Post: Bank destructor.
Bank::~Bank() {
    delete getAccounts();
    delete getTransactions();
}

// Parameter: const string& fileName.
// Post: Process the transactions from the file specified by fileName.
void Bank::processTransactions(const string& fileName) const {
    ifstream file(fileName);
    string transactionLine;
    while (getline(file, transactionLine)) {
        getTransactions()->push(transactionLine);
    }
    while (!getTransactions()->empty()) {
        transactionLine = getTransactions()->front();
        vector<string> parsedStringVector;

        auto transactionLineLength = static_cast<int>(transactionLine.length());
        for (int i = 0; i < transactionLineLength; i++) {
            string elementOfTransaction;
            while (transactionLine[i] != ' ' && i < transactionLineLength) {
                elementOfTransaction.push_back(transactionLine[i]);
                i++;
            }
            parsedStringVector.push_back(elementOfTransaction);
        }
        string transactionType = parsedStringVector[0];
        if (transactionType == "O") {
            open(parsedStringVector);
        } else if (transactionType == "H") {
            history(parsedStringVector);
        } else if (transactionType == "D") {
            deposit(transactionLine, parsedStringVector);
        } else if (transactionType == "W") {
            withdraw(transactionLine, parsedStringVector);
        } else { // transactionType == "T"
            transfer(transactionLine, parsedStringVector);
        }

        getTransactions()->pop();
    }
    file.close();
}

// Post: Prints all the accounts and their funds to the out-file.
void Bank::displayAllBankBalances() const {
    ofstream outputFile;
    outputFile.open("BankTransOut.txt", ofstream::app);
    outputFile << "\nProcessing Done. Final Balances." << endl;
    getAccounts()->display();
    outputFile.close();
}

// Parameters: vector<string> parsedStringVector
// Post: Processes the transaction information passed by parsedStringVector
// and opens an account.
void Bank::open(vector<string> parsedStringVector) const {
    int accountNumber = stoi(parsedStringVector[3]);
    Account* newAccountPtr = new Account(
        parsedStringVector[1] + " " + parsedStringVector[2], accountNumber);
    if (!getAccounts()->insert(newAccountPtr)) {
        delete newAccountPtr;
        printError(true, parsedStringVector[3]);
    }
}

// Parameters: const string& transactionLine,
// vector<string> parsedStringVector.
// Post: Processes the transaction information passed by parsedStringVector
// and deposits the amount specified.
void Bank::deposit(const string& transactionLine,
                   vector<string> parsedStringVector) const {
    int accountNumber = stoi(parsedStringVector[1]) / 10;
    int accountFundNumber = stoi(parsedStringVector[1]) % 10;
    Account* accountToDeposit = nullptr;
    if (getAccounts()->retrieve(accountNumber, accountToDeposit)) {
        int amountToDeposit = stoi(parsedStringVector[2]);
        accountToDeposit->deposit(accountFundNumber, amountToDeposit,
                                  transactionLine);
    } else {
        printError(false, parsedStringVector[1]);
    }
}

// Parameters: const string& transactionLine,
// vector<string> parsedStringVector.
// Post: Processes the transaction information passed by parsedStringVector
// and withdraws the amount specified.
void Bank::withdraw(const string& transactionLine,
                    vector<string> parsedStringVector) const {
    int accountNumber = stoi(parsedStringVector[1]) / 10;
    int accountFundNumber = stoi(parsedStringVector[1]) % 10;
    Account* accountToWithdraw = nullptr;
    if (getAccounts()->retrieve(accountNumber, accountToWithdraw)) {
        int amountToWithdraw = stoi(parsedStringVector[2]);
        accountToWithdraw->withdraw(accountFundNumber, amountToWithdraw,
                                    transactionLine);
    } else {
        printError(false, parsedStringVector[1]);
    }
}

// Parameters: const string& transactionLine,
// vector<string> parsedStringVector.
// Post: Processes the transaction information passed by
// parsedStringVector.
// Withdraws the amount specified from the first fund and deposits it in
// the second fund specified.
void Bank::transfer(const string& transactionLine,
                    vector<string> parsedStringVector) const {
    Account* recieverAccount = nullptr;
    int recieverAccountNumber = stoi(parsedStringVector[3]) / 10;
    int recieverAccountFundNumber = stoi(parsedStringVector[3]) % 10;

    Account* giverAccount = nullptr;
    int giverAccountNumber = stoi(parsedStringVector[1]) / 10;
    int giverAccountFundNumber = stoi(parsedStringVector[1]) % 10;

    bool bothAreNotNull = true;

    // if giver acc exists
    if (this->getAccounts()->retrieve(giverAccountNumber, giverAccount)) {
        // if giver and receiver acc aren't the same
        if (recieverAccountNumber != giverAccountNumber) {
            // if receiver acc does not exist
            if (!this->getAccounts()->retrieve(recieverAccountNumber, recieverAccount)) {
                bothAreNotNull = false;
                printError(false, to_string(recieverAccountNumber));
            }
        }
        else {
            recieverAccount = giverAccount;
        }
    } else {
        bothAreNotNull = false;
        printError(false, to_string(giverAccountNumber));
    }
    
    if (bothAreNotNull) {
        int amount = stoi(parsedStringVector[2]);
        if (giverAccount->withdraw(giverAccountFundNumber, amount,
                                   transactionLine)) {
            // make deposit string
            string dString = "D " + to_string(recieverAccountNumber) +
                                    to_string(recieverAccountFundNumber) + " " +
                                    to_string(amount);
            recieverAccount->deposit(recieverAccountFundNumber, amount,
                                     dString);
        }
    }
}

// Parameter: vector<string> parsedStringVector.
// Post: Processes the transaction information passed by parsedStringVector
// and prints the history of account or a specified fund.
void Bank::history(
    vector<string> parsedStringVector) const { 
    Account* acc;
    if (parsedStringVector[1].length() == 5) {
        int accNum = stoi(parsedStringVector[1]) / 10;
        int fundNum = stoi(parsedStringVector[1]) % 10;
        if (getAccounts()->retrieve(accNum, acc)) {
            acc->history(fundNum);
        } else {
            parsedStringVector[1].pop_back();
            printError(false, parsedStringVector[1]);
        }
    } else {
        int accNum = stoi(parsedStringVector[1]);
        if (getAccounts()->retrieve(accNum, acc)) {
            acc->history();
        } else {
            printError(false, parsedStringVector[1]);
        }
    }
}

// Parameters: bool transactionTypeIsOpen, const string& accountNumber.
// Post: Prints to out-file if there was an error in a transaction passed
// by the the in-file.
void Bank::printError(bool transactionTypeIsOpen, const string&accountNumber)
const {
    string printOut;
    if (transactionTypeIsOpen) {
        printOut = "ERROR: Account " + accountNumber +
                   " is already open. Transaction refused.\n";
    } else {
        printOut = "ERROR: Could not find Account " + accountNumber +
                   " Transfer cancelled.\n";
    }
    ofstream outputFile;
    outputFile.open("BankTransOut.txt", ofstream::app);
    outputFile << printOut;
    outputFile.close();
}

// Post: Returns AccountTree accounts with access to its binary search
// tree.
AccountTree* Bank::getAccounts() const { return this->accounts; }

// Post: Returns queue<string> transactions with the order of transactions
// they appeared in the in-file.
queue<string>* Bank::getTransactions() const { return this->transactions; }