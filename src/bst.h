#pragma once

#include "tree_utils.h"

#include <iostream>
#include <vector>
#include <string>
#include <chrono>

namespace BST
{
    BinaryTree *create();
    InsertResult insert(BinaryTree *tree, const std::string &word, int documentId);
    SearchResult search(BinaryTree *tree, const std::string &word);
    void destroy(BinaryTree *tree);
}