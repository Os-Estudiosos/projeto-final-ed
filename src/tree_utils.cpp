#include "tree_utils.h"


void auxPrint(Node *aux, int *num) {
    std::cout<< *num << ". " << aux->word <<": ";
    std::string toPrint = "";

    for(int i = 0; i < aux->documentIds.size(); i++){
        toPrint += std::to_string(aux->documentIds[i]) + ", ";
    }
    toPrint.erase(toPrint.size() - 2, 2);
    std::cout << toPrint << std::endl;
    *num += 1;

    if(aux->left != nullptr){
        auxPrint(aux->left, num);
    } 
    if(aux->right != nullptr){
        auxPrint(aux->right, num);
    }
}

void printIndex(BinaryTree* tree) {
    Node *aux = tree->root;
    int count = 1;
    
    if(aux != nullptr){
        auxPrint(aux, &count);
    }
}

void auxPrintTree(Node *aux, std::string space){
    if(aux->left != nullptr) {
        std::string folderRep = "├──";
        if(aux->right == nullptr){
            folderRep = "└──";
        }
        std::cout << space << folderRep << aux->left->word << std::endl;
        auxPrintTree(aux->left,space + "   ");
    }
    if(aux->right != nullptr) {
        std::cout << space << "└──" << aux->right->word << std::endl;
        auxPrintTree(aux->right,space + "   ");
    }

}

void printTree(BinaryTree* tree) {
    Node *aux = tree->root;

    if(aux != nullptr){
        std::cout << aux->word << std::endl;
        auxPrintTree(aux, "");
    }
}


Node* createNode(std::string x) 
{
    Node* n = new Node();
    n->documentIds = std::vector<int>{};
    n->word = x;
    n->left = nullptr;
    n->right = nullptr;
    n->parent = nullptr;
    n->height = 0;
    n->isRed = 0;

    return n;
}


BinaryTree* createBinaryTree()
{
    BinaryTree *tree = new BinaryTree;
    tree->root = nullptr;
    return tree;
}


InsertResult insert(BinaryTree *tree, const std::string &word, int documentId)
{
    auto start = std::chrono::high_resolution_clock::now();

    InsertResult result_insert;
    result_insert.numComparisons = 0;
    result_insert.executionTime = 0;

    if (tree == nullptr)
    {
        return result_insert;
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
        result_insert.executionTime = time_ms;
        return result_insert;
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