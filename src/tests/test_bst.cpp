#include "bst.h"

using namespace BST;


void printMessage(std::string message, bool breakLine = 0, std::string color_code = "") {
    std::cout << "\033[" << color_code << "m" << message << "\033[m";
    if (breakLine) std::cout << std::endl;
}
bool contains(const std::vector<int>& vec, int value) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] == value) {
            return true;
        }
    }
    return false;
}


void tree_structure_tests() {
    try {
        printMessage("Testando inserção numa ÁRVORE NULA...", 0);
        insert(nullptr, "Pamonha", 3);
        printMessage(" CONCLUÍDO", 1, "92");
    } catch (int errorCode) {
        printMessage(" ERRO", 1, "91");
        printMessage(".......", 0);
        printMessage("A função não lida corretamente com a entrada de árvores nulas como parâmetro", 1);
    }

    try {
        BinaryTree* tree = create();
        printMessage("Testando inserção numa árvore com raíz NULA...", 0);
        insert(tree, "Almofada", 0);
        std::vector<int> docsIds = tree->root->documentIds;
        if (tree->root->word != "Almofada") {
            throw std::runtime_error("A palavra não foi inserida no nó da árvore");
        }
        if (!contains(docsIds, 0)) {
            throw std::runtime_error("O número do documento não foi inserido na árvore");
        }
        printMessage(" CONCLUÍDO", 1, "92");
    } catch (const std::runtime_error& err) {
        printMessage(" ERRO", 1, "91");
        printMessage(".......", 0);
        printMessage(err.what(), 1);
    }

    try {

    } catch (const std::runtime_error& err) {
    }
}


int main() {
    tree_structure_tests();

    return 0;
}
