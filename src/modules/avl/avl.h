#pragma once

#include "../../utils/tree_utils.h"
#include <string>

namespace AVL
{

    /**
     * @brief Cria uma nova árvore binária de busca balanceada (AVL) vazia.
     * @return Ponteiro para a nova árvore criada.
     */
    BinaryTree *create();
    
    /**
     * @brief Inicializa um nó com os parâmetros passados.
     * @param documentID ID do documento associado à palavra.
     * @param word Palavra a ser inserida no nó.
     * @return Ponteiro para o nó criado.
     */
    Node* createNode(int documentId, const std::string &word);
    
    /**
     * @brief Insere uma palavra e um ID de documento na árvore binária de busca balanceada.
     * @param tree Ponteiro para a árvore onde a palavra será inserida.
     * @param word Palavra a ser inserida.
     * @param documentId ID do documento associado à palavra.
     * @return Estrutura contendo o número de comparações (numComparisons) e o tempo de execução (executionTime) em milissegundos.
     */
    InsertResult insert(BinaryTree *tree, const std::string &word, int documentId);

    /**
     * @brief Busca uma palavra na árvore binária de busca balanceada.
     * @param tree Ponteiro para a árvore onde a busca será realizada.
     * @param word Palavra a ser buscada.
     * @return Estrutura contendo se a palavra foi encontrada (found), a lista de documentIds, o número de comparações (numComparisons), e o tempo de execução (executionTime) em milissegundos.
     */
    SearchResult search(BinaryTree *tree, const std::string &word);

    /**
     * @brief Libera toda a memória alocada pela árvore binária de busca balanceada.
     * @param tree Ponteiro para a árvore a ser destruída.
     */
    void destroy(BinaryTree *tree);
    
    /**
     * @brief Realiza uma rotação à esquerda em torno do nó x.
     * @param root Ponteiro para a raiz da árvore.
     * @param x Nó ao redor do qual a rotação será feita.
     */
    Node* rotateLeft(Node* x);

    /**
     * @brief Realiza uma rotação à direita em torno do nó y.
     * @param root Ponteiro para a raiz da árvore.
     * @param y Nó ao redor do qual a rotação será feita.
     */
    Node* rotateRight(Node* y);

    /**
     * @brief Calcula a altura de um nó.
     * @param n Ponteiro para o nó cujo altura será calculada.
     * @return Altura do nó.
     */
    int getHeight(Node* n);

    /**
     * @brief Recalcula a altura mínima de um nó.
     * @param n Ponteiro para o nó cujo altura mínima será calculada.
     * @return Altura mínima do nó recalculada.
     */
    void recomputeHeight(Node* n);

    /**
     * @brief Calcula o fator de balanceamento de um nó.
     * @param n Ponteiro para o nó cujo fator de balanceamento será calculado.
     * @return Fator de balanceamento do nó.
     */
    int balanceFactor(Node* n);

    /**
     * @brief Calcula o maior valor entre dois inteiros.
     * @param a Primeiro inteiro.
     * @param b Segundo inteiro.
     * @return O maior valor entre a e b.
     */
    int max(int a, int b);

    /**
     * @brief Corrige a inserção de um nó na árvore AVL.
     * @param root Ponteiro para a raiz da árvore.
     * @param x Nó que foi inserido e precisa ser corrigido.
     */
    void fixInsert(Node** root, Node* x);

    /**
     * @brief Verifica se duas árvores são iguais.
     * @param root1 Ponteiro para a raiz da primeira árvore.
     * @param root2 Ponteiro para a raiz da segunda árvore.
     * @returns True se forem iguais ou False se forem diferentes 
     */
    bool isEqual(Node* root1, Node* root2);
}
