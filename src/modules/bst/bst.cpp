#include "bst.h"
#include "../data.h"
#include "../../utils/tree_utils.h"

namespace BST
{
    BinaryTree* create()
    {
        BinaryTree *tree = new BinaryTree;                                      // inicio uma árvore nova
        tree->root = nullptr;                                                   // defino a raiz como nula
        tree->height = 0;                                                       // inicio a altura como 0
        return tree;                                                            // retorno a árvore criada
    }

    InsertResult insert(BinaryTree *tree, const std::string &word, int documentId)
    {
        auto start = std::chrono::high_resolution_clock::now();                 // inicio a contagem do tempo
                                                                                
        InsertResult resultInsert;                                              // crio estrutra de insert
        resultInsert.numComparisons = 0;                                        // defino ambas variáveis como zero
        resultInsert.executionTime = 0;    

        if (tree == nullptr || word == "")                                      // verifico se a árvore é nula ou se passaram uma palavra vazia
        {                                                                       // se for, apenas retorno a estrutura de insert inicial (tudo 0)
            return resultInsert;                                                // (não faz sentido finalizar a contagem de tempo, pois esse caso nada incrementa as estatísticas)
        }   

        if (tree->root == nullptr)                                              // se a árvore não for nula, mas sua raiz é (árvore vazia)
        {
            tree->root = new Node;                                              // então alocamos um novo nó, que, no caso, é a raiz
            tree->root->word = word;                                            // alocamos a palavra  
            tree->root->documentIds.push_back(documentId);                      // adicionamos o id ao vetor de ids
            tree->root->parent = nullptr;                                       // alocamos o restante como null, pois é raiz
            tree->root->left = nullptr;
            tree->root->right = nullptr;
            tree->root->depth = 0;                                              // profundidade da raiz é 0
            auto end = std::chrono::high_resolution_clock::now();               // encerramos a contagem de tempo
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start); // subtraímos o tempo do começo e o do fim
            double time_ms = duration.count();                                  // mudamos para double
            resultInsert.executionTime = time_ms;                               // alteramos o atributo do tempo de execução 
            return resultInsert;                                                // retornamos a struct alterada
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
                        resultInsert.numComparisons += 1;                      // incremento o número de comparações(relacionado a comparar word == current-> word)
                        auto end = std::chrono::high_resolution_clock::now();   // encerramos a contagem de tempo
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start); // subtraímos o tempo do começo e o do fim
                        double time_ms = duration.count();                      // mudamos para double
                        resultInsert.executionTime = time_ms;                  // alteramos o atributo do tempo de execução 
                        return resultInsert;                                   // retornamos a struct alterada
                    }
                    else                                                        // caso o id ainda não estiver sido incluído no vetor                                                                       
                    {
                        resultInsert.numComparisons += 1;                      
                        current->documentIds.push_back(documentId);             // adiciono o id ao vetor 
                        auto end = std::chrono::high_resolution_clock::now();   // encerramos a contagem de tempo
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start); // subtraímos o tempo do começo e o do fim
                        double time_ms = duration.count();                      // mudamos para double
                        resultInsert.executionTime = time_ms;                  // alteramos o atributo do tempo de execução 
                        return resultInsert;                                   // retornamos a struct alterada
                    }
                }
                else if (word > current->word)                                  // caso a palavra não seja igual ao nó atual e seja "maior"
                {
                    resultInsert.numComparisons += 1;                          // incrementamos o número de comparações
                    last = current;                                             // atualizo o último para ser o pai
                    current = current->right;                                   // atualizo o current para direita pela palavra ser "maior"
                }
                else                                                            // caso contrário (palavra menor que o nó atual)
                {
                    resultInsert.numComparisons += 1;                          // incrementamos o número de comparações
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
            newNode->depth = newNode->parent->depth + 1;                        // a profundidade do novo nó sera a profundidade do pai mais um
            tree->nodeCount += 1;                                               // incrementando a contagem de nós

            // por fim, devemos verificar se iremos alterar o ponteiro para o filho do último nó a esquerda ou a direita
            if (word > last->word)                                              // se for "maior"
            {                                                                   
                resultInsert.numComparisons += 1;                              // incrementamos o número de comparações
                last->right = newNode;                                          // alteramos o nó da direita do pai como o nó que criamos
            }
            else                                                                // se for "menor"
            {
                resultInsert.numComparisons += 1;                              // incrementamos o número de comparações
                last->left = newNode;                                           // alteramos o nó da esquerda do pai como o nó que criamos
            }

            if (tree->height < newNode->depth)                                  //  Enfim, se a altura da árvore for menor que a profundidade do novo nó adicionado
            {
                tree->height = newNode->depth;                                  // então a altura da raiz (árvore) é a nova maior profundidade
            }

            auto end = std::chrono::high_resolution_clock::now();               // encerramos a contagem de tempo
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start); // subtraímos o tempo do começo e o do fim
            double time_ms = duration.count();                                  // mudamos para double
            resultInsert.executionTime = time_ms;                              // alteramos o atributo do tempo de execução 
            return resultInsert;                                               // retornamos a struct alterada
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