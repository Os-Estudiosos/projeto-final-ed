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
    int depth; 
    int height; // usado na AVL
    int isRed;  // usado na RBT
};

struct BinaryTree
{
    Node *root;
    Node *NIL; // usado na RBT (Opcional)
    int height;
    int nodeCount;  // usado para estatística
    int rotationsCount;
};

struct InsertResult
{
    int numComparisons;
    double executionTime;
};

struct SearchResult
{
    int found;
    std::vector<int> documentIds;
    double executionTime;
    int numComparisons;
};

/**
 * @brief Função que calcula a altura de uma árvore a partir de um nó.
 * @param node Nó a ser analisado.
 * @return int Altura da árvore.
 */
int computeHeight(Node* node);

/**
 * @brief Função que calcula a menor altura da árvore a partir de um nó.
 * @param node Nó que será analisado.
 * @return int Menor altura.
 */
int computeMinHeight(Node* node);

/**
 * @brief Libera recursivamente a memória de um nó e seus filhos na árvore.
 * @param node Ponteiro para o nó a ser liberado.
 */
void deleteNode(Node* node);

/**
* @brief Usando Pre-ordem, essa função imprime na tela todas as palavras da arvore com os indices dos arquivos em que fazem parte.
* @param tree Um ponteiro para arvore que terá os indices impressos.
*/
void printIndex(BinaryTree* tree);

/**
* @brief Auxilia a função que printa os indices, sendo usada de forma recursiva.
* @param aux Ponteiro para o nó que será impresso.
* @param num Ponteiro para num, usado para guardar qual posição de impressão.
*/
void auxPrint(Node *aux, int *num);

/**
* @brief Usando Pre-ordem, imprime a arvore de forma semelhante a diretórios.
* @param tree Um ponteiro para arvore que será impressa.
*/
void printTree(BinaryTree* tree);

/**
* @brief Auxilia a função printTree, printando cada uma das palavras do nós da arvore, de forma recursiva.
* @param aux Ponteiro para o nó que será impresso.
* @param space String que armazena a quantidade de espaços necessaŕios para uma identação correta.
*/
void auxPrintTree(Node *aux, std::string space);

/**
 * @brief Armazena em um vetor todas as palavras presentes na arvore, conta a quantidade de palavras unicas e define a altura da arvore, usando a função countNodesAux.
 * @param tree Ponteiro para arvore.
 * @param words Ponteiro para o vetor de palavras que será atualizado durante a função.
 * @return Retorna a quantidade de palavras unicas.
 */
int countNodes(BinaryTree* tree, std::vector<std::string> *words);

/**
 * @brief Auxilia a função countNodes de forma recursiva.
 * @param aux Ponteiro para nó.
 * @param num Ponteiro de int que armazena a quantidade de nós na arvore.
 * @param words Ponteiro para o vetor de palavras que será atualizado durante a função.
 * @param height armazena a altura do nó atual.
 * @param tree Ponteiro para arvore, usado para poder alterar sua altura.
 */
void countNodesAux(Node *aux, int *num, std::vector<std::string> *words, int height, BinaryTree* tree);

/**
 * @brief Busca uma palavra na árvore binária de busca.
 * @param tree Ponteiro para a árvore onde a busca será realizada.
 * @param word Palavra a ser buscada.
 * @return SearchResult Estrutura contendo se a palavra foi encontrada (found), a lista de documentIds, o número de comparações (numComparisons), e o tempo de execução (executionTime) em milissegundos.
 */
SearchResult search(BinaryTree *tree, const std::string &word);

/**
 * @brief Verifica se um valor está contido em um vetor de inteiros.
 * @param vec O vetor a ser verificado.
 * @param value O valor a ser procurado.
 * @return true se o valor for encontrado, false caso contrário.
 */
bool contains(const std::vector<int>& vec, int value);