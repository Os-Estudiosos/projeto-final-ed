#include "bst.h"
#include "data.h"

namespace BST
{
    BinaryTree *create()
    {
        BinaryTree *tree = new BinaryTree;
        tree->root = nullptr;
        return tree;
    }

    InsertResult insert(BinaryTree *tree, const std::string &word, int documentId)
    {
        auto start = std::chrono::high_resolution_clock::now();

        InsertResult result;
        result.numComparisons = 0;
        result.executionTime = 0;

        if (tree == nullptr)
        {
            return result;
        }

        if (tree->root == nullptr)
        {
            tree->root = new Node;
            tree->root->word = word;
            tree->root->documentIds.push_back(documentId);
            tree->root->parent = nullptr;
            tree->root->left = nullptr;
            tree->root->right = nullptr;
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            double time_ms = duration.count();
            result.executionTime = time_ms;
            return result;
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
                        result.numComparisons += 1;
                        auto end = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                        double time_ms = duration.count();
                        result.executionTime = time_ms;
                        return result;
                    }
                    else
                    {
                        result.numComparisons += 1;
                        current->documentIds.push_back(documentId);
                        auto end = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                        double time_ms = duration.count();
                        result.executionTime = time_ms;
                        return result;
                    }
                }
                else if (word > current->word)
                {
                    result.numComparisons += 1;
                    last = current;
                    current = current->right;
                }
                else
                {
                    result.numComparisons += 1;
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
                result.numComparisons += 1;
                last->right = newNode;
            }
            else
            {
                result.numComparisons += 1;
                last->left = newNode;
            }

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            double time_ms = duration.count();
            result.executionTime = time_ms;
            return result;
        }
    }

    SearchResult search(BinaryTree *tree, const std::string &word);
    void delete_BST(BinaryTree *tree);
}