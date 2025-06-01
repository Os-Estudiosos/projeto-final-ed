#pragma once

#include <iostream>
#include <vector>
#include <chrono>

struct Node 
{
    std::string word;
    std::vector<int> documentIds;
    Node* parent;
    Node* left;
    Node* right;
    int height;    // usado na AVL
    int isRed;     // usado na RBT
};

struct BinaryTree 
{
    Node* root;
    Node* NIL;  // usado na RBT (Opcional)
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



// TODO: Adicionar Docstring
BinaryTree *create();
// TODO: Adicionar Docstring
InsertResult insert(BinaryTree *tree, const std::string &word, int documentId);
// TODO: Adicionar Docstring
SearchResult search(BinaryTree *tree, const std::string &word);


// TODO: Adicionar docstring
void printIndex(BinaryTree* tree);
// TODO: Adicionar docstring
void printTree(BinaryTree* tree);



/**
 * @brief Cria um novo nó com a palavra fornecida.
 * 
 * @param x Palavra a ser armazenada no nó.
 * @return Node* Ponteiro para o novo nó criado.
 */
Node* createNode(std::string x);


/**
 * @brief Insere uma palavra na árvore binária de busca.
 * 
 * @param root Raiz da árvore/subárvore.
 * @param x Palavra a ser inserida.
 * @return Node* Ponteiro para a nova raiz após a inserção.
 */
Node* insert(Node* root, std::string x);



/**
 * @brief Procura uma palavra na árvore binária de busca.
 * @param root Raiz da árvore/subárvore.
 * @param x Palavra a ser inserida.
 * @return Node* Ponteiro para a palavra procurada.
 */
Node* treeSearch(Node* root, std::string x);

