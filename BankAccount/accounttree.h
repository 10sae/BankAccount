//
// Created by Tensae Woldeselassie (tensaew) and Gabriel Oliver (gaog1999) on
// 3/3/2020.
//

#pragma once

#include "account.h"
#include <iostream>

class AccountTree {
  private:
    class Node {
      public:
        // Parameter: Account* account.
        // Post: Constructs instance of private Node class.
        explicit Node(Account* account)
            : account{account}, right{nullptr}, left{nullptr} {}

        // Post: Node destructor.
        ~Node();

        // Parameter: Node* node.
        // Post: Returns this Node.
        Account* getAccount(Node* node) const;

        // Parameter: Node* node.
        // Post: Returns the branching Node* left.
        Node* getLeft(Node* node) const;
        
        // Parameter: Node* node.
        // Post: Returns the branching Node* right.
        Node* getRight(Node* node) const;
        
        // Parameters: Node* node, Account* account.
        // Post: Creates a new Node with account as its content, and assigns
        // this new Node as the left branch for this node.
        void setLeft(Node* node, Account* account);
        
        // Parameters: Node* node, Account* account.
        // Post: Creates a new Node with account as its content, and assigns
        // this new Node as the right branch for this node.
        void setRight(Node* node, Account* account);
      private:
        // The account stored in this Node.
        Account* account;
        // Node that branches right from the current Node.
        Node* right;
        // Node that branches left from the current Node.
        Node* left;        
    };
    // The root Node of the binary search tree.
    Node* root;

    // Parameters: Node* node, Account* account, int accountId
    // Post: Recurses through binary search tree to insert an account.
    // Returns true if the account is successfully inserted, false if the
    // account already exists.
    bool insertHelper(Node* node, Account* account, int accountId);

    // Parameters: const int& accountNumber, Account*& account, Node* node
    // Post: Recurses through binary search tree to see if account exists
    // and points account* to it.
    // Returns true if the account is found, false if not in binary search tree
    // NOLINTNEXTLINE
    bool retrieveHelper(const int& accountNumber, Account*& account,
                        Node* node) const;

    // Parameters: ofstream& outputFile, Node* node.
    // Post: Recurses through the binary search tree printing the accounts from
    // smallest accounts' ID number to largest. (In-Order Recursion)
    void displayHelper(ofstream& outputFile, Node* node) const;

    // Parameter: Node* node
    // Post: Delete all information in AccountTree.
    void clearHelper(Node* node);
  public:
    // Post: Create BST.
    // Constructs instance of AccountTree.
    AccountTree();

    // Post: Delete all nodes in BST.
    ~AccountTree();

    // Post: Calls to clear the binary search tree. 
    void clear();

    // Parameter: Account* account
    // Post: Insert new account.
    bool insert(Account* account);

    // Parameters: const int& accountNumber, Account*& account
    // Post: Retrieve account.
    // Returns true if successful AND *Account points to account
    // NOLINTNEXTLINE
    bool retrieve(const int& accountNumber, Account*& account) const;

    // Post: Display information on all accounts.
    void display() const;

    // Post: Check if tree is empty. Returns true if empty.=, false otherwise.
    bool isEmpty() const;
};
