#include "tree_utils.h"

void printIndex(BinaryTree *tree)
{
    // implementar
}
void printTree(BinaryTree *tree)
{
    // implementar
}

int computeHeight(Node *node) {
    if (node == nullptr) return 0;
    int left_height = computeHeight(node->left);
    int right_height = computeHeight(node->right);
    
    if (left_height >= right_height) {
        return left_height + 1;
    } else {
        return right_height + 1;
    }
}

int computeMinHeight(Node* node) {
    if (node == nullptr) return 0;
    if (node->left == nullptr && node->right == nullptr) return 1;

    if (node->left == nullptr) return computeMinHeight(node->right) + 1;
    if (node->right == nullptr) return computeMinHeight(node->left) + 1;

    int h_left = computeMinHeight(node->left);
    int h_right = computeMinHeight(node->right);

    if (h_left >= h_right) {
        return h_right + 1;
    } else {
        return h_left + 1;
    }
}

void deleteNode(Node *node)
{
    if (node == nullptr)                            // caso o nó a ser deletado seja nulo
    {
        return;                                     // nada acontece
    }
    else                                            // caso não seja nulo, então há algo a deletar
    {
        deleteNode(node->left);                     // então chamo a mesma função para deletar seus filhos
        deleteNode(node->right);                    // a mesma coisa acontece para os filhos dos filhos, e assim sucessivamente, até que, 
                                                    // primeiramente, as folhas sejam deletadas, e então seus pais, até a raiz  
        delete node;                                // deleta o nó atual
    }   
}