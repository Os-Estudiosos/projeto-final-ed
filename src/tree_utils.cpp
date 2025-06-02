#include "tree_utils.h"

void printIndex(BinaryTree *tree)
{
    // implementar
}
void printTree(BinaryTree *tree)
{
    // implementar
}

Node *createNode(std::string x)
{
    Node *node = new Node();
    node->documentIds = std::vector<int>{};
    node->word = x;
    node->left = nullptr;
    node->right = nullptr;
    node->parent = nullptr;
    node->height = 0;
    node->isRed = 0;

    return node;
}

void deleteNode(Node *node)
{
    if (node == nullptr)
    {
        return;
    }
    else
    {
        deleteNode(node->left);
        deleteNode(node->right);
        delete node;
    }
}