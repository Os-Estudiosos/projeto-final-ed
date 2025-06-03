#include "rbt.h"
#include "../data.h"
#include "../../utils/tree_utils.h"

namespace RBT
{


    BinaryTree* create()
    {
        BinaryTree *tree = new BinaryTree;                                      // inicio uma árvore nova
        tree->root = nullptr;                                                   // defino a raiz como nula
        return tree;                                                            // retorno a árvore criada
    }


    Node* createNode(int documentId, const std::string &word, Color color)
    {
        Node* node = new Node;                                                  // Então alocamos um novo nó, que, no caso, é a raiz
        node->word = word;                                                      // Alocamos a palavra  
        node->documentIds.push_back(documentId);                                // Adicionamos o id ao vetor de ids
        node->parent = nullptr;                                                 // Alocamos o restante como null, pois é raiz
        node->left = nullptr;
        node->right = nullptr;
        node->isRed = color;   
        
        return node;  
    }


    InsertResult insert(BinaryTree *tree, const std::string &word, int documentId)
    {
        auto start = std::chrono::high_resolution_clock::now();                 // Inicio a contagem do tempo
                                                                                
        InsertResult result_insert;                                             // Crio estrutura de insert
        result_insert.numComparisons = 0;                                       // Defino ambas variáveis como zero
        result_insert.executionTime = 0;    

        if (tree == nullptr || word == "")                                      // Verifico se a árvore é nula ou se passaram uma palavra vazia
        {                                                                       // Se for, apenas retorno a estrutura de insert inicial (tudo 0)
            return result_insert;                                               // (não faz sentido finalizar a contagem de tempo, pois esse caso nada incrementa as estatísticas)
        }   

        if (tree->root == nullptr)                                              // Se a árvore não for nula, mas sua raiz é (árvore vazia)
        {
            tree->root = createNode(documentId, word, BLACK);                                         // Raiz é sempre preta em uma RBT
            auto end = std::chrono::high_resolution_clock::now();               // Encerramos a contagem de tempo
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start); // Subtraímos o tempo do começo e o do fim
            double time_ms = duration.count();                                  // Mudamos para double
            result_insert.executionTime = time_ms;                              // Alteramos o atributo do tempo de execução 
            return result_insert;                                               // Retornamos a struct alterada
        }
        else                                                                    // Caso a árvore já tenha algum nó
        {
            Node *current = tree->root;                                         // Salvo o nó da raiz 
            Node *last = nullptr;                                               // Inicio um nó que irei usar depois para fazer a ligação entre o nó adicionado e seu pai
            while (current != nullptr)                                          // Enquanto o nó não for nulo (vamos fazer a comparação e passar em todos os nós necessários)
            {
                if (word == current->word)                                      // Se a palavra for igual a atual
                {
                    // Aqui, assumo documentIds não vazio (para não fazer a verificação se é vazio), 
                    // pois, por construção, o nó existente sempre tem pelo menos um ID
                    if (current->documentIds.back() == documentId)              // Vejo se o último elemento da lista de IDs é igual o id do documento atual
                    {                                                           // Pois se for, eu apenas ignoro
                                                                                // (posso olhar apenas o último id do vetor pois os ids são colocados em ordem e portanto para olhar se um id já foi colocado basta olhar por último)
                        result_insert.numComparisons += 1;                      // Incremento o número de comparações (relacionado a comparar word == current->word)
                        auto end = std::chrono::high_resolution_clock::now();   // Encerramos a contagem de tempo
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start); // Subtraímos o tempo do começo e o do fim
                        double time_ms = duration.count();                      // Mudamos para double
                        result_insert.executionTime = time_ms;                  // Alteramos o atributo do tempo de execução 
                        return result_insert;                                   // Retornamos a struct alterada
                    }
                    else                                                        // Caso o id ainda não estiver sido incluído no vetor                                                                       
                    {
                        result_insert.numComparisons += 1;                      
                        current->documentIds.push_back(documentId);             // Adiciono o id ao vetor 
                        auto end = std::chrono::high_resolution_clock::now();   // Encerramos a contagem de tempo
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start); // Subtraímos o tempo do começo e o do fim
                        double time_ms = duration.count();                      // Mudamos para double
                        result_insert.executionTime = time_ms;                  // Alteramos o atributo do tempo de execução 
                        return result_insert;                                   // Retornamos a struct alterada
                    }
                }
                else if (word > current->word)                                  // Caso a palavra não seja igual ao nó atual e seja "maior"
                {
                    result_insert.numComparisons += 1;                          // Incrementamos o número de comparações
                    last = current;                                             // Atualizo o último para ser o pai
                    current = current->right;                                   // Atualizo o current para direita pela palavra ser "maior"
                }
                else                                                            // Caso contrário (palavra menor que o nó atual)
                {
                    result_insert.numComparisons += 1;                          // Incrementamos o número de comparações
                    last = current;                                             // Atualizo o último para ser o pai
                    current = current->left;                                    // Atualizo o current para esquerda pela palavra ser "menor"
                }
            }

            // Se a palavra não está na lista e chegamos no current ser nullptr (lembre-se que salvamos o pai, o "last"):
            Node* newNode = createNode(documentId, word, RED);                        // Criamos um novo nó

            // Por fim, devemos verificar se iremos alterar o ponteiro para o filho do último nó a esquerda ou a direita
            if (word > last->word)                                              // Se for "maior"
            {                                                                   
                result_insert.numComparisons += 1;                              // Incrementamos o número de comparações
                last->right = newNode;                                          // Alteramos o nó da direita do pai como o nó que criamos
            }
            else                                                                // Se for "menor"
            {
                result_insert.numComparisons += 1;                              // Incrementamos o número de comparações
                last->left = newNode;                                           // Alteramos o nó da esquerda do pai como o nó que criamos
            }

            // Corrigir as propriedades da RBT após a inserção
            fixInsert(&tree->root, newNode);

            auto end = std::chrono::high_resolution_clock::now();               // Encerramos a contagem de tempo
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start); // Subtraímos o tempo do começo e o do fim
            double time_ms = duration.count();                                  // Mudamos para double
            result_insert.executionTime = time_ms;                              // Alteramos o atributo do tempo de execução 
            return result_insert;                                               // Retornamos a struct alterada
        }
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
                else if (word > current->word)                                  // caso a palavra não seja igual ao nó atual e seja "maior"
                {
                    result_search.numComparisons += 1;                          // incrementamos o número de comparações
                    current = current->right;                                   // atualizo o current para direita pela palavra ser "maior"
                }
                else                                                            // caso contrário (palavra menor que o nó atual)
                {
                    result_search.numComparisons += 1;                          // incrementamos o número de comparações
                    current = current->left;                                    // atualizo o current para esquerda pela palavra ser "menor"
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
            deleteNode(root);                                                   // usamos uma função auxiliar que deleta toda a árvore recursivamente
                                                                                // (só deleta o pai após deletar os filhos)
            delete tree;                                                        // deletamos a árvore
        }
    }
    void rotateLeft(Node** root, Node* x)
    {
        Node* y = x->right;
        x->right = y->left;
        
        if (y->left != nullptr)
            y->left->parent = x;

        y->parent = x->parent;

        // Atualiza pai de x
        if (x->parent == nullptr)
            *root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }


    void rotateRight(Node** root, Node* y)
    {
        Node* x = y->left;
        y->left = x->right;

        if (x->right != nullptr)
            x->right->parent = y;

        x->parent = y->parent;

        // Atualiza pai de y
        if (y->parent == nullptr)
            *root = x;
        else if (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;

        x->right = y;
        y->parent = x;
    }


    void fixInsert(Node **root, Node* z)
    {
        while (z->parent != nullptr && z->parent->isRed == RED)
        {
            Node* parent = z->parent;
            Node* grandparent = parent->parent;

            if (parent == grandparent->left)
            {
                Node* uncle = grandparent->right;

                if (uncle != nullptr && uncle->isRed == RED)
                {
                    // Tio vermelho — recoloração
                    parent->isRed = BLACK;
                    uncle->isRed = BLACK;
                    grandparent->isRed = RED;
                    z = grandparent;
                }
                else
                {
                    if (z == parent->right)
                    {
                        // Conversão para caso 3
                        z = parent;
                        rotateLeft(root, z);
                        parent = z->parent;
                        grandparent = parent->parent;
                    }

                    // Corrige com rotação
                    parent->isRed = BLACK;
                    grandparent->isRed = RED;
                    rotateRight(root, grandparent);
                }
            }
            else
            {
                Node* uncle = grandparent->left;

                if (uncle != nullptr && uncle->isRed == RED)
                {
                    parent->isRed = BLACK;
                    uncle->isRed = BLACK;
                    grandparent->isRed = RED;
                    z = grandparent;
                }
                else
                {
                    if (z == parent->left)
                    {
                        z = parent;
                        rotateRight(root, z);
                        parent = z->parent;
                        grandparent = parent->parent;
                    }

                    parent->isRed = BLACK;
                    grandparent->isRed = RED;
                    rotateLeft(root, grandparent);
                }
            }
        }

        (*root)->isRed = BLACK; // Raiz deve ser preta
    }
}

