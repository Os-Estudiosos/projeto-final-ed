#include "../modules/bst/bst.h"
#include "../utils/tree_utils.h"

void printMessage(std::string message, bool breakLine = 0, std::string color_code = "") {
    std::cout << "\033[" << color_code << "m" << message << "\033[m";
    if (breakLine) std::cout << std::endl;
}

void tree_structure_tests() {
    try {
        printMessage("Testando insercao numa ÁRVORE NULA...", 0);
        BST::insert(nullptr, "Pamonha", 3);
        printMessage(" CONCLUiDO", 1, "92");
    } catch (int errorCode) {
        printMessage(" ERRO", 1, "91");
        printMessage(".......", 0);
        printMessage("A funcao não lida corretamente com a entrada de arvores nulas como parametro", 1);
    }

    try {
        BinaryTree* tree = BST::create();
        printMessage("Testando insercao numa arvore com raiz NULA...", 0);
        BST::insert(tree, "Almofada", 0);
        std::vector<int> docsIds = tree->root->documentIds;
        if (tree->root->word != "Almofada") {
            BST::destroy(tree);
            throw std::runtime_error("A palavra nao foi inserida no noh da árvore");
        }
        BST::destroy(tree);
        if (!contains(docsIds, 0)) {
            throw std::runtime_error("O numero do documento nao foi inserido na arvore");
        }
        printMessage(" CONCLUIDO", 1, "92");
    } catch (const std::runtime_error& err) {
        printMessage(" ERRO", 1, "91");
        printMessage(".......", 0);
        printMessage(err.what(), 1);
    }

    try {
        printMessage("Testando insercao e busca na arvore", 0);
        std::vector<std::string> words_to_insert = {"orangotango", "chimpanze", "leao", "girafa", "elefante"};
        std::vector<int> docsIds = {0, 1, 2, 3, 4};

        BinaryTree* tree = BST::create();

        for (long unsigned int i = 0; i < words_to_insert.size(); i++) {
            BST::insert(tree, words_to_insert[i], docsIds[i]);
        }

        for (long unsigned int j = 0; j < words_to_insert.size(); j++) {
            SearchResult result = search(tree, words_to_insert[j]);
            if (!result.found) {
                BST::destroy(tree);
                throw std::runtime_error("Os nos nao estao sendo inseridos corretamente");
            }
            if (!contains(result.documentIds, docsIds[j])) {
                BST::destroy(tree);
                throw std::runtime_error("Os numeros dos documentos, ou nao estao sendo inseridos, ou nao estao sendo retornados pelo search");
            }
        }
        BST::destroy(tree);
        printMessage(" CONCLUIDO", 1, "92");
    } catch (const std::runtime_error& err) {
        printMessage(" ERRO", 1, "91");
        printMessage(".......", 0);
        printMessage(err.what(), 1);
    }

    try {
        printMessage("Testando insercao em arvore desbalanceada", 0);
        std::vector<std::string> words_to_insert = {"a", "b", "c"};
        std::vector<int> docsIds = {0, 1, 2};

        BinaryTree* tree = BST::create();

        BST::insert(tree, words_to_insert[0], docsIds[0]);
        BST::insert(tree, words_to_insert[1], docsIds[1]);
        BST::insert(tree, words_to_insert[2], docsIds[2]);

        if (!(
            tree->root->word == "a" && tree->root->right->word == "b" && tree->root->right->right->word == "c"
        )) {
            BST::destroy(tree);
            throw std::runtime_error("Nao esta inserindo da forma correta");
        }

        BST::destroy(tree);
        printMessage(" CONCLUIDO", 1, "92");
    } catch (const std::runtime_error& err) {
        printMessage(" ERRO", 1, "91");
        printMessage(".......", 0);
        printMessage(err.what(), 1);
    }
}

void tree_returns_tests() {
    try {
        BinaryTree* tree = BST::create();
        BST::insert(tree, "onomatopeia", 0);
        BST::insert(tree, "cachorro", 2);
        BST::insert(tree, "digimon", 2);
        BST::insert(tree, "panorama", 3);

        printMessage("Testando insercao de palavra duplicada no mesmo documento", 0);
        BST::insert(tree, "onomatopeia", 0);
        BST::insert(tree, "digimon", 2);

        SearchResult result1 = search(tree, "onomatopeia");
        SearchResult result2 = search(tree, "digimon");

        BST::destroy(tree);
        if (result1.documentIds.size() != 1 || result2.documentIds.size() != 1) {
            throw std::runtime_error("A funcao está inserindo o mesmo documento mais de uma vez");
        }

        printMessage(" CONCLUIDO", 1, "92");
    } catch (const std::runtime_error& err) {
        printMessage(" ERRO", 1, "91");
        printMessage(".......", 0);
        printMessage(err.what(), 1);
    }

    try {
        printMessage("Testando insercao de palavra duplicada em documento diferente", 0);

        BinaryTree* tree = BST::create();
        BST::insert(tree, "onomatopeia", 0);
        BST::insert(tree, "cachorro", 2);
        BST::insert(tree, "digimon", 2);
        BST::insert(tree, "panorama", 3);

        BST::insert(tree, "onomatopeia", 1);
        BST::insert(tree, "panorama", 5);

        SearchResult result1 = search(tree, "onomatopeia");
        SearchResult result2 = search(tree, "panorama");

        BST::destroy(tree);
        if (!contains(result1.documentIds, 1) || !contains(result2.documentIds, 5)) {
            throw std::runtime_error("A funcao nao esta inserindo documentos novos em novas aparicoes de palavras");
        }

        printMessage(" CONCLUIDO", 1, "92");
    } catch (const std::runtime_error& err) {
        printMessage(" ERRO", 1, "91");
        printMessage(".......", 0);
        printMessage(err.what(), 1);
    }

    try {
        printMessage("Testando insercao de palavras vazias", 0);

        BinaryTree* tree = BST::create();
        BST::insert(tree, "onomatopeia", 0);
        BST::insert(tree, "cachorro", 2);
        BST::insert(tree, "digimon", 2);
        BST::insert(tree, "panorama", 3);

        BST::insert(tree, "", 0);

        SearchResult result = search(tree, "");

        BST::destroy(tree);
        if (result.found) {
            throw std::runtime_error("A funcao esta adicionando strings vazias");
        }

        printMessage(" CONCLUIDO", 1, "92");
    } catch (const std::runtime_error& err) {
        printMessage(" ERRO", 1, "91");
        printMessage(".......", 0);
        printMessage(err.what(), 1);
    }
}

int main() {
    std::cout << "=========================== TESTES ESTRUTURAIS DA ARVORE ===========================" << std::endl;
    tree_structure_tests();

    std::cout << "=========================== TESTANDO O RETORNO DA ARVORE ===========================" << std::endl;
    tree_returns_tests();

    return 0;
}
