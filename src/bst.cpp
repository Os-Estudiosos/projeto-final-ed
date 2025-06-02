#include "bst.h"
#include "data.h"
#include "tree_utils.h"

namespace BST
{
    BinaryTree *create()
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

        if (tree == nullptr)                                                    // verifico se a árvore é nula
        {                                                                       // se for, apenas retorno a estrutura de insert inicial (tudo 0)
            return result_insert;                                               
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
        else
        {
            Node *current = tree->root;
            Node *last = nullptr;
            while (current != nullptr)
            {
                if (word == current->word)
                {
                    // assume documentIds não vazio, pois nó existente sempre tem pelo menos um ID.
                    if (current->documentIds.back() == documentId)
                    {
                        result_insert.numComparisons += 1;
                        auto end = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                        double time_ms = duration.count();
                        result_insert.executionTime = time_ms;
                        return result_insert;
                    }
                    else
                    {
                        result_insert.numComparisons += 1;
                        current->documentIds.push_back(documentId);
                        auto end = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                        double time_ms = duration.count();
                        result_insert.executionTime = time_ms;
                        return result_insert;
                    }
                }
                else if (word > current->word)
                {
                    result_insert.numComparisons += 1;
                    last = current;
                    current = current->right;
                }
                else
                {
                    result_insert.numComparisons += 1;
                    last = current;
                    current = current->left;
                }
            }

            Node *newNode = new Node;
            newNode->parent = last;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->documentIds.push_back(documentId);
            newNode->word = word;

            if (word > last->word)
            {
                result_insert.numComparisons += 1;
                last->right = newNode;
            }
            else
            {
                result_insert.numComparisons += 1;
                last->left = newNode;
            }

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            double time_ms = duration.count();
            result_insert.executionTime = time_ms;
            return result_insert;
        }
    }

    SearchResult search(BinaryTree *tree, const std::string &word)
    {
        auto start = std::chrono::high_resolution_clock::now();

        SearchResult result_search;
        result_search.found = 0;
        result_search.numComparisons = 0;
        result_search.executionTime = 0;
        result_search.documentIds = std::vector<int>{};

        if (tree == nullptr)
        {
            return result_search;
        }

        if (tree->root == nullptr)
        {
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            double time_ms = duration.count();
            result_search.executionTime = time_ms;
            return result_search;
        }
        else
        {
            Node *current = tree->root;
            while (current != nullptr)
            {
                if (word == current->word)
                {
                    result_search.numComparisons += 1;
                    result_search.found = 1;
                    result_search.documentIds = current->documentIds;
                    auto end = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                    double time_ms = duration.count();
                    result_search.executionTime = time_ms;
                    return result_search;
                }
                else if (word > current->word)
                {
                    result_search.numComparisons += 1;
                    current = current->right;
                }
                else
                {
                    result_search.numComparisons += 1;
                    current = current->left;
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            double time_ms = duration.count();
            result_search.executionTime = time_ms;
            return result_search;
        }
    }

    void destroy(BinaryTree *tree)
    {
        if (tree == nullptr)
        {
            return;
        }
        else if (tree->root == nullptr)
        {
            delete tree;
            return;
        }
        else
        {
            Node *root = tree->root;
            deleteNode(root);
            delete tree;
        }
    }
}