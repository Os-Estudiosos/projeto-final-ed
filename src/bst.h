#ifndef BST_H
#define BST_H

#include <iostream>
#include <vector>
#include <string>
#include <chrono>

namespace BST
{
    struct Node
    {
        std::string word;
        std::vector<int> documentIds;
        Node *parent;
        Node *left;
        Node *right;
    };

    struct BinaryTree
    {
        Node *root;
    };

    struct InsertResult
    {
        int numComparisons;
        double executionTime;
        //<Possíveis outras variáveis>
    };

    struct SearchResult
    {
        int found;
        std::vector<int> documentIds;
        double executionTime;
        int numComparisons;
        //<Possíveis outras variáveis>
    };

    BinaryTree *create();
    InsertResult insert(BinaryTree *tree, const std::string &word, int documentId);
    SearchResult search(BinaryTree *tree, const std::string &word);
    void delete_BST(BinaryTree *tree);
}
#endif