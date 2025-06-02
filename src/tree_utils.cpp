#include "tree_utils.h"

void printIndex(BinaryTree *tree)
{
    // implementar
}
void printTree(BinaryTree *tree)
{
    // implementar
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