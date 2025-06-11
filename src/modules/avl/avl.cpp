#include "avl.h"
#include "../data.h"
#include "../../utils/tree_utils.h"

namespace AVL
{

    // Auxiliares
    BinaryTree* create()
    {
        BinaryTree *tree = new BinaryTree;                                      // inicio uma árvore nova
        tree->root = nullptr;                                                   // defino a raiz como nula

        return tree;                                                            // retorno a árvore criada
    }


    Node* createNode(int documentId, const std::string &word)
    {
        Node* node = new Node;                                                  // Então alocamos um novo nó, que, no caso, é a raiz
        node->word = word;                                                      // Alocamos a palavra  
        node->documentIds.push_back(documentId);                                // Adicionamos o id ao vetor de ids
        node->parent = nullptr;                                                 // Alocamos o restante como null, pois é raiz
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1;                                                       // Definimos a altura como 1, pois é um novo nó
        
        return node;  
    }


    void destroy(BinaryTree *tree)
    {
        if (tree == nullptr)                                                    // caso a árvore seja nula, não há nada a ser deletado 
        {
            return;
        }
        else if (tree->root == nullptr)                                         // caso a árvore exista mas não tenha nós
        {
            delete tree;                                                        // apenas deletamos a árvore
            return;
        }
        else                                                                    // por fim, se a árvore exita e tenha nós
        {
            Node *root = tree->root;                                            // salvamos o nó raiz
            deleteNode(root);                                                   // usamos uma função auxiliar que deleta toda a árvore recursivamente (só deleta o pai após deletar os filhos)
            delete tree;                                                        // deletamos a árvore
        }
    }


    int max(int a, int b) 
    {
        return (a > b) ? a : b;                                                // Retorna o maior entre a e b
    }


    int getHeight(Node* n) 
    {
        return n == nullptr ? 0 : n->height;
    }


    void recomputeHeight(Node* n)
    {
        if (n != nullptr) {
            n->height = 1 + max(getHeight(n->left), getHeight(n->right));
        }
    }


    // Rotação à esquerda
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        // Realiza a rotação
        y->left = x;
        x->right = T2;

        // Atualiza os pais
        y->parent = x->parent; // O pai de y se torna o pai de x
        if (x != nullptr) x->parent = y;
        if (T2 != nullptr) T2->parent = x;

        // Atualiza alturas
        recomputeHeight(x);
        recomputeHeight(y);

        return y;
    }

    // Rotação à direita
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        // Realiza a rotação
        x->right = y;
        y->left = T2;

        // Atualiza os pais
        x->parent = y->parent; // O pai de x se torna o pai de y
        if (y != nullptr) y->parent = x;
        if (T2 != nullptr) T2->parent = y;

        // Atualiza alturas
        recomputeHeight(y);
        recomputeHeight(x);

        return x;
    }

    int balanceFactor(Node* n) 
    {
        if (n == nullptr) 
            return 0;                                                          // Se o nó for nulo, o fator de balanceamento é 0
        return getHeight(n->left) - getHeight(n->right);                       // Retorna a diferença entre a altura do filho esquerdo e do direito
    }

    // Função para balancear o nó após a inserção
    Node* balance(Node* node, InsertResult &result_insert) {
        if (node == nullptr) return node;

        recomputeHeight(node);

        int bf = balanceFactor(node);

        // Caso Esquerda-Esquerda
        if (bf > 1 && balanceFactor(node->left) >= 0) {
            result_insert.numRotations++;
            return rotateRight(node);
        }

        // Caso Direita-Direita
        if (bf < -1 && balanceFactor(node->right) <= 0) {
            result_insert.numRotations++;
            return rotateLeft(node);
        }

        // Caso Esquerda-Direita
        if (bf > 1 && balanceFactor(node->left) < 0) {
            result_insert.numRotations += 2;
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Caso Direita-Esquerda
        if (bf < -1 && balanceFactor(node->right) > 0) {
            result_insert.numRotations += 2;
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Função auxiliar recursiva para inserção
    Node* insertRecursive(Node* node, int documentId, const std::string &word, InsertResult &result_insert) {
        if (node == nullptr) {
            return createNode(documentId, word);
        }

        result_insert.numComparisons++;
        if (word < node->word) {
            node->left = insertRecursive(node->left, documentId, word, result_insert);
            node->left->parent = node;
        } else if (word > node->word) {
            node->right = insertRecursive(node->right, documentId, word, result_insert);
            node->right->parent = node;
        } else {
            // Palavra já existe, adiciona documentId se não estiver presente
            bool found = false;
            for (int id : node->documentIds) {
                if (id == documentId) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                node->documentIds.push_back(documentId);
            }
            return node;
        }

        return balance(node, result_insert);
    }

    // Principais
    InsertResult insert(BinaryTree *tree, const std::string &word, int documentId)
    {
        auto start = std::chrono::high_resolution_clock::now();                 // Inicio a contagem do tempo
        InsertResult result_insert;                                             // Crio estrutura de insert
        result_insert.numComparisons = 0;                                       // Defino ambas variáveis como zero
        result_insert.executionTime = 0;
        result_insert.numRotations = 0;    
        if (tree == nullptr || word == "")                                      // Verifico se a árvore é nula ou se passaram uma palavra vazia
        {                                                                       // Se for, apenas retorno a estrutura de insert inicial (tudo 0)
            return result_insert;                                               // (não faz sentido finalizar a contagem de tempo, pois esse caso nada incrementa as estatísticas)
        }   
        
        tree->root = insertRecursive(tree->root, documentId, word, result_insert);

        auto end = std::chrono::high_resolution_clock::now();               // Encerramos a contagem de tempo
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start); // Subtraímos o tempo do começo e o do fim
        double time_ms = duration.count();                                  // Mudamos para double
        result_insert.executionTime = time_ms;                              // Alteramos o atributo do tempo de execução 
        return result_insert;                                               // Retornamos a struct alterada
    }


    SearchResult search(BinaryTree *tree, const std::string &word)
    {
        auto start = std::chrono::high_resolution_clock::now();                 // inicio a contagem do tempo
        SearchResult result_search;                                             // inicio a struct search result
        result_search.found = 0;                                                // inicio genéricamente os atributos 
        result_search.numComparisons = 0;
        result_search.executionTime = 0;
        result_search.documentIds = std::vector<int>{};                         // inicio um vetor vazio ao vetor de documentos
        if (tree == nullptr)                                                    // se a árvore for vazia
        {
            return result_search;                                               // apenas retorno a estrutura genérica criada antes  
        }                                                                       // (não faz sentido finalizar a contagem de tempo, pois esse caso nada incrementa as estatísticas)
        if (tree->root == nullptr)                                              // caso a árvore exista mas a raiz seja nula  
        {
            auto end = std::chrono::high_resolution_clock::now();               // encerramos a contagem de tempo
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start); // subtraímos o tempo do começo e o do fim
            double time_ms = duration.count();                                  // mudamos para double
            result_search.executionTime = time_ms;                              // alteramos o atributo do tempo de execução 
            return result_search;                                               // retornamos a struct alterada
        }
        else                                                                    // caso exista a árvore e exista algum nó
        {
            Node *current = tree->root;                                         // salvo o nó raiz
            while (current != nullptr)                                          // enquanto o nó não for nulo
            {
                if (word == current->word)                                      // verifico se a palavra atual é igual a palavra procurada
                {
                    result_search.numComparisons += 1;                          // incremento ao número de comparações
                    result_search.found = 1;                                    // altero o found, sinalizando que a palavra foi encontrada
                    result_search.documentIds = current->documentIds;           // altero o vetor de documentos para ser o vetor da palavra encontrada
                    auto end = std::chrono::high_resolution_clock::now();       // encerramos a contagem de tempo
                    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start); // subtraímos o tempo do começo e o do fim
                    double time_ms = duration.count();                          // mudamos para double
                    result_search.executionTime = time_ms;                      // alteramos o atributo do tempo de execução 
                    return result_search;                                       // retornamos a struct alterada
                }
                else if (word > current->word)                                  // caso a palavra não seja igual ao nó atual e seja \"maior\"
                {
                    result_search.numComparisons += 1;                          // incrementamos o número de comparações
                    current = current->right;                                   // atualizo o current para direita pela palavra ser \"maior\"
                }
                else                                                            // caso contrário (palavra menor que o nó atual)
                {
                    result_search.numComparisons += 1;                          // incrementamos o número de comparações
                    current = current->left;                                    // atualizo o current para esquerda pela palavra ser \"menor\"
                }
            }
            // note que se não acharmos a palavra na árvore, apenas retornaremos a struct search result como definida inicialmente, a menos de mudar o tempo
            auto end = std::chrono::high_resolution_clock::now();               // portanto, encerramos a contagem de tempo
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start); // subtraímos o tempo do começo e o do fim
            double time_ms = duration.count();                                  // mudamos para double
            result_search.executionTime = time_ms;                              // alteramos o atributo do tempo de execução 
            return result_search;                                               // retornamos a struct alterada
        }
    }
}
