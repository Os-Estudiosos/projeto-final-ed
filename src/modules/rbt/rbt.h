#pragma once

#include "../../utils/tree_utils.h"

#include <string>

namespace RBT
{
    enum Color {RED, BLACK};
    
     /**
     * @brief Cria uma nova árvore binária de busca (BST) vazia.
     * @return BinaryTree* Ponteiro para a nova árvore criada.
     */
    BinaryTree *create();
    
    /**
     * @brief Inicializa um nó com os parâmetros passados.
     * @param documentID ID do documento associado à palavra.
     * @param word Palavra a ser inserida no nó.
     * @param color Cor do nó.
     * @return Node*, um ponteiro para o nó criado.
     */
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
     * @brief Libera toda a memória alocada pela árvore binária de busca.
     * @param tree Ponteiro para a árvore a ser destruída.
     */
    void destroy(BinaryTree *tree);
    

    /**
     * @brief Realiza uma rotação à esquerda em torno do nó x.
     * @param tree Ponteiro para a árvore a ser destruída.
     * @param root Ponteiro para a raiz da árvore.
     * @param x Nó ao redor do qual a rotação será feita.
     */
    void rotateLeft( BinaryTree *tree, Node** root, Node* x);

    /**
     * @brief Realiza uma rotação à direita em torno do nó y.
     * @param tree Ponteiro para a árvore a ser destruída.
     * @param root Ponteiro para a raiz da árvore.
     * @param y Nó ao redor do qual a rotação será feita.
     */
    void rotateRight( BinaryTree *tree, Node** root, Node* y);

    /**
     * @brief Corrige as violações da propriedade rubro-negra após uma inserção.
     * @param root Ponteiro para a raiz da árvore.
     * @param z Nó recém-inserido que pode causar violação.
     * @param tree Ponteiro para a árvore a ser destruída.
     */
    void fixInsert(Node **root, Node* z, BinaryTree *tree);

    /**
     * @brief Obtém a altura de um nó, retornando 0 se o nó for nulo.
     * @param node Ponteiro para o nó.
     * @return int A altura do nó.
     */
    int getNodeHeight(Node* node);

    /**
     * @brief Atualiza a altura de um nó com base na altura máxima de seus filhos.
     * @param node Ponteiro para o nó a ser atualizado.
     */
    void updateNodeHeight(Node* node);

    /**
     * @brief Sobe na árvore a partir de um nó, atualizando a altura de seus ancestrais.
     * @param node Nó inicial para a atualização.
     */
    void updateHeightUpwards(Node* node);
}
