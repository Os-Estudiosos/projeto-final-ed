#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "tree_utils.h"

namespace RBT
{
    enum Color {RED, BLACK};

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
