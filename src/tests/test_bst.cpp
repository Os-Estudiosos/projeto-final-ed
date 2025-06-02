#include "../modules/bst/bst.h"

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
            destroy(tree);
            throw std::runtime_error("A palavra não foi inserida no nó da árvore");
        }
        destroy(tree);
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
        printMessage("Testando inserção e busca na árvore", 0);
        std::vector<std::string> words_to_insert = {"orangotango", "chimpanze", "leao", "girafa", "elefante"};
        std::vector<int> docsIds = {0, 1, 2, 3, 4};

        BinaryTree* tree = create();

        for (int i = 0; i < words_to_insert.size(); i++) {
            insert(tree, words_to_insert[i], docsIds[i]);
        }

        for (int j = 0; j < words_to_insert.size(); j++) {
            SearchResult result = search(tree, words_to_insert[j]);
            if (!result.found) {
                destroy(tree);
                throw std::runtime_error("Os nós não estão sendo inseridos corretamente");
            }
            if (!contains(result.documentIds, docsIds[j])) {
                destroy(tree);
                throw std::runtime_error("Os números dos documentos, ou não estão sendo inseridos, ou não estão sendo retornados pelo search");
            }
        }
        destroy(tree);
        printMessage(" CONCLUÍDO", 1, "92");
    } catch (const std::runtime_error& err) {
        printMessage(" ERRO", 1, "91");
        printMessage(".......", 0);
        printMessage(err.what(), 1);
    }

    try {
        printMessage("Testando inserção em árvore desbalanceada", 0);
        std::vector<std::string> words_to_insert = {"a", "b", "c"};
        std::vector<int> docsIds = {0, 1, 2};

        BinaryTree* tree = create();

        insert(tree, words_to_insert[0], docsIds[0]);
        insert(tree, words_to_insert[1], docsIds[1]);
        insert(tree, words_to_insert[2], docsIds[2]);

        if (!(
            tree->root->word == "a" && tree->root->right->word == "b" && tree->root->right->right->word == "c"
        )) {
            destroy(tree);
            throw std::runtime_error("Não está inserindo da forma correta");
        }

        destroy(tree);
        printMessage(" CONCLUÍDO", 1, "92");
    } catch (const std::runtime_error& err) {
        printMessage(" ERRO", 1, "91");
        printMessage(".......", 0);
        printMessage(err.what(), 1);
    }
}


void tree_returns_tests() {
    try {
        BinaryTree* tree = create();
        insert(tree, "onomatopeia", 0);
        insert(tree, "cachorro", 2);
        insert(tree, "digimon", 2);
        insert(tree, "panorama", 3);

        printMessage("Testando inserção de palavra duplicada no mesmo documento", 0);
        insert(tree, "onomatopeia", 0);
        insert(tree, "digimon", 2);

        SearchResult result1 = search(tree, "onomatopeia");
        SearchResult result2 = search(tree, "digimon");

        destroy(tree);
        if (result1.documentIds.size() != 1 || result2.documentIds.size() != 1) {
            throw std::runtime_error("A função está inserindo o mesmo documento mais de uma vez");
        }

        printMessage(" CONCLUÍDO", 1, "92");
    } catch (const std::runtime_error& err) {
        printMessage(" ERRO", 1, "91");
        printMessage(".......", 0);
        printMessage(err.what(), 1);
    }

    try {
        printMessage("Testando inserção de palavra duplicada em documento diferente", 0);

        BinaryTree* tree = create();
        insert(tree, "onomatopeia", 0);
        insert(tree, "cachorro", 2);
        insert(tree, "digimon", 2);
        insert(tree, "panorama", 3);

        insert(tree, "onomatopeia", 1);
        insert(tree, "panorama", 5);

        SearchResult result1 = search(tree, "onomatopeia");
        SearchResult result2 = search(tree, "panorama");

        destroy(tree);
        if (!contains(result1.documentIds, 1) || !contains(result2.documentIds, 5)) {
            throw std::runtime_error("A função não está inserindo documentos novos em novas aparições de palavras");
        }

        printMessage(" CONCLUÍDO", 1, "92");
    } catch (const std::runtime_error& err) {
        printMessage(" ERRO", 1, "91");
        printMessage(".......", 0);
        printMessage(err.what(), 1);
    }

    try {
        printMessage("Testando inserção de palavras vazias", 0);

        BinaryTree* tree = create();
        insert(tree, "onomatopeia", 0);
        insert(tree, "cachorro", 2);
        insert(tree, "digimon", 2);
        insert(tree, "panorama", 3);

        insert(tree, "", 0);

        SearchResult result = search(tree, "");

        destroy(tree);
        if (result.found) {
            throw std::runtime_error("A função está adicionando strings vazias");
        }

        printMessage(" CONCLUÍDO", 1, "92");
    } catch (const std::runtime_error& err) {
        printMessage(" ERRO", 1, "91");
        printMessage(".......", 0);
        printMessage(err.what(), 1);
    }
}


int main() {
    std::cout << "=========================== TESTES ESTRUTURAIS DA ÁRVORE ===========================" << std::endl;
    tree_structure_tests();

    std::cout << "=========================== TESTANDO O RETORNO DA ÁRVORE ===========================" << std::endl;
    tree_returns_tests();

    return 0;
}
