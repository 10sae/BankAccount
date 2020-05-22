//
// Created by Tensae Woldeselassie (tensaew) and Gabriel Oliver (gaog1999) on
// 3/3/2020.
//

#include "account.h"
#include <fstream>
#include <string>

// Used when displaying final balance in phase 3.
// Prints the name and id of the account followed by
// the name and balance of each fund.
ostream& operator<<(ostream& out, const Account& acc) {
    out << acc.owner << " Account ID: " << acc.getId() << endl;
    for (int i = 0; i < acc.fundsArraySize; i++) {
       out << "        " << acc.funds[i]->getName() <<": $"
       << acc.funds[i]->getBalance()
       << "\n";
    }
    out << endl;
    return out;
}

// Parameters: string name, int accountNumber.
// Post: Constructs instance of Account class.
Account::Account(string name, int accountNumber) {
    this->accountNumber = accountNumber;
    this->owner = std::move(name);
    funds = new Fund*[fundsArraySize];
    funds[0] = new Fund(0, "Money Market");
    funds[1] = new Fund(1, "Prime Money Market");
    funds[2] = new Fund(2, "Long-Term Bond");
    funds[3] = new Fund(3, "Short-Term Bond");
    funds[4] = new Fund(4, "500 Index Fund");
    funds[5] = new Fund(5, "Capital Value Fund");
    funds[6] = new Fund(6, "Growth Equity Fund");
    funds[7] = new Fund(7, "Growth Index Fund");
    funds[8] = new Fund(8, "Value Fund");
    funds[9] = new Fund(9, "Value Stock Index");
}

// Post: Account destructor.
Account::~Account() {
    for (int i = 0; i < fundsArraySize; i++) {
        delete funds[i];
    }
    delete[] funds;
}

// Parameters: int fundIndex, int amount, const string& transactionLine.
// Post: Add amount of money to the Fund defined by the fundIndex.
// TransactionLine records this transaction in the specified Fund.
bool Account::deposit(int fundIndex, int amount,
                      const string& transactionLine) const {
    this->funds[fundIndex]->addOrSubtract(amount, transactionLine);
    return true;
}

// Parameters: int fundIndex, int amount, const string& transactionLine.
// Post: Subtracts amount of money from the Fund defined by the fundIndex.
// TransactionLine records this transaction in the specified Fund.
bool Account::withdraw(int fundIndex, int amount,
                       const string& transactionLine) const {
    // if balance in fund is less than withdrawal amount
    if (this->getFundBalance(fundIndex) < amount) {
        // if it's a sharing fund
        if (fundIndex < 4) {
            int fundBalance = this->getFundBalance(fundIndex);
            int friendlyFundBalance = 0;
            int friendFundIndex;

            // Get the friendFun balance
            if (fundIndex % 2 == 0) {
                friendFundIndex = fundIndex + 1;
                friendlyFundBalance = this->getFundBalance(friendFundIndex);
            } else {
                friendFundIndex = fundIndex - 1;
                friendlyFundBalance = this->getFundBalance(friendFundIndex);
            }

            // If there's enough money in fund + friend
            if (fundBalance + friendlyFundBalance >= amount) {
                int remainderOfAmount = amount - fundBalance;

                // make transfter string
                string tString = "T " + to_string(accountNumber) +
                                 to_string(friendFundIndex) + " " +
                                 to_string(remainderOfAmount) + " " +
                                 to_string(accountNumber) +
                                 to_string(fundIndex);
                cout << tString;
                this->funds[friendFundIndex]->addOrSubtract
                        (-remainderOfAmount, tString);

                // make deposit string
                string dString = "D " + to_string(accountNumber) +
                                 to_string(fundIndex) + " " +
                                 to_string(remainderOfAmount);
                this->funds[fundIndex]->addOrSubtract(remainderOfAmount,
                                                      dString);
                cout << dString;

                // withdraw string = transactionLine
                this->funds[fundIndex]->addOrSubtract(-amount,
                                                      transactionLine);


                
                return true;
            }
        }
        this->funds[fundIndex]->failedToSubtract(transactionLine);
        return false;
    }
    this->funds[fundIndex]->addOrSubtract(-amount,
                                          transactionLine);
    return true;
}

// Parameter: int fundIndex.
// Post: Prints the history if the specified Fund by the fundIndex.
void Account::history(int fundIndex) const {
    ofstream outputFile;
    outputFile.open("BankTransOut.txt", ofstream::app);
    outputFile << "Displaying Transaction History for " << this->owner << "'s ";
    outputFile << *(funds[fundIndex]);
    outputFile.close();
}

// Post: Prints the history of all of the funds in this Account.
void Account::history() const {
    ofstream outputFile;
    outputFile.open("BankTransOut.txt", ofstream::app);
    outputFile << "Displaying Transaction History for " << this->owner
    << " by fund.\n";
    for (int i = 0; i < fundsArraySize; i++) {
       outputFile << *(funds[i]);
    }
    outputFile.close();

}

// Returns accountNumber.
int Account::getId() const { return accountNumber; }

// Parameter: int fundIndex.
// Returns amount of money in Fund specified by the fundIndex.
int Account::getFundBalance(int fundIndex) const {
    return this->funds[fundIndex]->getBalance();
}