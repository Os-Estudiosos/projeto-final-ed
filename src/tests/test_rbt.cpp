#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include "../modules/rbt/rbt.h" // Supondo que rbt.h está neste caminho

// =============== FUNÇÕES AUXILIARES DE TESTE ===============

/**
 * @brief Imprime uma mensagem no console com uma cor opcional.
 * @param message A mensagem a ser impressa.
 * @param breakLine Se deve adicionar uma nova linha no final.
 * @param color_code O código de cor ANSI.
 */
void printMessage(const std::string& message, bool breakLine = false, const std::string& color_code = "") {
    std::cout << (color_code.empty() ? "" : "\033[" + color_code + "m") << message << (color_code.empty() ? "" : "\033[m");
    if (breakLine) std::cout << std::endl;
}

/**
 * @brief Verifica se um valor está contido em um vetor de inteiros.
 * @param vec O vetor a ser verificado.
 * @param value O valor a ser procurado.
 * @return true se o valor for encontrado, false caso contrário.
 */
bool contains(const std::vector<int>& vec, int value) {
    for (int item : vec) {
        if (item == value) {
            return true;
        }
    }
    return false;
}

// =============== FUNÇÕES DE VALIDAÇÃO DA RBT ===============

// Protótipos das funções de validação para que possam chamar umas às outras.
bool isBstUtil(Node* node, Node*& prev);
int checkBlackHeight(Node* node);
bool checkRedProperty(Node* node);

/**
 * @brief Função principal para validar todas as propriedades da RBT.
 * @param tree A árvore a ser validada.
 * @return true se todas as propriedades da RBT forem válidas, false caso contrário.
 */
bool isRBT(BinaryTree* tree) {
    if (!tree || !tree->root) {
        return true; // Uma árvore vazia é uma RBT válida.
    }

    // 1. A raiz deve ser PRETA.
    if (tree->root->isRed != RBT::BLACK) {
        printMessage("  [FALHA] Propriedade da Raiz: A raiz não é PRETA.", 1, "91");
        return false;
    }

    // 2. A árvore deve manter as propriedades de uma Árvore de Busca Binária.
    Node* prev = nullptr;
    if (!isBstUtil(tree->root, prev)) {
        printMessage("  [FALHA] Propriedade da BST: A ordem dos nós está incorreta.", 1, "91");
        return false;
    }
    
    // 3. Não devem existir dois nós vermelhos adjacentes.
    if (!checkRedProperty(tree->root)) {
        printMessage("  [FALHA] Propriedade Vermelha: Existem dois nós vermelhos adjacentes.", 1, "91");
        return false;
    }

    // 4. Todos os caminhos da raiz até as folhas devem ter a mesma altura negra.
    if (checkBlackHeight(tree->root) == -1) {
        printMessage("  [FALHA] Propriedade da Altura Negra: Alturas negras inconsistentes.", 1, "91");
        return false;
    }

    return true;
}

/**
 * @brief Verifica se a árvore é uma Árvore de Busca Binária (BST) válida.
 * Usa um percurso in-order para verificar se as chaves estão ordenadas.
 * @param node O nó atual a ser verificado.
 * @param prev O nó visitado anteriormente no percurso.
 * @return true se a subárvore for uma BST válida.
 */
bool isBstUtil(Node* node, Node*& prev) {
    if (node == nullptr) {
        return true;
    }
    if (!isBstUtil(node->left, prev)) {
        return false;
    }
    if (prev != nullptr && node->word <= prev->word) {
        return false;
    }
    prev = node;
    return isBstUtil(node->right, prev);
}

/**
 * @brief Verifica recursivamente a propriedade da altura negra.
 * @param node O nó atual.
 * @return A altura negra da subárvore, ou -1 se a propriedade for violada.
 */
int checkBlackHeight(Node* node) {
    if (node == nullptr) {
        return 1; // Folhas (NIL) contam como 1 nó preto.
    }

    int leftBlackHeight = checkBlackHeight(node->left);
    if (leftBlackHeight == -1) return -1;

    int rightBlackHeight = checkBlackHeight(node->right);
    if (rightBlackHeight == -1) return -1;

    if (leftBlackHeight != rightBlackHeight) {
        return -1; // Violação da propriedade.
    }

    return leftBlackHeight + (node->isRed == RBT::BLACK ? 1 : 0);
}

/**
 * @brief Verifica recursivamente a propriedade vermelha (sem nós vermelhos adjacentes).
 * @param node O nó atual.
 * @return true se a propriedade for mantida, false caso contrário.
 */
bool checkRedProperty(Node* node) {
    if (node == nullptr) {
        return true;
    }
    // Se o nó atual é vermelho, seus filhos devem ser pretos.
    if (node->isRed == RBT::RED) {
        if ((node->left && node->left->isRed == RBT::RED) || (node->right && node->right->isRed == RBT::RED)) {
            return false;
        }
    }
    return checkRedProperty(node->left) && checkRedProperty(node->right);
}


// =============== SUÍTES DE TESTE ===============

void tree_structure_tests() {
    try {
        printMessage("Testando insercao numa ÁRVORE NULA...", 0);
        RBT::insert(nullptr, "Pamonha", 3);
        printMessage(" CONCLUiDO", 1, "92");
    } catch (const std::exception& e) {
        printMessage(" ERRO", 1, "91");
        printMessage(".......A funcao nao lida corretamente com arvores nulas como parametro.", 1);
    }

    try {
        BinaryTree* tree = RBT::create();
        printMessage("Testando insercao numa arvore com raiz NULA...", 0);
        RBT::insert(tree, "Almofada", 0);
        if (tree->root->word != "Almofada" || !contains(tree->root->documentIds, 0)) {
            RBT::destroy(tree);
            throw std::runtime_error("A palavra/documento nao foi inserida corretamente na raiz.");
        }
        RBT::destroy(tree);
        printMessage(" CONCLUIDO", 1, "92");
    } catch (const std::runtime_error& err) {
        printMessage(" ERRO", 1, "91");
        printMessage(std::string(".......") + err.what(), 1);
    }

    try {
        printMessage("Testando insercao e busca na arvore", 0);
        std::vector<std::string> words_to_insert = {"orangotango", "chimpanze", "leao", "girafa", "elefante"};
        std::vector<int> docsIds = {0, 1, 2, 3, 4};
        BinaryTree* tree = RBT::create();
        for (size_t i = 0; i < words_to_insert.size(); i++) {
            RBT::insert(tree, words_to_insert[i], docsIds[i]);
        }
        for (size_t j = 0; j < words_to_insert.size(); j++) {
            SearchResult result = RBT::search(tree, words_to_insert[j]);
            if (!result.found || !contains(result.documentIds, docsIds[j])) {
                RBT::destroy(tree);
                throw std::runtime_error("Os nos ou doc IDs nao estao sendo inseridos/retornados corretamente.");
            }
        }
        RBT::destroy(tree);
        printMessage(" CONCLUIDO", 1, "92");
    } catch (const std::runtime_error& err) {
        printMessage(" ERRO", 1, "91");
        printMessage(std::string(".......") + err.what(), 1);
    }
}

void tree_returns_tests() {
    try {
        printMessage("Testando insercao de palavra duplicada no mesmo documento", 0);
        BinaryTree* tree = RBT::create();
        RBT::insert(tree, "onomatopeia", 0);
        RBT::insert(tree, "digimon", 2);
        RBT::insert(tree, "onomatopeia", 0); // Inserção duplicada
        SearchResult result = RBT::search(tree, "onomatopeia");
        RBT::destroy(tree);
        if (result.documentIds.size() != 1) {
            throw std::runtime_error("A funcao esta inserindo o mesmo documento mais de uma vez.");
        }
        printMessage(" CONCLUIDO", 1, "92");
    } catch (const std::runtime_error& err) {
        printMessage(" ERRO", 1, "91");
        printMessage(std::string(".......") + err.what(), 1);
    }

    try {
        printMessage("Testando insercao de palavra duplicada em documento diferente", 0);
        BinaryTree* tree = RBT::create();
        RBT::insert(tree, "onomatopeia", 0);
        RBT::insert(tree, "onomatopeia", 1); // Mesma palavra, outro doc
        SearchResult result = RBT::search(tree, "onomatopeia");
        RBT::destroy(tree);
        if (result.documentIds.size() != 2 || !contains(result.documentIds, 0) || !contains(result.documentIds, 1)) {
            throw std::runtime_error("A funcao nao esta inserindo documentos novos em palavras existentes.");
        }
        printMessage(" CONCLUIDO", 1, "92");
    } catch (const std::runtime_error& err) {
        printMessage(" ERRO", 1, "91");
        printMessage(std::string(".......") + err.what(), 1);
    }

    try {
        printMessage("Testando insercao de palavras vazias", 0);
        BinaryTree* tree = RBT::create();
        RBT::insert(tree, "palavra", 0);
        RBT::insert(tree, "", 1); // Tenta inserir string vazia
        SearchResult result = RBT::search(tree, "");
        RBT::destroy(tree);
        if (result.found) {
            throw std::runtime_error("A funcao esta adicionando strings vazias.");
        }
        printMessage(" CONCLUIDO", 1, "92");
    } catch (const std::runtime_error& err) {
        printMessage(" ERRO", 1, "91");
        printMessage(std::string(".......") + err.what(), 1);
    }
}

void rbt_properties_tests() {
    // Caso de teste 1: Inserção em ordem crescente (causa múltiplas rotações à esquerda)
    try {
        printMessage("Testando propriedades RBT com insercao crescente (a, b, c, d, e)...", 0);
        BinaryTree* tree = RBT::create();
        std::vector<std::string> words = {"a", "b", "c", "d", "e"};
        for (int i = 0; i < words.size(); ++i) {
            RBT::insert(tree, words[i], i);
        }
        
        if (!isRBT(tree)) {
             RBT::destroy(tree);
             throw std::runtime_error("A arvore violou as propriedades da RBT.");
        }

        RBT::destroy(tree);
        printMessage(" CONCLUIDO", 1, "92");
    } catch (const std::runtime_error& err) {
        printMessage(" ERRO", 1, "91");
        printMessage(std::string(".......") + err.what(), 1);
    }

    // Caso de teste 2: Inserção em ordem decrescente (causa múltiplas rotações à direita)
    try {
        printMessage("Testando propriedades RBT com insercao decrescente (e, d, c, b, a)...", 0);
        BinaryTree* tree = RBT::create();
        std::vector<std::string> words = {"e", "d", "c", "b", "a"};
        for (int i = 0; i < words.size(); ++i) {
            RBT::insert(tree, words[i], i);
        }

        if (!isRBT(tree)) {
             RBT::destroy(tree);
             throw std::runtime_error("A arvore violou as propriedades da RBT.");
        }
        
        RBT::destroy(tree);
        printMessage(" CONCLUIDO", 1, "92");
    } catch (const std::runtime_error& err) {
        printMessage(" ERRO", 1, "91");
        printMessage(std::string(".......") + err.what(), 1);
    }

    // Caso de teste 3: Inserção que causa rotação dupla (Direita-Esquerda)
    try {
        printMessage("Testando propriedades RBT com rotacao dupla (Dir-Esq)...", 0);
        BinaryTree* tree = RBT::create();
        RBT::insert(tree, "c", 0);
        RBT::insert(tree, "a", 1);
        RBT::insert(tree, "b", 2); // Causa rotação dupla

        if (!isRBT(tree) || tree->root->word != "b") {
             RBT::destroy(tree);
             throw std::runtime_error("A arvore falhou na rotacao dupla ou violou propriedades.");
        }

        RBT::destroy(tree);
        printMessage(" CONCLUIDO", 1, "92");
    } catch (const std::runtime_error& err) {
        printMessage(" ERRO", 1, "91");
        printMessage(std::string(".......") + err.what(), 1);
    }
    
    // Caso de teste 4: Inserção que causa recoloração (tio é vermelho)
    try {
        printMessage("Testando propriedades RBT com recoloracao...", 0);
        BinaryTree* tree = RBT::create();
        RBT::insert(tree, "d", 0); // Raiz, preta
        RBT::insert(tree, "b", 1); // Filho esq, vermelho
        RBT::insert(tree, "e", 2); // Filho dir, vermelho
        RBT::insert(tree, "a", 3); // Causa recoloração de b e e para preto
        
        // Após inserir 'a', 'b' e 'e' devem se tornar pretos e 'd' (raiz) permanece preto.
        if (!isRBT(tree) || tree->root->left->isRed != RBT::BLACK || tree->root->right->isRed != RBT::BLACK) {
            RBT::destroy(tree);
            throw std::runtime_error("A arvore falhou na recoloracao ou violou propriedades.");
        }
        
        RBT::destroy(tree);
        printMessage(" CONCLUIDO", 1, "92");
    } catch (const std::runtime_error& err) {
        printMessage(" ERRO", 1, "91");
        printMessage(std::string(".......") + err.what(), 1);
    }
}


// =============== FUNÇÃO PRINCIPAL ===============

int main() {
    std::cout << "======================= TESTES ESTRUTURAIS DA ARVORE =======================" << std::endl;
    tree_structure_tests();

    std::cout << "\n======================= TESTANDO O RETORNO DA ARVORE =======================" << std::endl;
    tree_returns_tests();
    
    std::cout << "\n====================== TESTANDO PROPRIEDADES DA RBT ======================" << std::endl;
    rbt_properties_tests();

    std::cout << "\nTodos os testes foram concluídos." << std::endl;

    return 0;
}
