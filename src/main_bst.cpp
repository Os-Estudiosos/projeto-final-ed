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

    std::cout << "Teste 8: Buscar 'casa'\n";
    SearchResult result8 = search(tree, "casa");
    std::cout << "found: " << result8.found << "\n";
    std::cout << "numComparisons: " << result8.numComparisons << ", executionTime: " << result8.executionTime << " ms\n";
    std::cout << "DocumentIDs: ";
    printDocumentIds(result8.documentIds);
    std::cout << "Tamanho documentIds: " << result8.documentIds.size() << "\n\n";

    std::cout << "Teste 9: Buscar 'mango'\n";
    SearchResult result9 = search(tree, "mango");
    std::cout << "found: " << result9.found << "\n";
    std::cout << "numComparisons: " << result9.numComparisons << ", executionTime: " << result9.executionTime << " ms\n";
    std::cout << "DocumentIDs: ";
    printDocumentIds(result9.documentIds);
    std::cout << "documentIds vazio: " << (result9.documentIds.empty() ? "Sim" : "Nao") << "\n\n";

    std::cout << "Teste 10: Buscar 'banana'\n";
    SearchResult result10 = search(tree, "banana");
    std::cout << "found: " << result10.found << "\n";
    std::cout << "numComparisons: " << result10.numComparisons << ", executionTime: " << result10.executionTime << " ms\n";
    std::cout << "DocumentIDs: ";
    printDocumentIds(result10.documentIds);
    std::cout << "Tamanho documentIds: " << result10.documentIds.size() << "\n\n";

    std::cout << "Teste 11: Buscar 'teste' em arvore nula\n";
    SearchResult result11 = search(nullTree, "teste");
    std::cout << "found: " << result11.found << "\n";
    std::cout << "numComparisons: " << result11.numComparisons << ", executionTime: " << result11.executionTime << " ms\n";
    std::cout << "DocumentIDs: ";
    printDocumentIds(result11.documentIds);
    std::cout << "documentIds vazio: " << (result11.documentIds.empty() ? "Sim" : "Nao") << "\n\n";

    std::cout << "Teste 12: Buscar 'casa' em arvore vazia\n";
    BinaryTree *emptyTree = new BinaryTree;
    emptyTree->root = nullptr;
    SearchResult result12 = search(emptyTree, "casa");
    std::cout << "found: " << result12.found << "\n";
    std::cout << "numComparisons: " << result12.numComparisons << ", executionTime: " << result12.executionTime << " ms\n";
    std::cout << "DocumentIDs: ";
    printDocumentIds(result12.documentIds);
    std::cout << "documentIds vazio: " << (result12.documentIds.empty() ? "Sim" : "Nao") << "\n\n";

    std::cout << "Teste 13: Inserir 'casa', ID=3 e buscar 'casa'\n";
    InsertResult result13_insert = insert(tree, "casa", 3);
    std::cout << "Insercao - numComparisons: " << result13_insert.numComparisons << ", executionTime: " << result13_insert.executionTime << " ms\n";
    SearchResult result13 = search(tree, "casa");
    std::cout << "found: " << result13.found << "\n";
    std::cout << "numComparisons: " << result13.numComparisons << ", executionTime: " << result13.executionTime << " ms\n";
    std::cout << "DocumentIDs: ";
    printDocumentIds(result13.documentIds);
    std::cout << "Tamanho documentIds: " << result13.documentIds.size() << "\n\n";

    std::cout << "Teste 14: Buscar palavra vazia\n";
    SearchResult result14 = search(tree, "");
    std::cout << "found: " << result14.found << "\n";
    std::cout << "numComparisons: " << result14.numComparisons << ", executionTime: " << result14.executionTime << " ms\n";
    std::cout << "DocumentIDs: ";
    printDocumentIds(result14.documentIds);
    std::cout << "documentIds vazio: " << (result14.documentIds.empty() ? "Sim" : "Nao") << "\n\n";

    return 0;
}