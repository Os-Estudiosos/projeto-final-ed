#include "tree_utils.h"


void printIndex(BinaryTree* tree)
{
    // implementar 
}
void printTree(BinaryTree* tree)
{
    // implementar 
}


Node* createNode(std::string x) 
{
    Node* n = new Node();
    n->documentIds = std::vector<int>{};
    n->word = x;
    n->left = nullptr;
    n->right = nullptr;
    n->parent = nullptr;
    n->height = 0;
    n->isRed = 0;

    return n;
}


Node* insert(Node* root, std::string x) 
{
    if (root == nullptr) // Posição correta encontrada
        return createNode(x);

    if (x < root->word) 
    {
        Node* leftChild = insert(root->left, x);
        root->left = leftChild;
        leftChild->parent = root; // Atualiza pai
    } else if (x > root->word) 
    {
        Node* rightChild = insert(root->right, x);
        root->right = rightChild;
        rightChild->parent = root; // Atualiza pai
    }
    return root;
}


Node* treeSearch(Node* root, std::string x) 
{
    if (root == nullptr || root->word == x) 
    {
        return root;
    }

    if (x < root->word) 
    {
        return treeSearch(root->left, x);
    } else {
        return treeSearch(root->right, x);
    }
}

int main(){

}