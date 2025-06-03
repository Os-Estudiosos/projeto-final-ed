#include "tree_utils.h"

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


// Structs e Funções auxiliares, como Criar Nó, Computar altura, Busca, Exibir Árvore, etc

void printIndexHelper(Node* node, int& index) {
    // Se o ponteiro for nullptr não faz nada 
    if (!node) return;

    // Chamada recursiva para o filho à esquerda 
    printIndexHelper(node->left, index);

    // Imprime palavra e os IDs dos documentos 
    std::cout << index << ". " << node->word << ": ";
    for (size_t i = 0; i < node->documentIds.size(); ++i) {
        std::cout << node->documentIds[i];
        if (i != node->documentIds.size() - 1)
            std::cout << ", ";
    }
    std::cout << "\n";
 
    ++index;

    // Chamada recursiva para o filho à direita
    printIndexHelper(node->right, index);
}

void printIndex(BinaryTree* tree) {
    int index = 1;
    // Inicia chamando a função recursiva a partir do nó raiz 
    printIndexHelper(tree->root, index);
}

void printTreeHelper(Node* node, const std::string& prefix, bool isLeft) {
    // Se o nó for nulo não faz nada 
    if (!node) return;

    std::cout << prefix;

    // Se o nó não tem pai, então ele é a raiz e imprime apenas a palavra 
    if (!node->parent) {
        std::cout << node->word << "\n";
    } else {  // Se tem pai: "|__" para filho da esquerda; "\__" para filho à direita 
        std::cout << (isLeft ? "/__" : " \\__") << node->word << "\n";
    }

    // Nova string prefixo para os filhos do nó atual 
    std::string newPrefix = prefix;
    if (node->parent)
        // "|   " se o nó atual for da esquerda; "    " se for da direita 
        newPrefix += (isLeft ? "|   " : "    ");

    // Se o nó tiver pelo menos um filho, chama recursivamente nos filhos 
    if (node->left || node->right) {
        if (node->left)
            printTreeHelper(node->left, newPrefix, true);
        if (node->right)
            printTreeHelper(node->right, newPrefix, false);
    }
}

void printTree(BinaryTree* tree) {
    // Se a árvore estiver vazia retorna 
    if (!tree->root) return;
    // Inicia chamando a função recursiva a partir do nó raiz
    printTreeHelper(tree->root, "", false);
}

