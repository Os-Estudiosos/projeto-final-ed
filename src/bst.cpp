#include "bst.h"
#include "data.h"
#include "tree_utils.h"

namespace BST
{
    BinaryTree* create()
    {
        BinaryTree *tree = new BinaryTree;                                      // inicio uma árvore nova
        tree->root = nullptr;                                                   // defino a raiz como nula
        return tree;                                                            // retorno a árvore criada
    }

    InsertResult insert(BinaryTree *tree, const std::string &word, int documentId)
    {
        auto start = std::chrono::high_resolution_clock::now();                 // inicio a contagem do tempo
                                                                                
        InsertResult result_insert;                                             // crio estrutra de insert
        result_insert.numComparisons = 0;                                       // defino ambas variáveis como zero
        result_insert.executionTime = 0;    

        if (tree == nullptr || word == "")                                      // verifico se a árvore é nula ou se passaram uma palavra vazia
        {                                                                       // se for, apenas retorno a estrutura de insert inicial (tudo 0)
            return result_insert;                                               // (não faz sentido finalizar a contagem de tempo, pois esse caso nada incrementa as estatísticas)
        }   

        if (tree->root == nullptr)                                              // se a árvore não for nula, mas sua raiz é (árvore vazia)
        {
            tree->root = new Node;                                              // então alocamos um novo nó, que, no caso, é a raiz
            tree->root->word = word;                                            // alocamos a palavra  
            tree->root->documentIds.push_back(documentId);                      // adicionamos o id ao vetor de ids
            tree->root->parent = nullptr;                                       // alocamos o restante como null, pois é raiz
            tree->root->left = nullptr;
            tree->root->right = nullptr;
            auto end = std::chrono::high_resolution_clock::now();               // encerramos a contagem de tempo
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); // subtraímos o tempo do começo e o do fim
            double time_ms = duration.count();                                  // mudamos para double
            result_insert.executionTime = time_ms;                              // alteramos o atributo do tempo de execução 
            return result_insert;                                               // retornamos a struct alterada
        }
        else                                                                    // caso a árvore já tenha algum nó
        {
            Node *current = tree->root;                                         // salvo o nó da raiz 
            Node *last = nullptr;                                               // inicio um nó que irei usar depois para fazer a ligação entre o nó adicionado e seu pai
            while (current != nullptr)                                          // enquanto o nó não for nulo(vamos fazer a comparação e passar em todos os nós necessários)
            {
                if (word == current->word)                                      // se a palavra for igual a atual
                {
                    // aqui, assumo documentIds não vazio (para não fazer a verificação se é vazio), 
                    // pois, por construção, o nó existente sempre tem pelo menos um ID
                    if (current->documentIds.back() == documentId)              // vejo se o último elemento da lista de IDs é igual o id do documento atual
                    {                                                           // pois se for, eu apenas ignoro
                                                                                // (posso olhar apenas o último id do vetor pois os ids são colocados em ordem e portanto para olhar se um id já foi colocado basta olhar por último)
                        result_insert.numComparisons += 1;                      // incremento o número de comparações(relacionado a comparar word == current-> word)
                        auto end = std::chrono::high_resolution_clock::now();   // encerramos a contagem de tempo
                        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); // subtraímos o tempo do começo e o do fim
                        double time_ms = duration.count();                      // mudamos para double
                        result_insert.executionTime = time_ms;                  // alteramos o atributo do tempo de execução 
                        return result_insert;                                   // retornamos a struct alterada
                    }
                    else                                                        // caso o id ainda não estiver sido incluído no vetor                                                                       
                    {
                        result_insert.numComparisons += 1;                      
                        current->documentIds.push_back(documentId);             // adiciono o id ao vetor 
                        auto end = std::chrono::high_resolution_clock::now();   // encerramos a contagem de tempo
                        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); // subtraímos o tempo do começo e o do fim
                        double time_ms = duration.count();                      // mudamos para double
                        result_insert.executionTime = time_ms;                  // alteramos o atributo do tempo de execução 
                        return result_insert;                                   // retornamos a struct alterada
                    }
                }
                else if (word > current->word)                                  // caso a palavra não seja igual ao nó atual e seja "maior"
                {
                    result_insert.numComparisons += 1;                          // incrementamos o número de comparações
                    last = current;                                             // atualizo o último para ser o pai
                    current = current->right;                                   // atualizo o current para direita pela palavra ser "maior"
                }
                else                                                            // caso contrário (palavra menor que o nó atual)
                {
                    result_insert.numComparisons += 1;                          // incrementamos o número de comparações
                    last = current;                                             // atualizo o último para ser o pai
                    current = current->left;                                    // atualizo o current para esquerda pela palavra ser "menor"
                }
            }

            // se, a palavra não está na lista e chegamos no current ser nullptr(lembre-se que salvamos o pai, o "last"):
            Node *newNode = new Node;                                           // criamos um novo nó
            newNode->parent = last;                                             // ligamos ao pai
            newNode->left = nullptr;                                            // a esquerda e a direita ainda será nullptr
            newNode->right = nullptr;
            newNode->documentIds.push_back(documentId);                         // adiciono o id do documento ao seu vetor
            newNode->word = word;                                               // incremento a palavra sendo a palavra

            // por fim, devemos verificar se iremos alterar o ponteiro para o filho do último nó a esquerda ou a direita
            if (word > last->word)                                              // se for "maior"
            {                                                                   
                result_insert.numComparisons += 1;                              // incrementamos o número de comparações
                last->right = newNode;                                          // alteramos o nó da direita do pai como o nó que criamos
            }
            else                                                                // se for "menor"
            {
                result_insert.numComparisons += 1;                              // incrementamos o número de comparações
                last->left = newNode;                                           // alteramos o nó da esquerda do pai como o nó que criamos
            }

            auto end = std::chrono::high_resolution_clock::now();               // encerramos a contagem de tempo
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); // subtraímos o tempo do começo e o do fim
            double time_ms = duration.count();                                  // mudamos para double
            result_insert.executionTime = time_ms;                              // alteramos o atributo do tempo de execução 
            return result_insert;                                               // retornamos a struct alterada
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
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); // subtraímos o tempo do começo e o do fim
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
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); // subtraímos o tempo do começo e o do fim
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
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); // subtraímos o tempo do começo e o do fim
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
}