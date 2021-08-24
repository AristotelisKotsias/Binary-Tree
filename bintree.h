#pragma once

#include <stdlib.h>

struct Node {
    int key;
    double data;
    Node *right;
    Node *left;
};

Node *init(int, double);
Node *min(Node *);

/* Inserts key and value in the binary tree, initialize the new nodes left and right 
to nullptr. If the key already exists the value is overwritten, duplicate keys are not 
allowed */
void insert(Node *&, int, double);

/* Remove the node with this key. If the node has two children you need to find the 
find the minimum node to the right. Copy that node to the node with the key to be deleted 
and remove the found minimum node instead */
void remove(Node *&, const int &);

/* Deletes the entire tree at p */
void delete_tree(Node *&);

/* Find the node with key and returns it associated data */
const double &find(Node *, const int &);

/* Find and return a reference to editable data associated with the key */
double &edit(Node *, const int &);

/* returns true if the tree is balanced */
bool is_balanced(Node *);

/* returns the height (longest chain) of the tree */
unsigned int max_height(Node *);

/* returns the shortest chain of the tree */
unsigned int min_height(Node *);

/* returns the number of nodes (p included) in the tree */
unsigned int size(Node *);