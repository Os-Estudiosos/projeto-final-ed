// Inclusão dos cabeçalhos com a implementação da AVL e utilitários da árvore
#include "../modules/avl/avl.h"
#include "../utils/tree_utils.h"

// Função auxiliar para imprimir mensagens formatadas no terminal com opção de cor e quebra de linha
void printMessage(std::string message, bool breakLine = 0, std::string color_code = "") {
    std::cout << "\033[" << color_code << "m" << message << "\033[m";
    if (breakLine) std::cout << std::endl;
}

// Função que realiza uma série de testes estruturais na árvore AVL
void tree_structure_tests() {
    try {
        // Teste: inserção em ponteiro de árvore nulo (nullptr)
        printMessage("Testando insercao numa ARVORE NULA...", 0);
        AVL::insert(nullptr, "pamonha", 3);
        printMessage(" CONCLUiDO", 1, "92"); // verde (código 92)
    } catch (int errorCode) {
        // Esperado: erro ao tentar inserir em nullptr
        printMessage(" ERRO", 1, "91"); // vermelho
        printMessage(".......", 0);
        printMessage("A funcao nao lida corretamente com a entrada de arvores nulas como parametro", 1);
    }

    try {
        // Teste: inserção na raiz nula
        BinaryTree* tree = AVL::create();
        printMessage("Testando insercao numa arvore com raiz NULA...", 0);
        AVL::insert(tree, "almofada", 0);
        std::vector<int> docsIds = tree->root->documentIds;
        if (tree->root->word != "almofada") {
            AVL::destroy(tree);
            throw std::runtime_error("A palavra nao foi inserida no no da arvore");
        }
        AVL::destroy(tree);
        if (!contains(docsIds, 0)) {
            throw std::runtime_error("O numero do documento nao foi inserido na arvore");
        }
        printMessage(" CONCLUIDO", 1, "92");
    } catch (const std::runtime_error& err) {
        // Caso ocorra erro nos testes acima
        printMessage(" ERRO", 1, "91");
        printMessage(".......", 0);
        printMessage(err.what(), 1);
    }

    try {
        // Teste: inserção e busca múltipla
        printMessage("Testando insercao e busca na arvore", 0);
        std::vector<std::string> words_to_insert = {"orangotango", "chimpanze", "leao", "girafa", "elefante"};
        std::vector<int> docsIds = {0, 1, 2, 3, 4};
        BinaryTree* tree = AVL::create();

        // Inserindo palavras
        for (long unsigned int i = 0; i < words_to_insert.size(); i++) {
            AVL::insert(tree, words_to_insert[i], docsIds[i]);
        }

        // Verificando se todas foram inseridas corretamente
        for (long unsigned int j = 0; j < words_to_insert.size(); j++) {
            SearchResult result = search(tree, words_to_insert[j]);
            if (!result.found) {
                AVL::destroy(tree);
                throw std::runtime_error("Os nos nao estao sendo inseridos corretamente");
            }
            if (!contains(result.documentIds, docsIds[j])) {
                AVL::destroy(tree);
                throw std::runtime_error("Os numeros dos documentos, ou nao estao sendo inseridos, ou nao estao sendo retornados pelo search");
            }
        }
        AVL::destroy(tree);
        printMessage(" CONCLUIDO", 1, "92");
    } catch (const std::runtime_error& err) {
        printMessage(" ERRO", 1, "91");
        printMessage(".......", 0);
        printMessage(err.what(), 1);
    }
}

// Função que testa os retornos da árvore, como tratamento de duplicatas e strings vazias
void tree_returns_tests() {
    try {
        // Teste: inserção de palavras duplicadas no mesmo documento
        BinaryTree* tree = AVL::create();
        AVL::insert(tree, "onomatopeia", 0);
        AVL::insert(tree, "cachorro", 2);
        AVL::insert(tree, "digimon", 2);
        AVL::insert(tree, "panorama", 3);
        printMessage("Testando insercao de palavra duplicada no mesmo documento", 0);
        AVL::insert(tree, "onomatopeia", 0);
        AVL::insert(tree, "digimon", 2);
        SearchResult result1 = search(tree, "onomatopeia");
        SearchResult result2 = search(tree, "digimon");
        AVL::destroy(tree);
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
        // Teste: inserção de palavras duplicadas em documentos diferentes
        printMessage("Testando insercao de palavra duplicada em documento diferente", 0);
        BinaryTree* tree = AVL::create();
        AVL::insert(tree, "onomatopeia", 0);
        AVL::insert(tree, "cachorro", 2);
        AVL::insert(tree, "digimon", 2);
        AVL::insert(tree, "panorama", 3);
        AVL::insert(tree, "onomatopeia", 1);
        AVL::insert(tree, "panorama", 5);
        SearchResult result1 = search(tree, "onomatopeia");
        SearchResult result2 = search(tree, "panorama");
        AVL::destroy(tree);
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
        // Teste: inserção de string vazia
        printMessage("Testando insercao de palavras vazias", 0);
        BinaryTree* tree = AVL::create();
        AVL::insert(tree, "onomatopeia", 0);
        AVL::insert(tree, "cachorro", 2);
        AVL::insert(tree, "digimon", 2);
        AVL::insert(tree, "panorama", 3);
        AVL::insert(tree, "", 0); // string vazia
        SearchResult result = search(tree, "");
        AVL::destroy(tree);
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

void tree_avl_propreties()
{
    // Testes de balanceamento da AVL nos quatro casos clássicos

        try {
            // Caso RR (rotação simples à esquerda)
            printMessage("Testando insercao em arvore desbalanceada (caso RR)", 0);
            BinaryTree* tree = AVL::create();
            AVL::insert(tree, "a", 0);
            AVL::insert(tree, "b", 1);
            AVL::insert(tree, "c", 2);
            if (!(tree->root->word == "b" && tree->root->left->word == "a" && tree->root->right->word == "c" &&
                tree->root->height == 2 && tree->root->left->height == 1 && tree->root->right->height == 1)) {
                AVL::destroy(tree);
                throw std::runtime_error("A arvore nao esta sendo balanceada corretamente para o caso RR");
            }
            AVL::destroy(tree);
            printMessage(" CONCLUIDO", 1, "92");
        } catch (const std::runtime_error& err) {
            printMessage(" ERRO", 1, "91");
            printMessage(".......", 0);
            printMessage(err.what(), 1);
        }

        try {
            // Caso LL (rotação simples à direita)
            printMessage("Testando insercao em arvore desbalanceada (caso LL)", 0);
            BinaryTree* tree = AVL::create();
            AVL::insert(tree, "c", 0);
            AVL::insert(tree, "b", 1);
            AVL::insert(tree, "a", 2);
            if (!(tree->root->word == "b" && tree->root->left->word == "a" && tree->root->right->word == "c" &&
                tree->root->height == 2 && tree->root->left->height == 1 && tree->root->right->height == 1)) {
                AVL::destroy(tree);
                throw std::runtime_error("A arvore nao esta sendo balanceada corretamente para o caso LL");
            }
            AVL::destroy(tree);
            printMessage(" CONCLUIDO", 1, "92");
        } catch (const std::runtime_error& err) {
            printMessage(" ERRO", 1, "91");
            printMessage(".......", 0);
            printMessage(err.what(), 1);
        }

        try {
            // Caso LR (rotação dupla esquerda-direita)
            printMessage("Testando insercao em arvore desbalanceada (caso LR)", 0);
            BinaryTree* tree = AVL::create();
            AVL::insert(tree, "c", 0);
            AVL::insert(tree, "a", 1);
            AVL::insert(tree, "b", 2);
            if (!(tree->root->word == "b" && tree->root->left->word == "a" && tree->root->right->word == "c" &&
                tree->root->height == 2 && tree->root->left->height == 1 && tree->root->right->height == 1)) {
                AVL::destroy(tree);
                throw std::runtime_error("A arvore nao esta sendo balanceada corretamente para o caso LR");
            }
            AVL::destroy(tree);
            printMessage(" CONCLUIDO", 1, "92");
        } catch (const std::runtime_error& err) {
            printMessage(" ERRO", 1, "91");
            printMessage(".......", 0);
            printMessage(err.what(), 1);
        }

        try {
            // Caso RL (rotação dupla direita-esquerda)
            printMessage("Testando insercao em arvore desbalanceada (caso RL)", 0);
            BinaryTree* tree = AVL::create();
            AVL::insert(tree, "a", 1);
            AVL::insert(tree, "c", 1);
            AVL::insert(tree, "b", 2);
            if (!(tree->root->word == "b" && tree->root->left->word == "a" && tree->root->right->word == "c" &&
                tree->root->height == 2 && tree->root->left->height == 1 && tree->root->right->height == 1)) {
                AVL::destroy(tree);
                throw std::runtime_error("A arvore nao esta sendo balanceada corretamente para o caso RL");
            }
            AVL::destroy(tree);
            printMessage(" CONCLUIDO", 1, "92");
        } catch (const std::runtime_error& err) {
            printMessage(" ERRO", 1, "91");
            printMessage(".......", 0);
            printMessage(err.what(), 1);
        }
}

// Função principal do programa que executa todos os testes
int main() {
    std::cout << "=========================== TESTES ESTRUTURAIS DA ARVORE ===========================" << std::endl;
    tree_structure_tests();

    std::cout << "=========================== TESTANDO O RETORNO DA ARVORE ===========================" << std::endl;
    tree_returns_tests();

    std::cout << "=========================== TESTANDO PROPRIEDADES DA AVL ===========================" << std::endl;
    tree_avl_propreties();

    return 0;
}
