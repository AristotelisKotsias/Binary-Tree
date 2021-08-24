#include "bintree.h"

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <limits>

// helper function
Node* newNode(int key, double data) {
  Node* toReturn = new Node;
  toReturn->data = data;
  toReturn->key = key;
  toReturn->left = nullptr;
  toReturn->right = nullptr;
  return toReturn;
}

Node* init(const int key, double data) { return newNode(key, data); }

void insert(Node*& p, int key, double to_be_inserted) {
  if (!p) {
    p = newNode(key, to_be_inserted);
    return;
  } else if (!(p->key < key) && !(key < p->key)) {
    p->data = to_be_inserted;
  } else if (p->key < key) {
    insert(p->right, key, to_be_inserted);
  } else {
    insert(p->left, key, to_be_inserted);
  }
}

// helper function tha calculates the min node for a given tree
Node* min(Node* n) {
  Node* current = n;
  while (current->left != nullptr) current = current->left;

  return current;
}

void remove(Node*& p, const int& key) {
  if (!p) throw std::out_of_range("THE KEY LOOKED FOR IS NOT IN THE TREE\n");

  // search for key on left subtree
  if (key < p->key) {
    remove(p->left, key);
  }
  // search for key on right subtree
  else if (p->key < key) {
    remove(p->right, key);
  } else {
    if (!p->right && !p->left) {
      delete p;
      p = nullptr;
    } else if (p->right && p->left) {
      Node* temp = min(p->right);
      p->key = temp->key;
      p->data = temp->data;
      remove(p->right, temp->data);
    } else {
      Node* temp = (p->left) ? p->left : p->right;
      delete p;
      p = temp;
    }
  }
}

void delete_tree(Node*& p) {
  if (!p) return;
  delete_tree(p->left);
  delete_tree(p->right);
  delete p;
  p = nullptr;
}

const double& find(Node* p, const int& to_be_found) {
  if (!p) {
    throw std::out_of_range("THE KEY LOOKED FOR IS NOT IN THE TREE\n");
  } else if (!(p->key < to_be_found) && !(to_be_found < p->key)) {
    return p->data;
  } else if (p->key < to_be_found) {  // check right tree
    return find(p->right, to_be_found);
  } else {  // check left tree
    return find(p->left, to_be_found);
  }
}
double& edit(Node* p, const int& to_be_changed) {
  if (!p) throw std::out_of_range("THE KEY LOOKED FOR IS NOT IN THE TREE\n");

  if (!(p->key < to_be_changed) && !(to_be_changed < p->key)) {
    return p->data;
  } else if (to_be_changed < p->key) {
    return edit(p->left, to_be_changed);
  } else {
    return edit(p->right, to_be_changed);
  }
}

unsigned int max_height(Node* p) {
  if (!p) return 0;

  // Get the depth of the left and right subtree
  int lHeight = max_height(p->left);
  int rHeight = max_height(p->right);

  // Choose the larger one and add the root to it.
  return (lHeight > rHeight) ? lHeight + 1 : rHeight + 1;
}

unsigned int min_height(Node* p) {
  if (!p) return 0;

  // Get the depth of the left and right subtree
  int lHeight = min_height(p->left);
  int rHeight = min_height(p->right);

  // Choose the smallest one and add the root to it.
  return (lHeight > rHeight) ? rHeight + 1 : lHeight + 1;
}

unsigned int size(Node* p) {
  if (!p)
    return 0;
  else
    return (size(p->left) + 1 + size(p->right));
}

bool is_balanced(Node* p) {
  if (!p) return true;

  int lHeight = max_height(p->left);
  int rHeight = max_height(p->right);

  return (abs(lHeight - rHeight) <= 1 && is_balanced(p->left) &&
          is_balanced(p->right))
             ? true
             : false;
}