#include "bst.h"
#include <iostream>
#include <string>
#include <chrono>
#include <chrono>

using namespace BST;

void printTree(Node *node)
{
    if (node == nullptr)
        return;
    printTree(node->left);
    std::cout << "Palavra: " << node->word << ", DocumentIDs: ";
    for (int id : node->documentIds)
    {
        std::cout << id << " ";
    }
    std::cout << std::endl;
    printTree(node->right);
}

void printDocumentIds(const std::vector<int> &ids)
{
    for (int id : ids)
    {
        std::cout << id << " ";
    }
    std::cout << std::endl;
}

int main()
{
    BinaryTree *tree = new BinaryTree;
    tree->root = nullptr;

    std::cout << "Teste 1: Inserir 'casa', ID=1 em arvore vazia\n";
    InsertResult result1 = insert(tree, "casa", 1);
    std::cout << "numComparisons: " << result1.numComparisons << ", executionTime: " << result1.executionTime << " ms\n";
    std::cout << "Raiz: " << tree->root->word << ", DocumentIDs: ";
    printDocumentIds(tree->root->documentIds);
    std::cout << "Esquerda: " << (tree->root->left == nullptr ? "nullptr" : "nao nulo") << ", Direita: " << (tree->root->right == nullptr ? "nullptr" : "não nulo") << "\n\n";

    std::cout << "Teste 2: Inserir 'casa', ID=2\n";
    InsertResult result2 = insert(tree, "casa", 2);
    std::cout << "numComparisons: " << result2.numComparisons << ", executionTime: " << result2.executionTime << " ms\n";
    std::cout << "Raiz: " << tree->root->word << ", DocumentIDs: ";
    printDocumentIds(tree->root->documentIds);
    std::cout << "\n";

    std::cout << "Teste 3: Inserir 'casa', ID=2 (duplicado)\n";
    InsertResult result3 = insert(tree, "casa", 2);
    std::cout << "numComparisons: " << result3.numComparisons << ", executionTime: " << result3.executionTime << " ms\n";
    std::cout << "Raiz: " << tree->root->word << ", DocumentIDs: ";
    printDocumentIds(tree->root->documentIds);
    std::cout << "\n";

    std::cout << "Teste 4: Inserir 'apple', ID=3\n";
    InsertResult result4 = insert(tree, "apple", 3);
    std::cout << "numComparisons: " << result4.numComparisons << ", executionTime: " << result4.executionTime << " ms\n";
    std::cout << "Esquerda: " << tree->root->left->word << ", DocumentIDs: ";
    printDocumentIds(tree->root->left->documentIds);
    std::cout << "Pai da esquerda aponta para raiz: " << (tree->root->left->parent == tree->root ? "Sim" : "Nao") << "\n\n";

    std::cout << "Teste 5: Inserir 'zebra', ID=4\n";
    InsertResult result5 = insert(tree, "zebra", 4);
    std::cout << "numComparisons: " << result5.numComparisons << ", executionTime: " << result5.executionTime << " ms\n";
    std::cout << "Direita: " << tree->root->right->word << ", DocumentIDs: ";
    printDocumentIds(tree->root->right->documentIds);
    std::cout << "Pai da direita aponta para raiz: " << (tree->root->right->parent == tree->root ? "Sim" : "Nao") << "\n\n";

    std::cout << "Teste 6: Inserir 'teste', ID=5 em arvore nula\n";
    BinaryTree *nullTree = nullptr;
    InsertResult result6 = insert(nullTree, "teste", 5);
    std::cout << "numComparisons: " << result6.numComparisons << ", executionTime: " << result6.executionTime << " ms\n\n";

    std::cout << "Teste 7: Inserir 'banana', ID=6\n";
    InsertResult result7 = insert(tree, "banana", 6);
    std::cout << "numComparisons: " << result7.numComparisons << ", executionTime: " << result7.executionTime << " ms\n";
    std::cout << "Esquerda->Direita: " << tree->root->left->right->word << ", DocumentIDs: ";
    printDocumentIds(tree->root->left->right->documentIds);
    std::cout << "Pai de banana aponta para apple: " << (tree->root->left->right->parent == tree->root->left ? "Sim" : "Nao") << "\n\n";

    std::cout << "Estrutura final da arvore (inordem):\n";
    printTree(tree->root);

    return 0;
}