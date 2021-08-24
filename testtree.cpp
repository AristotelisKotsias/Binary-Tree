#include <gtest/gtest.h>

#include <stdexcept>

#include "bintree.h"

TEST(insert, testDublicateKeys) {
  Node *root = nullptr;
  insert(root, 1, 2.0);
  ASSERT_EQ(root->data, 2.0);
  ASSERT_EQ(size(root), 1);
  insert(root, 1, 3.0);
  ASSERT_EQ(root->data, 3.0);
  ASSERT_EQ(size(root), 1);

  delete_tree(root);
}

TEST(insert, insertBothSides) {
  Node *root = nullptr;
  insert(root, 1, 2.0);

  ASSERT_EQ(root->data, 2.0);

  insert(root, 0, 1.0);
  insert(root, 2, 3.0);
  insert(root, 3, 4.0);

  ASSERT_EQ(root->left->data, 1.0);
  ASSERT_EQ(root->right->data, 3.0);

  // test if the key already exists the value is overwritten
  insert(root, 3, 5.0);
  ASSERT_EQ(root->right->right->data, 5.0);

  delete_tree(root);
}

TEST(remove, removeBothSides) {
  // Node *root = init(1, 2.0);
  Node *root = nullptr;
  insert(root, 1, 2.0);
  remove(root, 1);
  ASSERT_EQ(size(root), 0);

  insert(root, 0, 1.0);
  insert(root, 2, 3.0);
  insert(root, 3, 4.0);
  remove(root, 2);
  ASSERT_EQ(size(root), 2);

  delete_tree(root);
}

TEST(remove, throwsException) {
  Node *root = nullptr;
  insert(root, 1, 1);

  // this tests _that_ the expected exception is thrown
  EXPECT_THROW(
      {
        try {
          remove(root, 5);
        } catch (const std::out_of_range &e) {
          // and this tests that it has the correct message
          EXPECT_STREQ("THE KEY LOOKED FOR IS NOT IN THE TREE\n", e.what());
          throw;
        }
      },
      std::out_of_range);

  delete_tree(root);
}

TEST(min, min) {
  Node *root = init(10, 2.0);
  ASSERT_EQ(min(root)->key, 10);

  insert(root, 1, 1.0);
  insert(root, 2, 3.0);
  insert(root, 3, 4.0);
  insert(root, 4, 4.0);
  insert(root, 5, 4.0);
  insert(root, 6, 4.0);

  Node *minNode = min(root);
  int min = minNode->key;
  ASSERT_EQ(min, 1);
  delete_tree(root);
}

TEST(find, findKey) {
  Node *root = init(1, 2.0);
  ASSERT_EQ(find(root, 1), 2);

  insert(root, 0, 1.0);
  insert(root, 2, 3.0);
  insert(root, 3, 4.0);

  ASSERT_EQ(find(root, 0), 1);
  delete_tree(root);
}

TEST(find, throwsException) {
  Node *root = nullptr;
  insert(root, 1, 1);
  EXPECT_THROW(
      {
        try {
          find(root, 5);
        } catch (const std::out_of_range &e) {
          EXPECT_STREQ("THE KEY LOOKED FOR IS NOT IN THE TREE\n", e.what());
          throw;
        }
      },
      std::out_of_range);
  delete_tree(root);
}

TEST(find, throwsExceptionSize5) {
  Node *root = init(3, 2.0);
  insert(root, 0, 1.0);
  insert(root, 1, 1.0);
  insert(root, 2, 1.0);
  insert(root, 4, 1.0);
  EXPECT_THROW(
      {
        try {
          find(root, 5);
        } catch (const std::out_of_range &e) {
          EXPECT_STREQ("THE KEY LOOKED FOR IS NOT IN THE TREE\n", e.what());
          throw;
        }
      },
      std::out_of_range);
  delete_tree(root);
}

TEST(delete_tree, deleteTree) {
  Node *root = init(1, 2.0);
  delete_tree(root);
  ASSERT_EQ(root, nullptr);

  insert(root, 0, 1.0);
  insert(root, 2, 3.0);
  insert(root, 3, 4.0);

  delete_tree(root);
  ASSERT_EQ(root, nullptr);
  delete_tree(root);
}

TEST(edit, edit) {
  Node *root = init(1, 2.0);
  double &data = edit(root, 1);
  ASSERT_EQ(data, 2.0);

  insert(root, 0, 1.0);
  insert(root, 2, 3.0);
  insert(root, 4, 4.0);

  double &data1 = edit(root, 4);
  ASSERT_EQ(data1, 4.0);
  delete_tree(root);
}

TEST(edit, throwsException) {
  Node *root = nullptr;
  EXPECT_THROW(
      {
        try {
          edit(root, 5);
        } catch (const std::out_of_range &e) {
          EXPECT_STREQ("THE KEY LOOKED FOR IS NOT IN THE TREE\n", e.what());
          throw;
        }
      },
      std::out_of_range);
  delete_tree(root);
}

TEST(max_height, max_height) {
  Node *root = nullptr;
  ASSERT_EQ(max_height(root), 0);

  insert(root, 1, 2.0);
  ASSERT_EQ(max_height(root), 1);

  insert(root, 0, 1.0);
  insert(root, 2, 3.0);
  insert(root, 4, 4.0);

  unsigned int height = max_height(root);
  ASSERT_EQ(height, 3);
  delete_tree(root);
}

TEST(min_height, min_height) {
  Node *root = nullptr;
  ASSERT_EQ(min_height(root), 0);

  insert(root, 1, 2.0);
  ASSERT_EQ(min_height(root), 1);

  insert(root, 0, 1.0);
  insert(root, 2, 3.0);
  insert(root, 4, 4.0);

  unsigned int height = min_height(root);
  ASSERT_EQ(height, 2);
  delete_tree(root);
}

TEST(size, size) {
  Node *root = nullptr;
  ASSERT_EQ(size(root), 0);

  insert(root, 1, 2.0);
  ASSERT_EQ(size(root), 1);

  insert(root, 0, 1.0);
  insert(root, 2, 3.0);
  insert(root, 4, 4.0);

  unsigned int sizeTree = size(root);
  ASSERT_EQ(sizeTree, 4);
  delete_tree(root);
}

TEST(is_balanced, balanceFalse) {
  Node *root = nullptr;
  ASSERT_EQ(is_balanced(root), 1);

  insert(root, 10, 2.0);
  insert(root, 9, 1.0);
  insert(root, 8, 1.0);
  insert(root, 7, 1.0);
  insert(root, 6, 1.0);
  insert(root, 15, 1.0);
  insert(root, 12, 1.0);
  insert(root, 25, 1.0);
  insert(root, 26, 1.0);

  int balanced = is_balanced(root);
  ASSERT_EQ(balanced, 0);
  delete_tree(root);
}

TEST(allFunctions, sizeOne) {
  Node *root = nullptr;
  insert(root, 10, 10);
  ASSERT_EQ(find(root, 10), 10);
  ASSERT_EQ(edit(root, 10), 10);
  ASSERT_EQ(is_balanced(root), 1);
  ASSERT_EQ(max_height(root), 1);
  ASSERT_EQ(min_height(root), 1);
  ASSERT_EQ(size(root), 1);
  delete_tree(root);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}