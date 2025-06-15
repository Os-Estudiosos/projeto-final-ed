// Inclusão dos cabeçalhos necessários para usar a árvore binária de busca (BST)
#include "../modules/bst/bst.h"
#include "../utils/tree_utils.h"

// Função utilitária para imprimir mensagens formatadas com cores e quebra de linha opcional
void printMessage(std::string message, bool breakLine = 0, std::string color_code = "") {
    std::cout << "\033[" << color_code << "m" << message << "\033[m";  // ANSI escape code para cor
    if (breakLine) std::cout << std::endl;
}

// Função para testar o comportamento estrutural da árvore
void tree_structure_tests() {
    try {
        // Teste de inserção em uma árvore nula (ponteiro nullptr)
        printMessage("Testando insercao numa ÁRVORE NULA...", 0);
        BST::insert(nullptr, "Pamonha", 3);  // Espera-se que isso lance exceção ou erro
        printMessage(" CONCLUiDO", 1, "92"); // Verde
    } catch (int errorCode) {
        printMessage(" ERRO", 1, "91"); // Vermelho
        printMessage(".......", 0);
        printMessage("A funcao não lida corretamente com a entrada de arvores nulas como parametro", 1);
    }

    try {
        // Teste de inserção em uma árvore recém-criada com raiz nula
        BinaryTree* tree = BST::create();
        printMessage("Testando insercao numa arvore com raiz NULA...", 0);
        BST::insert(tree, "Almofada", 0);

        // Verifica se a palavra foi inserida corretamente como raiz
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
        // Teste de múltiplas inserções e buscas
        printMessage("Testando insercao e busca na arvore", 0);
        std::vector<std::string> words_to_insert = {"orangotango", "chimpanze", "leao", "girafa", "elefante"};
        std::vector<int> docsIds = {0, 1, 2, 3, 4};

        BinaryTree* tree = BST::create();

        // Inserção das palavras na árvore
        for (size_t i = 0; i < words_to_insert.size(); i++) {
            BST::insert(tree, words_to_insert[i], docsIds[i]);
        }

        // Verificação por busca se todas foram corretamente inseridas
        for (size_t j = 0; j < words_to_insert.size(); j++) {
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
        // Teste de árvore desbalanceada (inserção em ordem crescente)
        printMessage("Testando insercao em arvore desbalanceada", 0);
        std::vector<std::string> words_to_insert = {"a", "b", "c"};
        std::vector<int> docsIds = {0, 1, 2};

        BinaryTree* tree = BST::create();
        for (int i = 0; i < 3; i++) {
            BST::insert(tree, words_to_insert[i], docsIds[i]);
        }

        // Verifica a estrutura da árvore (espera-se que seja linear: a -> b -> c)
        if (!(tree->root->word == "a" && tree->root->right->word == "b" && tree->root->right->right->word == "c")) {
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

// Testa o comportamento do retorno da árvore em inserções específicas
void tree_returns_tests() {
    try {
        // Testa inserção duplicada da mesma palavra no mesmo documento
        BinaryTree* tree = BST::create();
        BST::insert(tree, "onomatopeia", 0);
        BST::insert(tree, "cachorro", 2);
        BST::insert(tree, "digimon", 2);
        BST::insert(tree, "panorama", 3);

        printMessage("Testando insercao de palavra duplicada no mesmo documento", 0);
        BST::insert(tree, "onomatopeia", 0);  // Deve ignorar essa duplicação
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
        // Testa inserção de mesma palavra em documentos diferentes
        printMessage("Testando insercao de palavra duplicada em documento diferente", 0);

        BinaryTree* tree = BST::create();
        BST::insert(tree, "onomatopeia", 0);
        BST::insert(tree, "cachorro", 2);
        BST::insert(tree, "digimon", 2);
        BST::insert(tree, "panorama", 3);

        BST::insert(tree, "onomatopeia", 1);  // Documento novo
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
        // Teste de inserção de palavra vazia
        printMessage("Testando insercao de palavras vazias", 0);

        BinaryTree* tree = BST::create();
        BST::insert(tree, "onomatopeia", 0);
        BST::insert(tree, "cachorro", 2);
        BST::insert(tree, "digimon", 2);
        BST::insert(tree, "panorama", 3);

        BST::insert(tree, "", 0);  // Inserção inválida

        SearchResult result = search(tree, "");  // Não deveria encontrar nada

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

// Função principal que executa todos os testes
int main() {
    std::cout << "=========================== TESTES ESTRUTURAIS DA ARVORE ===========================" << std::endl;
    tree_structure_tests();

    std::cout << "=========================== TESTANDO O RETORNO DA ARVORE ===========================" << std::endl;
    tree_returns_tests();

    return 0;
}
