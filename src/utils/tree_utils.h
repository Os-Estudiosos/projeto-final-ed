#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <cstring>

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
    int numRotations;
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


/**
*@brief Usando Pre-ordem, essa função imprime na tela todas as palavras da arvore com os indices dos arquivos em que fazem parte.
*@param tree Um ponteiro para arvore que terá os indices impressos.
*/
void printIndex(BinaryTree* tree);

/**
*@brief Auxilia a função que printa os indices, sendo usada de forma recursiva.
*@param aux Ponteiro para o nó que será impresso.
*@param num Ponteiro para num, usado para guardar qual posição de impressão.
*/
void auxPrint(Node *aux, int *num);

/**
*@brief Usando Pre-ordem, imprime a arvore de forma semelhante a diretórios.
*@param tree Um ponteiro para arvore que será impressa.
*/
void printTree(BinaryTree* tree);

/**
*@brief Auxilia a função printTree, printando cada uma das palavras do nós da arvore, de forma recursiva.
*@param aux Ponteiro para o nó que será impresso.
*@param space String que armazena a quantidade de espaços necessaŕios para uma identação correta.
*/
void auxPrintTree(Node *aux, std::string space);

/**
*@brief Utilizando estrutura semelhante a printIndex, conta quantos nós existem nas arvores e armazena as palavras que aparecem
*@param tree um ponteiro para a arvore
*@param words um ponteiro para o array onde as palavras serão armazenadas
*@return Retorna um inteiro, a quantidade de elementos no vector
*/
int countNodes(BinaryTree* tree, std::vector<std::string> *words);

/**
 * @brief Auxilia a função countNodes de forma recursiva
 * @param aux ponteiro para o nó a ser contado
 * @param num ponteiro para o contador de palavras
 * @param words ponteiro para vector que armazena as palavras
 */
void countNodesAux(Node *aux, int *num, std::vector<std::string> *words);
