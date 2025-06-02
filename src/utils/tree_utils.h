#pragma once

#include <iostream>
#include <vector>
#include <string>
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
BinaryTree* createBinaryTree();
// TODO: Adicionar Docstring
InsertResult insert(BinaryTree *tree, const std::string &word, int documentId);
// TODO: Adicionar Docstring
SearchResult search(BinaryTree *tree, const std::string &word);


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
 * @brief Cria um novo nó com a palavra fornecida.
 * 
 * @param x Palavra a ser armazenada no nó.
 * @return Node* Ponteiro para o novo nó criado.
 */
Node* createNode(std::string x);
