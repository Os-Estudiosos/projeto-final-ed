#pragma once

#include "../../utils/tree_utils.h"

#include <string>

namespace BST
{
    /**
     * @brief Cria uma nova árvore binária de busca (BST) vazia.
     * @return BinaryTree* Ponteiro para a nova árvore criada.
     */
    BinaryTree *create();

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
}