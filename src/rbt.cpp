#include "rbt.h"

namespace RBT
{
    void rotateLeft(Node** root, Node* x)
    {
        Node* y = x->right;
        x->right = y->left;
        
        if(y->left != nullptr)
        {
            y->left->parent = x;
        }

        y->parent = x->parent;

        if (x->parent == nullptr)
        {
            *root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }

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
            Node* grandparent = z->parent->parent;
            
            // pai é filho da esquerda
            if (parent == grandparent->left) 
            { 
                Node* uncle = grandparent->right; 
                
                // Caso 1: pai e tio são vermelhos 
                if (uncle->isRed == RED) 
                {
                    parent->isRed = BLACK;
                    uncle->isRed = BLACK;
                    grandparent->isRed = RED;
                    z = grandparent;
                } else {
                    // Caso 2: z é filho à direita 
                    if (z == parent->right) 
                    {
                        z = parent;
                        rotateLeft(root, z);
                        parent = z->parent;
                        grandparent = parent->parent;
                    }
                    // Caso 3: z é filho à esquerda 
                    parent->isRed = BLACK;
                    grandparent->isRed = RED;
                    rotateRight(root, grandparent);
                }
            } else 
            {
                // Casos simétricos (pai é filho da direita)
                Node* uncle = grandparent->left;

                // Caso 1
                if (uncle != nullptr && uncle->isRed == RED) 
                {
                    parent->isRed = BLACK;
                    uncle->isRed = BLACK;
                    grandparent->isRed = RED;
                    z = grandparent;
                } else {
                    // Caso 2
                    if (z == parent->left) 
                    {
                        z = parent;
                        rotateRight(root, z);
                        parent = z->parent;
                        grandparent = parent->parent;
                    }
                    // Caso 3
                    parent->isRed = BLACK;
                    grandparent->isRed = RED;
                    rotateLeft(root, grandparent);
                }
            }
        }

        (*root)->isRed = BLACK; // Garante que a raiz é preta 

    }
}

