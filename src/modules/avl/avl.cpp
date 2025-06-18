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
        tree->height = 0;                                                       // altura da árvore
        tree->rotationsCount = 0;                                               // contagem de rotações

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
        node->height = 0;                                                       // Definimos a altura como 0, pois é um novo nó
        
        return node;  
    }

    // Principais
    InsertResult insert(BinaryTree *tree, const std::string &word, int documentId)
    {
        auto start = std::chrono::high_resolution_clock::now();                 // Inicio a contagem do tempo
                                                                                
        InsertResult resultInsert;                                             // Crio estrutura de insert
        resultInsert.numComparisons = 0;                                       // Defino ambas variáveis como zero
        resultInsert.executionTime = 0;    

        if (tree == nullptr || word == "")                                      // Verifico se a árvore é nula ou se passaram uma palavra vazia
        {                                                                       // Se for, apenas retorno a estrutura de insert inicial (tudo 0)
            return resultInsert;                                               // (não faz sentido finalizar a contagem de tempo, pois esse caso nada incrementa as estatísticas)
        }   

        if (tree->root == nullptr)                                              // Se a árvore não for nula, mas sua raiz é (árvore vazia)
        {
            tree->root = createNode(documentId, word);                          // Raiz é sempre preta em uma RBT
            tree->nodeCount += 1;                                               // incrementando a contagem de nós
            auto end = std::chrono::high_resolution_clock::now();               // Encerramos a contagem de tempo
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start); // Subtraímos o tempo do começo e o do fim
            double time_ms = duration.count();                                  // Mudamos para double
            resultInsert.executionTime = time_ms;                              // Alteramos o atributo do tempo de execução

            return resultInsert;                                               // Retornamos a struct alterada
            
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
                        resultInsert.numComparisons += 1;                      // Incremento o número de comparações (relacionado a comparar word == current->word)
                        auto end = std::chrono::high_resolution_clock::now();   // Encerramos a contagem de tempo
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start); // Subtraímos o tempo do começo e o do fim
                        double time_ms = duration.count();                      // Mudamos para double
                        resultInsert.executionTime = time_ms;                  // Alteramos o atributo do tempo de execução 
                        return resultInsert;                                   // Retornamos a struct alterada
                    }
                    else                                                        // Caso o id ainda não estiver sido incluído no vetor                                                                       
                    {
                        resultInsert.numComparisons += 1;                      
                        current->documentIds.push_back(documentId);             // Adiciono o id ao vetor 
                        auto end = std::chrono::high_resolution_clock::now();   // Encerramos a contagem de tempo
                        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start); // Subtraímos o tempo do começo e o do fim
                        double time_ms = duration.count();                      // Mudamos para double
                        resultInsert.executionTime = time_ms;                  // Alteramos o atributo do tempo de execução 
                        return resultInsert;                                   // Retornamos a struct alterada
                    }
                }
                else if (word > current->word)                                  // Caso a palavra não seja igual ao nó atual e seja "maior"
                {
                    resultInsert.numComparisons += 1;                          // Incrementamos o número de comparações
                    last = current;                                             // Atualizo o último para ser o pai
                    current = current->right;                                   // Atualizo o current para direita pela palavra ser "maior"
                }
                else                                                            // Caso contrário (palavra menor que o nó atual)
                {
                    resultInsert.numComparisons += 1;                          // Incrementamos o número de comparações
                    last = current;                                             // Atualizo o último para ser o pai
                    current = current->left;                                    // Atualizo o current para esquerda pela palavra ser "menor"
                }
            }

            // Se a palavra não está na lista e chegamos no current ser nullptr (lembre-se que salvamos o pai, o "last"):
            Node* newNode = createNode(documentId, word);                        // Criamos um novo nó
            tree->nodeCount += 1;                                                // incrementando a contagem de nós

            newNode->parent = last;

            // Por fim, devemos verificar se iremos alterar o ponteiro para o filho do último nó a esquerda ou a direita
            if (word > last->word)                                              // Se for "maior"
            {                                                                   
                resultInsert.numComparisons += 1;                              // Incrementamos o número de comparações
                last->right = newNode;                                          // Alteramos o nó da direita do pai como o nó que criamos
            }
            else                                                                // Se for "menor"
            {
                resultInsert.numComparisons += 1;                              // Incrementamos o número de comparações
                last->left = newNode;                                           // Alteramos o nó da esquerda do pai como o nó que criamos
            }

            // Corrigir as propriedades da AVL após a inserção
            fixInsert(&tree->root, newNode, tree);

            auto end = std::chrono::high_resolution_clock::now();               // Encerramos a contagem de tempo
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start); // Subtraímos o tempo do começo e o do fim
            double time_ms = duration.count();                                  // Mudamos para double
            resultInsert.executionTime = time_ms;                              // Alteramos o atributo do tempo de execução
            tree->height = tree->root->height;                                 // Definindo a altura da árvore

            return resultInsert;                                               // Retornamos a struct alterada
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
        return n == nullptr ? -1 : n->height;
    }

    void recomputeHeight(Node* n)
    {
        if (n != nullptr) 
        {
            n->height = 1 + max(getHeight(n->left), getHeight(n->right));
        }
    }

    void rotateLeft(Node** root, Node* x)
    {
        Node* y = x->right;                                                     // y será o novo pai de x após a rotação
        x->right = y->left;                                                     // o filho esquerdo de y vira o filho direito de x

        if (y->left != nullptr)                                                 // se y tiver filho esquerdo
        {
            y->left->parent = x;                                                // atualiza o pai desse filho para x
        }

        y->parent = x->parent;                                                  // y assume o pai de x

        // Atualiza o ponteiro do pai de x para apontar para y
        if (x->parent == nullptr)                                               // se x era a raiz
        {
            *root = y;                                                          // y vira a nova raiz
        }
        else if (x == x->parent->left)                                          // se x era filho à esquerda
        {
            x->parent->left = y;                                                // y vira o novo filho à esquerda
        }
        else                                                                    // se x era filho à direita
        {
            x->parent->right = y;                                               // y vira o novo filho à direita
        }

        y->left = x;                                                            // x vira filho à esquerda de y
        x->parent = y;                                                          // atualiza o pai de x para ser y

        recomputeHeight(x);                                                     // Recomputo as alturas
        recomputeHeight(y);

    }

    void rotateRight(Node** root, Node* y)
    {
        Node* x = y->left;                                                      // x será o novo pai de y após a rotação
        y->left = x->right;                                                     // o filho direito de x vira o filho esquerdo de y

        if (x->right != nullptr)                                                // se x tiver filho direito
        {
            x->right->parent = y;                                               // atualiza o pai desse filho para y
        }

        x->parent = y->parent;                                                  // x assume o pai de y

        // Atualiza o ponteiro do pai de y para apontar para x
        if (y->parent == nullptr)                                               // se y era a raiz
        {
            *root = x;                                                          // x vira a nova raiz
        }
        else if (y == y->parent->right)                                         // se y era filho à direita
        {
            y->parent->right = x;                                               // x vira o novo filho à direita
        }
        else                                                                    // se y era filho à esquerda
        {
            y->parent->left = x;                                                // x vira o novo filho à esquerda
        }

        x->right = y;                                                           // y vira filho à direita de x
        y->parent = x;                                                          // atualiza o pai de y para ser x

        recomputeHeight(x);                                                     // recomputo as alturas
        recomputeHeight(y);
    }

    
    int balanceFactor(Node* n) 
    {
        if (n == nullptr) return 0;                                            // Se o nó for nulo, o fator de balanceamento é 0
       
        return getHeight(n->left) - getHeight(n->right);                       // Retorna a diferença entre a altura do filho esquerdo e do direito
    }


    void fixInsert(Node **root, Node* z, BinaryTree *tree)
    {
        Node* current = z;
        while (current != nullptr) 
        {
            recomputeHeight(current);
            int bf = balanceFactor(current);

            if (bf > 1) // Left-heavy
            { 
                if (balanceFactor(current->left) < 0) // LR
                { 
                    rotateLeft(root, current->left);
                    rotateRight(root, current);
                    tree->rotationsCount += 2;
                } 
                else // LL 
                { 
                    rotateRight(root, current);
                    tree->rotationsCount += 1;
                }

                recomputeHeight(current->left);
                recomputeHeight(current->right);
                recomputeHeight(current);

            } else if (bf < -1)  // Right-heavy
            {
                if (balanceFactor(current->right) > 0) // RL
                { 
                    rotateRight(root, current->right);
                    rotateLeft(root, current);
                    tree->rotationsCount += 2;
                } else // RR 
                { 
                    rotateLeft(root, current);
                    tree->rotationsCount += 1;
                }

                recomputeHeight(current->left);
                recomputeHeight(current->right);
                recomputeHeight(current);
            }
            current = current->parent;
        }
    }

}
