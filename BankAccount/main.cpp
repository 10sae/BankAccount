//
// Created by Tensae Woldeselassie (tensaew) and Gabriel Oliver (gaog1999) on
// 3/3/2020.
//

#include "bank.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    Bank bank;

    // Note that tests were done in BankTransIn.txt
    for (int i = 1; i < argc; i++) {
        cout << "The command line argument(s) was " << argv[i] << endl;
        string fileName = argv[i];
        bank.processTransactions(fileName);
    }
    bank.displayAllBankBalances();
    cout << "Done" << endl;

    return 0;
}