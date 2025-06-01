#include "rbt.h"

namespace RBT
{
    void rotateLeft(Node** root, Node* x)
    {
        Node* y = x->right;
        x->right = y->left;
        
        if (y->left != nullptr)
            y->left->parent = x;

        y->parent = x->parent;

        // Atualiza pai de x
        if (x->parent == nullptr)
            *root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void rotateRight(Node** root, Node* y)
    {
        Node* x = y->left;
        y->left = x->right;

        if (x->right != nullptr)
            x->right->parent = y;

        x->parent = y->parent;

        // Atualiza pai de y
        if (y->parent == nullptr)
            *root = x;
        else if (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;

        x->right = y;
        y->parent = x;
    }

    void fixInsert(Node **root, Node* z)
    {
        while (z->parent != nullptr && z->parent->isRed == RED)
        {
            Node* parent = z->parent;
            Node* grandparent = parent->parent;

            if (parent == grandparent->left)
            {
                Node* uncle = grandparent->right;

                if (uncle != nullptr && uncle->isRed == RED)
                {
                    // Tio vermelho — recoloração
                    parent->isRed = BLACK;
                    uncle->isRed = BLACK;
                    grandparent->isRed = RED;
                    z = grandparent;
                }
                else
                {
                    if (z == parent->right)
                    {
                        // Conversão para caso 3
                        z = parent;
                        rotateLeft(root, z);
                        parent = z->parent;
                        grandparent = parent->parent;
                    }

                    // Corrige com rotação
                    parent->isRed = BLACK;
                    grandparent->isRed = RED;
                    rotateRight(root, grandparent);
                }
            }
            else
            {
                Node* uncle = grandparent->left;

                if (uncle != nullptr && uncle->isRed == RED)
                {
                    parent->isRed = BLACK;
                    uncle->isRed = BLACK;
                    grandparent->isRed = RED;
                    z = grandparent;
                }
                else
                {
                    if (z == parent->left)
                    {
                        z = parent;
                        rotateRight(root, z);
                        parent = z->parent;
                        grandparent = parent->parent;
                    }

                    parent->isRed = BLACK;
                    grandparent->isRed = RED;
                    rotateLeft(root, grandparent);
                }
            }
        }

        (*root)->isRed = BLACK; // Raiz deve ser preta
    }
}
