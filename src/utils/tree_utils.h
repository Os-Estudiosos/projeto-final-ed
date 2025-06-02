#pragma once

#include <iostream>
#include <vector>
#include <chrono>

struct Node
{
    std::string word;
    std::vector<int> documentIds;
    Node *parent;
    Node *left;
    Node *right;
    int height; // usado na AVL
    int isRed;  // usado na RBT
};

struct BinaryTree
{
    Node *root;
    Node *NIL; // usado na RBT (Opcional)
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

// TODO: Adicionar docstring
void printIndex(BinaryTree *tree);
// TODO: Adicionar docstring
void printTree(BinaryTree *tree);

/**
 * @brief Função que calcula a altura de uma árvore a partir de um nó
 * 
 * @param node Nó a ser analisado
 * @return int Altura da árvore
 */
int computeHeight(Node* node);

/**
 * @brief Função que calcula a menor altura da árvore a partir de um nó
 * 
 * @param node Nó que será analisado
 * @return int Menor altura
 */
int computeMinHeight(Node* node);

/**
 * @brief Libera recursivamente a memória de um nó e seus filhos na árvore.
 * @param node Ponteiro para o nó a ser liberado.
 */
void deleteNode(Node* node);
