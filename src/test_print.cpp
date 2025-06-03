
#include "modules/bst/bst.h"
#include "utils/tree_utils.h"

using namespace BST;

int main(int argc, char* argv[]) {

    BinaryTree* tree = create(); // criar a arvore
    
    insert(tree, "amor", 1);
    insert(tree, "roupa", 2);
    insert(tree, "matheus", 3);
    insert(tree, "algo", 1);
    insert(tree, "casa", 2);
    insert(tree, "voce", 3);
    insert(tree, "beleza", 1);
    insert(tree, "zebra", 2);
    insert(tree, "maquiagem", 3);

    std::cout << "== Indice Invertido ==\n";
    printIndex(tree);

    std::cout << "\n== Estrutura da Arvore ==\n";
    printTree(tree);

    return 0;
}
