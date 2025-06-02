#include "tree_utils.h"

void printIndex(BinaryTree *tree)
{
    // implementar
}
void printTree(BinaryTree *tree)
{
    // implementar
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