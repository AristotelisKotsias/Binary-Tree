#include <unistd.h>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <tuple>
#include <vector>

#define IMPROVED 1

#include "bintree.h"

#define ITERATIONS (unsigned int)800

#define SIZE (unsigned int)9000

std::vector<int> init_vector() {
  unsigned int seed = 960219;
  std::vector<int> vec(SIZE);
  for (unsigned int i = 1; i <= SIZE; i++) {
    vec[i - 1] = i;
  }
  std::shuffle(vec.begin(), vec.end(), std::default_random_engine(seed));
  return vec;
}

std::vector<int> init_vector_improved() {
  void *trash;

  unsigned long f = reinterpret_cast<unsigned long>(&trash);
  auto rng = std::default_random_engine(f);
  std::vector<int> vec(SIZE);
  for (unsigned int i = 1; i <= SIZE; i++) {
    vec[i - 1] = i;
  }
  std::shuffle(std::begin(vec), std::end(vec), rng);
  return vec;
}

Node *init_tree(const std::vector<int> &vector) {
  Node *node = nullptr;

  for (auto i : vector) {
    insert(node, i, (double)i);
  }
  return node;
}

std::tuple<unsigned, unsigned> bench(Node *&p) {
  unsigned minh = min_height(p);
  unsigned maxh = max_height(p);

  return std::make_tuple(minh, maxh);
}

std::vector<std::tuple<unsigned, unsigned>> benchmark() {
  // init a vector with random numbers

#if IMPROVED
  std::vector<int> vec = init_vector_improved();
#else
  std::vector<int> vec = init_vector();

#endif

  std::vector<std::tuple<unsigned, unsigned>> res;
  unsigned counter = 0;
  Node *tree;

  while (counter != ITERATIONS) {
    tree = init_tree(vec);
    std::tuple<unsigned, unsigned> results = bench(tree);
    res.push_back(results);

#if IMPROVED
    unsigned long f = reinterpret_cast<unsigned long>(&tree);
    auto rng = std::default_random_engine(f);
    std::shuffle(std::begin(vec), std::end(vec), rng);
#else
    std::next_permutation(vec.begin(), vec.end());
#endif
    delete_tree(tree);
    counter++;
  }
  return res;
}

void extract_results(std::vector<std::tuple<unsigned, unsigned>> &results) {
  double avg = 0, amaxh = 0, amh = 0, adelta = 0;
  std::vector<double> mins, maxs, diffs;
  for (auto &i : results) {
    // calulate avg height
    avg += (double)((std::get<0>(i) + std::get<1>(i)) / 2);
    mins.push_back(std::get<0>(i));
    maxs.push_back(std::get<1>(i));
    amaxh += (double)std::get<1>(i);
    amh += (double)std::get<0>(i);
    diffs.push_back(std::get<1>(i) - std::get<0>(i));
    adelta += std::get<1>(i) - std::get<0>(i);
  }

  std::sort(mins.begin(), mins.end());
  std::sort(maxs.begin(), maxs.end());
  std::sort(diffs.begin(), diffs.end());
  std::cout << std::fixed;
  std::cout << std::setprecision(2);
  std::cout << "Average maximum height of the tree is : " << amaxh / ITERATIONS
            << std::endl;
  std::cout << "Average minimum height of the tree is : " << amh / ITERATIONS
            << std::endl;
  std::cout << "Highest maximum height is : " << maxs.at(maxs.size() - 1)
            << std::endl;
  std::cout << "Lowest minimum height is : " << mins.at(0) << std::endl;
  std::cout << "Average diffrence between min and max height is : "
            << adelta / ITERATIONS << std::endl;
  std::cout << "Greatest diffrence between min and max height is : "
            << diffs.at(diffs.size() - 1) << std::endl;
  std::cout << "Lowest diffrence between min and max height is : "
            << diffs.at(0) << std::endl;
}

int main() {
  std::vector<std::tuple<unsigned, unsigned>> results = benchmark();
  extract_results(results);
}