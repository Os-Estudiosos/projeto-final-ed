#pragma once

#include "../../utils/tree_utils.h"

#include <vector>
#include <string>
#include <iostream>


namespace RBT
{
    enum Color {RED, BLACK};
    
     /**
     * @brief Cria uma nova árvore binária de busca (BST) vazia.
     * @return BinaryTree* Ponteiro para a nova árvore criada.
     */
    BinaryTree *create();

    Node* createNode(int documentId, const std::string &word, Color color);
    

    /**
     * @brief Insere uma palavra e um ID de documento na árvore binária de busca.
     * @param tree Ponteiro para a árvore onde a palavra será inserida.
     * @param word Palavra a ser inserida.
     * @param documentId ID do documento associado à palavra.
     * @return InsertResult Estrutura contendo o número de comparações (numComparisons) e o tempo de execução (executionTime) em milissegundos.
     */
    InsertResult insert(BinaryTree *tree, const std::string &word, int documentId);

    /**
     * @brief Busca uma palavra na árvore binária de busca.
     * @param tree Ponteiro para a árvore onde a busca será realizada.
     * @param word Palavra a ser buscada.
     * @return SearchResult Estrutura contendo se a palavra foi encontrada (found), a lista de documentIds, o número de comparações (numComparisons), e o tempo de execução (executionTime) em milissegundos.
     */
    SearchResult search(BinaryTree *tree, const std::string &word);

    /**
     * @brief Libera toda a memória alocada pela árvore binária de busca.
     * @param tree Ponteiro para a árvore a ser destruída.
     */
    void destroy(BinaryTree *tree);
    

    /**
     * @brief Realiza uma rotação à esquerda em torno do nó x.
     * 
     * @param root Ponteiro para a raiz da árvore.
     * @param x Nó ao redor do qual a rotação será feita.
     */
    void rotateLeft(Node** root, Node* x);

    /**
     * @brief Realiza uma rotação à direita em torno do nó y.
     * 
     * @param root Ponteiro para a raiz da árvore.
     * @param y Nó ao redor do qual a rotação será feita.
     */
    void rotateRight(Node** root, Node* y);

    /**
     * @brief Corrige as violações da propriedade rubro-negra após uma inserção.
     * 
     * @param root Ponteiro para a raiz da árvore.
     * @param z Nó recém-inserido que pode causar violação.
     */
    void fixInsert(Node **root, Node* z);
}
