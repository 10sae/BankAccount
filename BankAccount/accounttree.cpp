//
// Created by Tensae Woldeselassie (tensaew) and Gabriel Oliver (gaog1999) on
// 3/3/2020.
//

#include "accounttree.h"
#include <fstream>

// Post: Create BST.
// Constructs instance of AccountTree.
AccountTree::AccountTree() { this->root = nullptr; }

// Post: Delete all nodes in BST.
AccountTree::~AccountTree() {
    if (!this->isEmpty()) {
        clear();
    }
}

// Post: Calls to clear the binary search tree.
void AccountTree::clear() { clearHelper(this->root); }

// Parameter: Node* node
// Post: Delete all information in AccountTree.
void AccountTree::clearHelper(Node* node) {
    if (node->getLeft(node) != nullptr) {
        clearHelper(node->getLeft(node));
    }
    if (node->getRight(node) != nullptr) {
        clearHelper(node->getRight(node));
    }
    delete node->getAccount(node);
    delete node;
}

// Parameter: Account* account
// Post: Insert new account.
bool AccountTree::insert(Account* account) {
    if (this->isEmpty()) {
        this->root = new Node(account);
        return true;
    }
    return insertHelper(this->root, account, account->getId());
}

// Parameters: Node* node, Account* account, int accountId
// Post: Recurses through binary search tree to insert an account.
// Returns true if the account is successfully inserted, false if the
// account already exists.
bool AccountTree::insertHelper(Node* node, Account* account, int accountId) {
    int currentAccountId = node->getAccount(node)->getId();
    if (currentAccountId != accountId) {
        if (currentAccountId < accountId) {
            if (node->getRight(node) == nullptr) {
                node->setRight(node, account);
                return true;
            }
            return insertHelper(node->getRight(node), account, accountId);
        }
        if (currentAccountId > accountId) {
            if (node->getLeft(node) == nullptr) {
                node->setLeft(node, account);
                return true;
            }
            return insertHelper(node->getLeft(node), account, accountId);
        }
    }
    return false;
}

// Parameters: const int& accountNumber, Account*& account
// Post: Retrieve account.
// Returns true if successful AND *Account points to account
bool AccountTree::retrieve(const int& accountNumber, Account*& account) const {
    if (this->root->getAccount(this->root)->getId() != accountNumber) {
        return retrieveHelper(accountNumber, account, this->root);
    }
    account = this->root->getAccount(this->root);
    return true;
}

// Parameters: const int& accountNumber, Account*& account, Node* node
// Post: Recurses through binary search tree to see if account exists
// and points account* to it.
// Returns true if the account is found, false if not in binary search tree
bool AccountTree::retrieveHelper(const int& accountNumber, Account*& account,
                                 Node* node) const {
    int nodeId = node->getAccount(node)->getId();
    if (nodeId != accountNumber) {
        if (nodeId < accountNumber) {
            if (node->getRight(node) != nullptr) {
                return retrieveHelper(accountNumber, account,
                                      node->getRight(node));
            }
            return false;
        }
        if (nodeId > accountNumber) {
            if (node->getLeft(node) != nullptr) {
                return retrieveHelper(accountNumber, account,
                                      node->getLeft(node));
            }
            return false;
        }
    }
    account = node->getAccount(node);
    return true;
}

// Post: Display information on all accounts.
void AccountTree::display() const {
    ofstream outputFile;
    outputFile.open("BankTransOut.txt", ofstream::app);
    displayHelper(outputFile, this->root);
}

// Parameters: ofstream& outputFile, Node* node.
// Post: Recurses through the binary search tree printing the accounts from
// smallest accounts' ID number to largest. (In-Order Recursion)
void AccountTree::displayHelper(ofstream& outputFile, Node* node) const {
    if (node != nullptr) {
        displayHelper(outputFile, node->getLeft(node));
        outputFile << *(node->getAccount(node));
        displayHelper(outputFile, node->getRight(node));
    }
}

// Post: Check if tree is empty. Returns true if empty.=, false otherwise.
bool AccountTree::isEmpty() const { return this->root == nullptr; }

// Post: Node destructor.
AccountTree::Node::~Node() = default;

// Parameter: Node* node.
// Post: Returns this Node.
Account* AccountTree::Node::getAccount(Node* node) const {
    return node->account;
}

// Parameter: Node* node.
// Post: Returns the branching Node* left.
AccountTree::Node* AccountTree::Node::getLeft(Node* node) const {
    return node->left;
}

// Parameter: Node* node.
// Post: Returns the branching Node* right.
AccountTree::Node* AccountTree::Node::getRight(Node* node) const {
    return node->right;
}

// Parameters: Node* node, Account* account.
// Post: Creates a new Node with account as its content, and assigns
// this new Node as the left branch for this node.
void AccountTree::Node::setLeft(Node* node, Account* account) {
    auto newNode = new Node(account);
    node->left = newNode;
}

// Parameters: Node* node, Account* account.
// Post: Creates a new Node with account as its content, and assigns
// this new Node as the right branch for this node.
void AccountTree::Node::setRight(Node* node, Account* account) {
    auto newNode = new Node(account);
    node->right = newNode;
}