#include "modules/bst/bst.h"
#include "utils/tree_utils.h"

#include <iostream>
#include <string>
#include <chrono>

using namespace BST;
using namespace std;

// tirar isso em breve
void printTree(Node *node)
{
    if (node == nullptr)
        return;
    printTree(node->left);
    cout << "Palavra: " << node->word << ", DocumentIDs: ";
    for (int id : node->documentIds)
    {
        cout << id << " ";
    }
    cout << endl;
    printTree(node->right);
}

void printDocumentIds(const vector<int> &ids)
{
    for (int id : ids)
    {
        cout << id << " ";
    }
    cout << endl;
}

int main()
{

    BinaryTree *tree = new BinaryTree;
    tree->root = nullptr;

    cout << "Teste 1: Inserir 'casa', ID=1 em arvore vazia\n";
    InsertResult result1 = insert(tree, "casa", 1);
    cout << "numComparisons: " << result1.numComparisons << ", executionTime: " << result1.executionTime << " ms\n";
    cout << "Raiz: " << tree->root->word << ", DocumentIDs: ";
    printDocumentIds(tree->root->documentIds);
    cout << "Esquerda: " << (tree->root->left == nullptr ? "nullptr" : "nao nulo") << ", Direita: " << (tree->root->right == nullptr ? "nullptr" : "não nulo") << "\n\n";

    cout << "Teste 2: Inserir 'casa', ID=2\n";
    InsertResult result2 = insert(tree, "casa", 2);
    cout << "numComparisons: " << result2.numComparisons << ", executionTime: " << result2.executionTime << " ms\n";
    cout << "Raiz: " << tree->root->word << ", DocumentIDs: ";
    printDocumentIds(tree->root->documentIds);
    cout << "\n";

    cout << "Teste 3: Inserir 'casa', ID=2 (duplicado)\n";
    InsertResult result3 = insert(tree, "casa", 2);
    cout << "numComparisons: " << result3.numComparisons << ", executionTime: " << result3.executionTime << " ms\n";
    cout << "Raiz: " << tree->root->word << ", DocumentIDs: ";
    printDocumentIds(tree->root->documentIds);
    cout << "\n";

    cout << "Teste 4: Inserir 'apple', ID=3\n";
    InsertResult result4 = insert(tree, "apple", 3);
    cout << "numComparisons: " << result4.numComparisons << ", executionTime: " << result4.executionTime << " ms\n";
    cout << "Esquerda: " << tree->root->left->word << ", DocumentIDs: ";
    printDocumentIds(tree->root->left->documentIds);
    cout << "Pai da esquerda aponta para raiz: " << (tree->root->left->parent == tree->root ? "Sim" : "Nao") << "\n\n";

    cout << "Teste 5: Inserir 'zebra', ID=4\n";
    InsertResult result5 = insert(tree, "zebra", 4);
    cout << "numComparisons: " << result5.numComparisons << ", executionTime: " << result5.executionTime << " ms\n";
    cout << "Direita: " << tree->root->right->word << ", DocumentIDs: ";
    printDocumentIds(tree->root->right->documentIds);
    cout << "Pai da direita aponta para raiz: " << (tree->root->right->parent == tree->root ? "Sim" : "Nao") << "\n\n";

    cout << "Teste 6: Inserir 'teste', ID=5 em arvore nula\n";
    BinaryTree *nullTree = nullptr;
    InsertResult result6 = insert(nullTree, "teste", 5);
    cout << "numComparisons: " << result6.numComparisons << ", executionTime: " << result6.executionTime << " ms\n\n";

    cout << "Teste 7: Inserir 'banana', ID=6\n";
    InsertResult result7 = insert(tree, "banana", 6);
    cout << "numComparisons: " << result7.numComparisons << ", executionTime: " << result7.executionTime << " ms\n";
    cout << "Esquerda->Direita: " << tree->root->left->right->word << ", DocumentIDs: ";
    printDocumentIds(tree->root->left->right->documentIds);
    cout << "Pai de banana aponta para apple: " << (tree->root->left->right->parent == tree->root->left ? "Sim" : "Nao") << "\n\n";

    cout << "Estrutura final da arvore (inordem):\n";
    printTree(tree->root);

    cout << "Teste 8: Buscar 'casa'\n";
    SearchResult result8 = search(tree, "casa");
    cout << "found: " << result8.found << "\n";
    cout << "numComparisons: " << result8.numComparisons << ", executionTime: " << result8.executionTime << " ms\n";
    cout << "DocumentIDs: ";
    printDocumentIds(result8.documentIds);
    cout << "Tamanho documentIds: " << result8.documentIds.size() << "\n\n";

    cout << "Teste 9: Buscar 'mango'\n";
    SearchResult result9 = search(tree, "mango");
    cout << "found: " << result9.found << "\n";
    cout << "numComparisons: " << result9.numComparisons << ", executionTime: " << result9.executionTime << " ms\n";
    cout << "DocumentIDs: ";
    printDocumentIds(result9.documentIds);
    cout << "documentIds vazio: " << (result9.documentIds.empty() ? "Sim" : "Nao") << "\n\n";

    cout << "Teste 10: Buscar 'banana'\n";
    SearchResult result10 = search(tree, "banana");
    cout << "found: " << result10.found << "\n";
    cout << "numComparisons: " << result10.numComparisons << ", executionTime: " << result10.executionTime << " ms\n";
    cout << "DocumentIDs: ";
    printDocumentIds(result10.documentIds);
    cout << "Tamanho documentIds: " << result10.documentIds.size() << "\n\n";

    cout << "Teste 11: Buscar 'teste' em arvore nula\n";
    SearchResult result11 = search(nullTree, "teste");
    cout << "found: " << result11.found << "\n";
    cout << "numComparisons: " << result11.numComparisons << ", executionTime: " << result11.executionTime << " ms\n";
    cout << "DocumentIDs: ";
    printDocumentIds(result11.documentIds);
    cout << "documentIds vazio: " << (result11.documentIds.empty() ? "Sim" : "Nao") << "\n\n";

    cout << "Teste 12: Buscar 'casa' em arvore vazia\n";
    BinaryTree *emptyTree = new BinaryTree;
    emptyTree->root = nullptr;
    SearchResult result12 = search(emptyTree, "casa");
    cout << "found: " << result12.found << "\n";
    cout << "numComparisons: " << result12.numComparisons << ", executionTime: " << result12.executionTime << " ms\n";
    cout << "DocumentIDs: ";
    printDocumentIds(result12.documentIds);
    cout << "documentIds vazio: " << (result12.documentIds.empty() ? "Sim" : "Nao") << "\n\n";

    cout << "Teste 13: Inserir 'casa', ID=3 e buscar 'casa'\n";
    InsertResult result13_insert = insert(tree, "casa", 3);
    cout << "Insercao - numComparisons: " << result13_insert.numComparisons << ", executionTime: " << result13_insert.executionTime << " ms\n";
    SearchResult result13 = search(tree, "casa");
    cout << "found: " << result13.found << "\n";
    cout << "numComparisons: " << result13.numComparisons << ", executionTime: " << result13.executionTime << " ms\n";
    cout << "DocumentIDs: ";
    printDocumentIds(result13.documentIds);
    cout << "Tamanho documentIds: " << result13.documentIds.size() << "\n\n";

    cout << "Teste 14: Buscar palavra vazia\n";
    SearchResult result14 = search(tree, "");
    cout << "found: " << result14.found << "\n";
    cout << "numComparisons: " << result14.numComparisons << ", executionTime: " << result14.executionTime << " ms\n";
    cout << "DocumentIDs: ";
    printDocumentIds(result14.documentIds);
    cout << "documentIds vazio: " << (result14.documentIds.empty() ? "Sim" : "Nao") << "\n\n";

    destroy(tree);
    destroy(emptyTree);
    destroy(nullTree);

    return 0;
}