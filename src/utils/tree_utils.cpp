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


void auxPrint(Node *aux, int *num) {
    std::cout<< *num << ". " << aux->word <<": ";
    std::string toPrint = "";

    for(long unsigned int i = 0; i < aux->documentIds.size(); i++){
        toPrint += std::to_string(aux->documentIds[i]) + ", ";
    }
    toPrint.erase(toPrint.size() - 2, 2);
    std::cout << toPrint << std::endl;
    *num += 1;

    if(aux->left != nullptr){
        auxPrint(aux->left, num);
    } 
    if(aux->right != nullptr){
        auxPrint(aux->right, num);
    }
}

void printIndex(BinaryTree* tree) {
    Node *aux = tree->root;
    int count = 1;
    
    if(aux != nullptr){
        auxPrint(aux, &count);
    }
}

void auxPrintTree(Node *aux, std::string space){
    if(aux->left != nullptr) {
        std::string folderRep = "├──";
        if(aux->right == nullptr){
            folderRep = "└──";
            std::cout << space << folderRep << aux->left->word << std::endl;
            auxPrintTree(aux->left,space + "   ");
        } else{
        std::cout << space << folderRep << aux->left->word << std::endl;
        auxPrintTree(aux->left,space + "│  ");
        }
    }
    if(aux->right != nullptr) {
        std::cout << space << "└──" << aux->right->word << std::endl;
        int n = space.size();
        std::string space2 = "";
        std::string tmp = "";
        int c = 0;
        for(int i = n; i > -1; i++){
            tmp = "";
            tmp += space[i];
            if(strcmp(tmp.c_str(), "│")){
                c = i;
                break;
            }
        }
        for(int i = 0; i < c ; i++){
            space2 += space[i];
        }
        for(int i = 0; i < n-c; i++){
            space2 += " ";
        }
        
        auxPrintTree(aux->right,space2 + "   ");
    }

}

void printTree(BinaryTree* tree) {
    Node *aux = tree->root;

    if(aux != nullptr){
        std::cout << aux->word << std::endl;
        auxPrintTree(aux, "");
    }
}

