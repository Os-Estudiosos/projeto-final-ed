#include "bst.h"
#include "data.h"

namespace BST
{
    BinaryTree *create_BST()
    {
        BinaryTree *tree = new BinaryTree;
        tree->root = nullptr;
        return tree;
    }

    InsertResult insert(BinaryTree *tree, const std::string &word, int documentId);
    SearchResult search(BinaryTree *tree, const std::string &word);
    void delete_BST(BinaryTree *tree);
}