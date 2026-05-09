// card_list.cpp
// Author: Zhe Wang
// Implementation of the classes defined in card_list.h
#include "card_list.h"
#include <iostream>
using namespace std;

CardBST::CardBST() : root(nullptr) {}

CardBST::~CardBST() { destroyTree(root); }

void CardBST::destroyTree(Node *node)
{
    if (node == nullptr)
        return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

CardBST::Node *CardBST::findMin(Node *node) const
{
    if (node == nullptr)
        return nullptr;
    while (node->left != nullptr)
        node = node->left;
    return node;
}

CardBST::Node *CardBST::findMax(Node *node) const
{
    if (node == nullptr)
        return nullptr;
    while (node->right != nullptr)
        node = node->right;
    return node;
}

CardBST::Node *CardBST::insertHelper(Node *node, Node *parent, const Card &c)
{
    if (node == nullptr)
    {
        Node *n = new Node(c);
        n->parent = parent;
        return n;
    }
    if (c < node->data)
        node->left = insertHelper(node->left, node, c);
    else if (c > node->data)
        node->right = insertHelper(node->right, node, c);
    // if equal: duplicate, do nothing
    return node;
}

void CardBST::insert(const Card &c)
{
    root = insertHelper(root, nullptr, c);
}

CardBST::Node *CardBST::removeHelper(Node *node, const Card &c)
{
    if (node == nullptr)
        return nullptr;

    if (c < node->data)
    {
        node->left = removeHelper(node->left, c);
        if (node->left)
            node->left->parent = node;
    }
    else if (c > node->data)
    {
        node->right = removeHelper(node->right, c);
        if (node->right)
            node->right->parent = node;
    }
    else
    {
        // Found the node to delete
        if (node->left == nullptr)
        { // 0 or 1 child (right)
            Node *temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr)
        { // 1 child (left)
            Node *temp = node->left;
            delete node;
            return temp;
        }
        else
        { // 2 children: swap with in order successor
            Node *succ = findMin(node->right);
            node->data = succ->data;
            node->right = removeHelper(node->right, succ->data);
            if (node->right)
                node->right->parent = node;
        }
    }
    return node;
}

void CardBST::remove(const Card &c)
{
    root = removeHelper(root, c);
    if (root)
        root->parent = nullptr;
}

bool CardBST::containsHelper(Node *node, const Card &c) const
{
    if (node == nullptr)
        return false;
    if (c == node->data)
        return true;
    if (c < node->data)
        return containsHelper(node->left, c);
    return containsHelper(node->right, c);
}

bool CardBST::contains(const Card &c) const
{
    return containsHelper(root, c);
}

void CardBST::printHelper(Node *node) const
{
    if (node == nullptr)
        return;
    printHelper(node->left);
    cout << node->data << endl; // in order = smallest to largest
    printHelper(node->right);
}

void CardBST::print() const { printHelper(root); }

bool CardBST::empty() const { return root == nullptr; }

// Successor: next card in in-order sequence
CardBST::Node *CardBST::findSuccessor(Node *node) const
{
    if (node == nullptr)
        return nullptr;
    // Case 1: has right child → go right, then all the way left
    if (node->right != nullptr)
        return findMin(node->right);
    // Case 2: no right child → climb up until we came from a left
    Node *p = node->parent;
    while (p != nullptr && node == p->right)
    {
        node = p;
        p = p->parent;
    }
    return p; // nullptr means we were at the largest node
}

// Predecessor: previous card in in order sequence
CardBST::Node *CardBST::findPredecessor(Node *node) const
{
    if (node == nullptr)
        return nullptr;
    // Case 1: has left child → go left, then all the way right
    if (node->left != nullptr)
        return findMax(node->left);
    // Case 2: no left child → climb up until we came from a right
    Node *p = node->parent;
    while (p != nullptr && node == p->left)
    {
        node = p;
        p = p->parent;
    }
    return p;
}

CardBST::Iterator CardBST::begin() const { return Iterator(findMin(root), this); }
CardBST::Iterator CardBST::end() const { return Iterator(nullptr, this); }
CardBST::Iterator CardBST::rbegin() const { return Iterator(findMax(root), this); }
CardBST::Iterator CardBST::rend() const { return Iterator(nullptr, this); }

// play game
void playGame(CardBST &alice, CardBST &bob)
{
    bool foundMatch = true;
    bool aliceTurn = true;

    while (foundMatch)
    {
        foundMatch = false;

        if (aliceTurn)
        {
            for (auto it = alice.begin(); it != alice.end(); ++it)
            {
                if (bob.contains(*it))
                {
                    cout << "Alice picked matching card " << *it << endl;
                    Card match = *it;
                    alice.remove(match);
                    bob.remove(match);
                    foundMatch = true;
                    break;
                }
            }
        }
        else
        {
            for (auto it = bob.rbegin(); it != bob.rend(); --it)
            {
                if (alice.contains(*it))
                {
                    cout << "Bob picked matching card " << *it << endl;
                    Card match = *it;
                    alice.remove(match);
                    bob.remove(match);
                    foundMatch = true;
                    break;
                }
            }
        }
        aliceTurn = !aliceTurn;
    }

    cout << "\nAlice's cards:" << endl;
    for (auto it = alice.begin(); it != alice.end(); ++it)
        cout << *it << endl;

    cout << "\nBob's cards:" << endl;
    for (auto it = bob.begin(); it != bob.end(); ++it)
        cout << *it << endl;
}
