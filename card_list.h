// card_list.h
// Author: Zhe Wang
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H
#include "card.h"

class CardBST
{
private:
    struct Node
    {
        Card data;
        Node *left;
        Node *right;
        Node *parent;
        Node(const Card &c)
            : data(c), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node *root;

    Node *insertHelper(Node *node, Node *parent, const Card &c);
    Node *removeHelper(Node *node, const Card &c);
    Node *findMin(Node *node) const;
    Node *findMax(Node *node) const;
    bool containsHelper(Node *n, const Card &c) const;
    void printHelper(Node *n) const;
    void destroyTree(Node *n);
    Node *findSuccessor(Node *n) const;
    Node *findPredecessor(Node *n) const;

public:
    class Iterator
    {
        Node *current;
        const CardBST *tree;

    public:
        Iterator(Node *n, const CardBST *t) : current(n), tree(t) {}

        const Card &operator*() const { return current->data; }
        const Card *operator->() const { return &current->data; }

        Iterator &operator++()
        { // move to next (forward)
            current = tree->findSuccessor(current);
            return *this;
        }
        Iterator &operator--()
        { // move to prev (backward)
            current = tree->findPredecessor(current);
            return *this;
        }
        bool operator==(const Iterator &o) const { return current == o.current; }
        bool operator!=(const Iterator &o) const { return current != o.current; }
    };

    CardBST();
    ~CardBST();

    void insert(const Card &c);
    void remove(const Card &c);
    bool contains(const Card &c) const;
    void print() const;
    bool empty() const;

    Iterator begin() const;  // smallest card
    Iterator end() const;    // past the end
    Iterator rbegin() const; // largest card
    Iterator rend() const;   // past ther end
};

void playGame(CardBST &alice, CardBST &bob);
#endif
