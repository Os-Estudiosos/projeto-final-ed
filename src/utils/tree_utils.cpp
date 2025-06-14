#include "tree_utils.h"

int computeHeight(Node *node) {
    if (node == nullptr) return 0;                                          // Se o nó é vazio, para
    int left_height = computeHeight(node->left);                            // Recursão para a esquerda
    int right_height = computeHeight(node->right);                          // Recursão para a direita 
    
    if (left_height >= right_height) {                                      // Checagem se a altura da esquerda é maior do que a direita
        return left_height + 1;                                             // Retorna a altura da árvore
    } else {
        return right_height + 1;                                            // Retorna a altura da árvore
    }
}

int computeMinHeight(Node* node) {
    if (node == nullptr) return 0;                                          // Se o nó é vazio, para        
    if (node->left == nullptr && node->right == nullptr) return 1;          // Se apenas não há filhos, retorna 1

    if (node->left == nullptr) return computeMinHeight(node->right) + 1;    // Se o filho à esquerda é inexistente, então aplica a recursão para o filho à direita
    if (node->right == nullptr) return computeMinHeight(node->left) + 1;    // Se o filho à esquerda é inexistente, então aplica a recursão para o filho à direita

    int h_left = computeMinHeight(node->left);                              // Aplica a recursão para o filho da esquerda
    int h_right = computeMinHeight(node->right);                            // Aplica a recursão para o filho da direita

    if (h_left >= h_right) {                                                // Decide qual dos filhos possuem o nó com a maior altura
        return h_right + 1;
    } else {
        return h_left + 1;
    }
}

void deleteNode(Node *node)
{
    if (node == nullptr)                            // caso o nó a ser deletado seja nulo
    {
        return;                                     // nada acontece
    }
    else                                            // caso não seja nulo, então há algo a deletar
    {
        deleteNode(node->left);                     // então chamo a mesma função para deletar seus filhos
        deleteNode(node->right);                    // a mesma coisa acontece para os filhos dos filhos, e assim sucessivamente, até que, 
                                                    // primeiramente, as folhas sejam deletadas, e então seus pais, até a raiz  
        delete node;                                // deleta o nó atual
    }   

}

void auxPrint(Node *aux, int *num) {
    std::cout<< *num << ". " << aux->word <<": ";
    std::string toPrint = "";
    int size = aux->documentIds.size();
    // Armazena todos os ids referentes a uma palavras em uma string
    for(int i = 0; i < size; i++){
        toPrint += std::to_string(aux->documentIds[i]) + ", ";
    }
    // Apaga os dois ultimos elementos da string formada acima
    toPrint.erase(toPrint.size() - 2, 2);

    std::cout << toPrint << std::endl;

    // Acrescenta na contagem de palavras
    *num += 1;

    // Chama de forma recursiva para imprimir os próximos nós
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
    
    // Chama a função auxPrint para que imprima os indices
    if(aux != nullptr){
        auxPrint(aux, &count);
    }
}

void auxPrintTree(Node *aux, std::string space){
    if(aux->left != nullptr) {
        std::cout << space << "|--" << aux->left->word << std::endl;
        auxPrintTree(aux->left,space + "|  ");
    }
    if(aux->right != nullptr) {
        std::cout << space << "|--" << aux->right->word << std::endl;
        
        int n = space.size();
        std::string space2 = "";
        std::string tmp = "";
        int c = 0;

        // Encontra o | e o apaga para que faça sentido seu uso quando não existirá mais um nó irmão
        for(int i = n; i > -1; i++){
            tmp = "";
            tmp += space[i];
            if(strcmp(tmp.c_str(), "|")){
                c = i;
                break;
            }
        }
        
        for(int i = 0; i < c ; i++){
            space2 += space[i];
        }
        for(int i = 0; i < n-c; i++){
            space2 += " ";
        }
        
        // Continua de forma recursiva com o espaço correto
        auxPrintTree(aux->right,space2 + "   ");
    }

}

void printTree(BinaryTree* tree) {
    Node *aux = tree->root;
    // Usa auxPrintTree para fazer a impressão da arvore
    if(aux != nullptr){
        std::cout << aux->word << std::endl;
        auxPrintTree(aux, "");
    }
}

int countNodes(BinaryTree* tree, std::vector<std::string> *words) {
    if(tree == nullptr){
        return -1;
    }
    Node *aux = tree->root;
    int count = 1;
    // usa countNodesAux para contar a quantidade de nós e armazenar a quantidade de palavras
    if(aux != nullptr){
        words->push_back(aux->word);
        countNodesAux(aux, &count, words, 0, tree);
    }
    return count;
}

void countNodesAux(Node *aux, int *num, std::vector<std::string> *words, int height, BinaryTree* tree) {
    *num += 1;
    height += 1;
    // Calcula a altura da arvore e caso seja maior que a atual, atualiza para a estrutura
    if (tree->height < height)
    {
        tree->height = height;
    }

    // Salva as palavras de cada nó no vetor e continua assim de forma recursiva
    if(aux->left != nullptr){
        words->push_back(aux->word);
        countNodesAux(aux->left, num, words, height, tree);
    } 
    if(aux->right != nullptr){
        words->push_back(aux->word);
        countNodesAux(aux->right, num, words, height, tree);
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

bool contains(const std::vector<int>& vec, int value) {
    for (size_t i = 0; i < vec.size(); ++i) {                               // Processo de iteração do loop
        if (vec[i] == value) {                                              // Se encontrar o valor no vetor, retorna verdade
            return true;
        }
    }
    return false;                                                           // Não encontrou, então retorna false
}