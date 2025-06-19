#include "../modules/rbt/rbt.h" 
#include "../utils/tree_utils.h"
#include "../utils/utils.h"

bool isBstUtil(Node* node, Node*& prev)
{
    if (node == nullptr) return true;
    
    if (!isBstUtil(node->left, prev)) return false;
    
    if (prev != nullptr && node->word <= prev->word) return false;
    
    prev = node;
    return isBstUtil(node->right, prev);
}

int checkBlackHeight(Node* node) 
{
    if (node == nullptr) return 1;
    
    int left = checkBlackHeight(node->left);
    if (left == -1) return -1;
    
    int right = checkBlackHeight(node->right);
    if (right == -1) return -1;
    
    if (left != right) return -1;
    
    return left + (node->isRed == RBT::BLACK ? 1 : 0);
}

bool checkRedProperty(Node* node)
{
    if (!node) return true;
    
    if (node->isRed == RBT::RED)
    {
        if ((node->left && node->left->isRed == RBT::RED) ||
        (node->right && node->right->isRed == RBT::RED))
        {
            return false;
        }
    }
    
    return checkRedProperty(node->left) && checkRedProperty(node->right);
}

bool isRBT(BinaryTree* tree)
{
    if (!tree || !tree->root) return true; // Árvore vazia é válida por definição

    // Propriedade 1: Raiz deve ser preta
    if (tree->root->isRed != RBT::BLACK)
    {
        printMessage("  [FALHA] Propriedade da Raiz: A raiz nao e PRETA.", 1, "91");
        return false;
    }

    // Propriedade 2: Deve respeitar a ordenação BST
    Node* prev = nullptr;
    if (!isBstUtil(tree->root, prev))
    {
        printMessage("  [FALHA] Propriedade da BST: A ordem dos nós esta incorreta.", 1, "91");
        return false;
    }

    // Propriedade 3: Não pode haver dois nós vermelhos consecutivos
    if (!checkRedProperty(tree->root))
    {
        printMessage("  [FALHA] Propriedade Vermelha: Existem dois nos vermelhos adjacentes.", 1, "91");
        return false;
    }

    // Propriedade 4: Caminhos da raiz às folhas devem ter mesma altura negra
    if (checkBlackHeight(tree->root) == -1)
    {
        printMessage("  [FALHA] Propriedade da Altura Negra: Alturas negras inconsistentes.", 1, "91");
        return false;
    }

    return true;
}

void treeStructureTests()
{
    try
    {
        printMessage("Testando insercao numa ARVORE NULA...", 0);
        RBT::insert(nullptr, "Pamonha", 3);
        printMessage(" CONCLUiDO", 1, "92");
    } catch (const std::exception& e)
    {
        printMessage(" ERRO", 1, "91");
        printMessage(".......A funcao nao lida corretamente com arvores nulas como parametro.", 1);
    }

    try
    {
        BinaryTree* tree = RBT::create();
        printMessage("Testando insercao numa arvore com raiz NULA...", 0);
        RBT::insert(tree, "Almofada", 0);
        if (tree->root->word != "Almofada" || !contains(tree->root->documentIds, 0))
        {
            RBT::destroy(tree);
            throw std::runtime_error("A palavra/documento nao foi inserida corretamente na raiz.");
        }
        RBT::destroy(tree);
        printMessage(" CONCLUIDO", 1, "92");
    } catch (const std::runtime_error& err) 
    {
        printMessage(" ERRO", 1, "91");
        printMessage(std::string(".......") + err.what(), 1);
    }

    try
    {
        printMessage("Testando insercao e busca na arvore", 0);
        std::vector<std::string> words = {"orangotango", "chimpanze", "leao", "girafa", "elefante"};
        std::vector<int> docs = {0, 1, 2, 3, 4};
        BinaryTree* tree = RBT::create();
        for (size_t i = 0; i < words.size(); i++) 
        {
            RBT::insert(tree, words[i], docs[i]);
        }
        for (size_t j = 0; j < words.size(); j++)
        {
            SearchResult result = search(tree, words[j]);
            if (!result.found || !contains(result.documentIds, docs[j]))
            {
                RBT::destroy(tree);
                throw std::runtime_error("Os nos ou doc IDs nao estao sendo inseridos/retornados corretamente.");
            }
        }
        RBT::destroy(tree);
        printMessage(" CONCLUIDO", 1, "92");
    } catch (const std::runtime_error& err)
    {
        printMessage(" ERRO", 1, "91");
        printMessage(std::string(".......") + err.what(), 1);
    }
}

void treeReturnsTests()
{
    try
    {
        printMessage("Testando insercao de palavra duplicada no mesmo documento", 0);
        BinaryTree* tree = RBT::create();
        RBT::insert(tree, "onomatopeia", 0);
        RBT::insert(tree, "digimon", 2);
        RBT::insert(tree, "onomatopeia", 0);
        SearchResult result = search(tree, "onomatopeia");
        RBT::destroy(tree);
        if (result.documentIds.size() != 1)
        {
            throw std::runtime_error("A funcao esta inserindo o mesmo documento mais de uma vez.");
        }
        printMessage(" CONCLUIDO", 1, "92");
    } catch (const std::runtime_error& err)
    {
        printMessage(" ERRO", 1, "91");
        printMessage(std::string(".......") + err.what(), 1);
    }

    try
    {
        printMessage("Testando insercao de palavra duplicada em documento diferente", 0);
        BinaryTree* tree = RBT::create();
        RBT::insert(tree, "onomatopeia", 0);
        RBT::insert(tree, "onomatopeia", 1);
        SearchResult result = search(tree, "onomatopeia");
        RBT::destroy(tree);
        if (result.documentIds.size() != 2 || !contains(result.documentIds, 0) || !contains(result.documentIds, 1))
        {
            throw std::runtime_error("A funcao nao esta inserindo documentos novos em palavras existentes.");
        }
        printMessage(" CONCLUIDO", 1, "92");
    } catch (const std::runtime_error& err)
    {
        printMessage(" ERRO", 1, "91");
        printMessage(std::string(".......") + err.what(), 1);
    }

    try
    {
        printMessage("Testando insercao de palavras vazias", 0);
        BinaryTree* tree = RBT::create();
        RBT::insert(tree, "palavra", 0);
        RBT::insert(tree, "", 1);
        SearchResult result = search(tree, "");
        RBT::destroy(tree);
        if (result.found)
        {
            throw std::runtime_error("A funcao esta adicionando strings vazias.");
        }
        printMessage(" CONCLUIDO", 1, "92");
    } catch (const std::runtime_error& err)
    {
        printMessage(" ERRO", 1, "91");
        printMessage(std::string(".......") + err.what(), 1);
    }
}


void rbtPropertiesTests()
{
    // Teste com inserção crescente
    try
    {
        printMessage("Testando propriedades RBT com insercao crescente (a, b, c, d, e)...", 0);
        BinaryTree* tree = RBT::create();
        std::vector<std::string> words = {"a", "b", "c", "d", "e"};
        
        int size = words.size();
        for (int i = 0; i < size; ++i) RBT::insert(tree, words[i], i);

        if (!isRBT(tree))
        {
            RBT::destroy(tree);
            throw std::runtime_error("A arvore violou as propriedades da RBT.");
        }

        RBT::destroy(tree);
        printMessage(" CONCLUIDO", 1, "92");
    } catch (const std::runtime_error& err)
    {
        printMessage(" ERRO", 1, "91");
        printMessage(std::string(".......") + err.what(), 1);
    }

    // Teste com inserção decrescente
    try
    {
        printMessage("Testando propriedades RBT com insercao decrescente (e, d, c, b, a)...", 0);
        BinaryTree* tree = RBT::create();
        std::vector<std::string> words = {"e", "d", "c", "b", "a"};
        int size = words.size();
        for (int i = 0; i < size; ++i) RBT::insert(tree, words[i], i);

        if (!isRBT(tree))
        {
            RBT::destroy(tree);
            throw std::runtime_error("A arvore violou as propriedades da RBT.");
        }

        RBT::destroy(tree);
        printMessage(" CONCLUIDO", 1, "92");
    } catch (const std::runtime_error& err)
    {
        printMessage(" ERRO", 1, "91");
        printMessage(std::string(".......") + err.what(), 1);
    }

    // Teste com rotação dupla Direita-Esquerda
    try
    {
        printMessage("Testando propriedades RBT com rotacao dupla (Dir-Esq)...", 0);
        BinaryTree* tree = RBT::create();
        RBT::insert(tree, "c", 0);
        RBT::insert(tree, "a", 1);
        RBT::insert(tree, "b", 2);

        if (!isRBT(tree) || tree->root->word != "b")
        {
            RBT::destroy(tree);
            throw std::runtime_error("A arvore falhou na rotacao dupla ou violou propriedades.");
        }

        RBT::destroy(tree);
        printMessage(" CONCLUIDO", 1, "92");
    } catch (const std::runtime_error& err)
    {
        printMessage(" ERRO", 1, "91");
        printMessage(std::string(".......") + err.what(), 1);
    }

    // Teste com recoloração (tio vermelho)
    try
    {
        printMessage("Testando propriedades RBT com recoloracao...", 0);
        BinaryTree* tree = RBT::create();
        RBT::insert(tree, "d", 0);
        RBT::insert(tree, "b", 1);
        RBT::insert(tree, "e", 2);
        RBT::insert(tree, "a", 3);
        
        if (!isRBT(tree) || tree->root->left->isRed != RBT::BLACK || tree->root->right->isRed != RBT::BLACK)
        {
            RBT::destroy(tree);
            throw std::runtime_error("A arvore falhou na recoloracao ou violou propriedades.");
        }
        
        RBT::destroy(tree);
        printMessage(" CONCLUIDO", 1, "92");
    } catch (const std::runtime_error& err)
    {
        printMessage(" ERRO", 1, "91");
        printMessage(std::string(".......") + err.what(), 1);
    }
    
    try
    {
        printMessage("Testando propriedades RBT com numero de rotacoes...", 0);
        BinaryTree* tree = RBT::create();
        std::vector<std::string> words = {"a", "b", "c", "d", "e", "f", "g"};
        for(size_t i = 0; i < words.size(); ++i) {
            RBT::insert(tree, words[i], i);
        }
        
        // Para a sequência de 1 a 7, o número esperado de rotações é 5.
        int valorEsperado = 3; 
        
        if (tree->rotationsCount != valorEsperado)
        {
            // Monta a mensagem de erro
            std::string error_msg = "Errou a contagem de rotacoes. Esperado: " + 
            std::to_string(valorEsperado) + ", Obtido: " + 
            std::to_string(tree->rotationsCount);
            throw std::runtime_error(error_msg);
        }
        RBT::destroy(tree);
        printMessage(" CONCLUIDO", 1, "92");
        
    } catch (const std::runtime_error& err)
    {
        printMessage("FALHA", 1, "91"); // Vermelho brilhante
        printMessage(err.what(), 1);
    }
    
}


int main()
{
    std::cout << "======================= TESTES ESTRUTURAIS DA ARVORE =======================" << std::endl;
    treeStructureTests();

    std::cout << "\n======================= TESTANDO O RETORNO DA ARVORE =======================" << std::endl;
    treeReturnsTests();
    
    std::cout << "\n====================== TESTANDO PROPRIEDADES DA RBT ======================" << std::endl;
    rbtPropertiesTests();

    std::cout << "\nTodos os testes foram concluidos." << std::endl;

    return 0;
}