#include "rbt.h"
#include "../data.h"
#include "../../utils/tree_utils.h"

namespace RBT
{
    BinaryTree* create()
    {
        BinaryTree *tree = new BinaryTree;                                      // inicio uma árvore nova
        tree->root = nullptr;  
        tree->height = 0;                                                       // defino a raiz como nula
        tree->rotationsCount = 0;
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
                                                                                
        InsertResult resultInsert;                                             // Crio estrutura de insert
        resultInsert.numComparisons = 0;                                       // Defino ambas variáveis como zero
        resultInsert.executionTime = 0;    
        if (tree == nullptr || word == "")                                      // Verifico se a árvore é nula ou se passaram uma palavra vazia
        {                                                                       // Se for, apenas retorno a estrutura de insert inicial (tudo 0)
            return resultInsert;                                               // (não faz sentido finalizar a contagem de tempo, pois esse caso nada incrementa as estatísticas)
        }   

        if (tree->root == nullptr)                                              // Se a árvore não for nula, mas sua raiz é (árvore vazia)
        {
            tree->root = createNode(documentId, word, BLACK);                                         // Raiz é sempre preta em uma RBT
            tree->nodeCount += 1;                                                // incrementando a contagem de nós
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
            Node* newNode = createNode(documentId, word, RED);                        // Criamos um novo nó
            tree->nodeCount += 1;                                                     // incrementando a contagem de nós
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

            // Corrigir as propriedades da RBT após a inserção
            fixInsert(&tree->root, newNode, tree);

            auto end = std::chrono::high_resolution_clock::now();               // Encerramos a contagem de tempo
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start); // Subtraímos o tempo do começo e o do fim
            double time_ms = duration.count();                                  // Mudamos para double
            resultInsert.executionTime = time_ms;                              // Alteramos o atributo do tempo de execução 
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
            deleteNode(root);                                                   // usamos uma função auxiliar que deleta toda a árvore recursivamente                                                                 // (só deleta o pai após deletar os filhos)
            delete tree;                                                        // deletamos a árvore
        }
    }

        void rotateLeft(Node** root, Node* x)
    {
        Node* y = x->right;                                                     // y será o novo pai de x após a rotação
        x->right = y->left;                                                     // o filho esquerdo de y vira o filho direito de x

        if (y->left != nullptr)                                                 // se y tiver filho esquerdo
            y->left->parent = x;                                                // atualiza o pai desse filho para x

        y->parent = x->parent;                                                  // y assume o pai de x

        // Atualiza o ponteiro do pai de x para apontar para y
        if (x->parent == nullptr)                                               // se x era a raiz
            *root = y;                                                          // y vira a nova raiz
        else if (x == x->parent->left)                                          // se x era filho à esquerda
            x->parent->left = y;                                                // y vira o novo filho à esquerda
        else                                                                    // se x era filho à direita
            x->parent->right = y;                                               // y vira o novo filho à direita

        y->left = x;                                                            // x vira filho à esquerda de y
        x->parent = y;                                                          // atualiza o pai de x para ser y
    }

    void rotateRight(Node** root, Node* y)
    {
        Node* x = y->left;                                                      // x será o novo pai de y após a rotação
        y->left = x->right;                                                     // o filho direito de x vira o filho esquerdo de y

        if (x->right != nullptr)                                                // se x tiver filho direito
            x->right->parent = y;                                               // atualiza o pai desse filho para y

        x->parent = y->parent;                                                  // x assume o pai de y

        // Atualiza o ponteiro do pai de y para apontar para x
        if (y->parent == nullptr)                                               // se y era a raiz
            *root = x;                                                          // x vira a nova raiz
        else if (y == y->parent->right)                                         // se y era filho à direita
            y->parent->right = x;                                               // x vira o novo filho à direita
        else                                                                    // se y era filho à esquerda
            y->parent->left = x;                                                // x vira o novo filho à esquerda

        x->right = y;                                                           // y vira filho à direita de x
        y->parent = x;                                                          // atualiza o pai de y para ser x
    }

    void fixInsert(Node **root, Node* z, BinaryTree *tree)
    {
        while (z->parent != nullptr && z->parent->isRed == RED)                // enquanto o pai de z for vermelho (violação da RBT)
        {
            Node* parent = z->parent;                                          // salva o pai
            Node* grandparent = parent->parent;                                // salva o avô

            if (parent == grandparent->left)                                   // se o pai for filho à esquerda do avô
            {
                Node* uncle = grandparent->right;                              // salva o tio (lado oposto)

                if (uncle != nullptr && uncle->isRed == RED)                   // caso 1: tio vermelho
                {
                    parent->isRed = BLACK;                                     // recolore pai para preto
                    uncle->isRed = BLACK;                                      // recolore tio para preto
                    grandparent->isRed = RED;                                  // recolore avô para vermelho
                    z = grandparent;                                           // sobe para corrigir possíveis violações acima
                }
                else                                                           // tio preto (ou nulo)
                {
                    if (z == parent->right)                                   // caso 2: z é filho à direita do pai
                    {
                        z = parent;                                           // salva o pai
                        rotateLeft(root, z);                                  // rotaciona para transformar no caso 3
                        parent = z->parent;                                   // atualiza o pai
                        grandparent = parent->parent;                         // atualiza o avô
                        tree->rotationsCount ++;
                    }

                    // caso 3: z é filho à esquerda do pai
                    parent->isRed = BLACK;                                    // recolore pai para preto
                    grandparent->isRed = RED;                                 // recolore avô para vermelho
                    rotateRight(root, grandparent);                           // rotação à direita para balancear
                    tree->rotationsCount ++;
                }
            }
            else                                                               // espelho do caso acima (pai é filho à direita)
            {
                Node* uncle = grandparent->left;                              // salva o tio (lado oposto)
                
                if (uncle != nullptr && uncle->isRed == RED)                  // caso 1: tio vermelho
                {
                    parent->isRed = BLACK;                                    // recolore pai para preto
                    uncle->isRed = BLACK;                                     // recolore tio para preto
                    grandparent->isRed = RED;                                 // recolore avô para vermelho
                    z = grandparent;                                          // sobe para corrigir possíveis violações acima
                }
                else                                                          // tio preto (ou nulo)
                {
                    if (z == parent->left)                                   // caso 2: z é filho à esquerda do pai
                    {
                        z = parent;                                          // salva o pai
                        rotateRight(root, z);                                // rotação para transformar no caso 3
                        parent = z->parent;                                  // atualiza o pai
                        grandparent = parent->parent;                        // atualiza o avô
                        tree->rotationsCount ++;
                    }
                    
                    // caso 3: z é filho à direita do pai
                    parent->isRed = BLACK;                                   // recolore pai para preto
                    grandparent->isRed = RED;                                // recolore avô para vermelho
                    rotateLeft(root, grandparent);                           // rotação à esquerda para balancear
                    tree->rotationsCount ++;
                }
            }
        }
        
        (*root)->isRed = BLACK;                                               // a raiz da árvore deve sempre ser preta
    }
}
