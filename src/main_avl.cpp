#include "modules/avl/avl.h"
#include "modules/data.h"
#include "utils/utils.h"

#include <fstream>


int main(int argc, char* argv[])
{
    if (valCLI(argc, argv)){
        return 0;
    }

    std::string command_type = argv[1];
    int n_docs = std::stoi(argv[2]);
    std::string path = argv[3];

    if (command_type == "search") {
        clearTerminal();

        BinaryTree* tree = AVL::create();


        for (int i = 0; i < n_docs; i++) {
            std::string archive_path = path + std::to_string(i) + ".txt";
            std::vector<std::string> words = readArchive(archive_path);
            
            for (int j = 0; j < words.size(); j++) {
                AVL::insert(tree, words[j], i);
            }
        }
        printTree(tree);

        std::string word_to_search = "";
        while(true) {
            std::cout << "========================\033[96m PESQUISA COM INDICE INVERTIDO \033[m========================" << std::endl;
            std::cout << "(Se quiser sair, aperte digite . e de enter)" << std::endl;
            std::cout << "Digite a palavra que gostaria de procurar:" << std::endl;
            std::cout << "--> ";
            std::cin >> word_to_search;
            std::cout << std::endl;

            if (!strcmp(word_to_search.c_str(),".")) {
                std::cout << "Encerrando o programa" << std::endl;
                break;
            }

            SearchResult result = AVL::search(tree, word_to_search);
            
            if (result.found) {
                std::cout << "Sua palavra foi \033[92mENCONTRADA\033[m!" << std::endl;
                std::cout << "Ela se localiza nos documentos: ";

                for (int d = 0; d < result.documentIds.size(); d++) {
                    std::cout << result.documentIds[d] << ", ";
                }
                std::cout << std::endl;

                std::cout << "Aperte Enter para procurar outra palavra" << std::endl;

                std::cin.ignore();
                std::cin.get();
            } else {
                std::cout << "Sua palavra \033[91nao\033[m foi encontrada :(. Aperte Enter para procurar outra palavra" << std::endl;
                std::cin.ignore();
                std::cin.get();
            }
            clearTerminal();
        }

        AVL::destroy(tree);
    } else if (command_type == "stats") {
        BinaryTree* tree = AVL::create();

        std::ofstream InsertingStats("./src/stats/inserting_stats_"+ std::to_string(n_docs)+".csv");

        InsertingStats << "time; comparisions; height; min_height" << std::endl;

        int comparacoes = 0;
        long int time = 0;
        int cwords = 0;
        int c = 0;
        for (int i = 0; i < n_docs; i++) {
            std::string archive_path = path + std::to_string(i) + ".txt";
            std::vector<std::string> words = readArchive(archive_path);
            c = words.size();
            cwords += c;
            for (int j = 0; j < c; j++) {
                InsertResult result = AVL::insert(tree, words[j], i);      
                time +=result.executionTime;
                comparacoes += result.numComparisons;
            }
        }
        std::vector<std::string> words;
        int uwords = countNodes(tree, &words);
        std::cout << "Tempo de execucao: " << (float)time/1e9 << std::endl;
        std::cout << "Total de palavras inseridas: " << cwords << std::endl;
        std::cout << "Palavras unicas: " << uwords << std::endl;
        std::cout << "Total de comparacoes: " << comparacoes << std::endl;
        std::cout << "Media de comparacoes: " << (float)comparacoes/cwords << std::endl;
        //std::cout << "Altura: " << computeHeight(tree) << std::endl;
        //std::cout << "Menor altura: " << computeMinHeight(tree) << std::endl;
        SearchResult result;
        std::string toSearch;
        long int stime = 0;
        int scomp = 0;
        for(int i = 0; i < uwords; i++){
            toSearch = words[i];
            result = AVL::search(tree, toSearch);
            stime += result.executionTime;
            scomp += result.numComparisons;
            std::cout << toSearch << ":  " << result.numComparisons << std::endl; 
        }
        std::cout << "Media tempo de busca: " << (float)stime/(uwords*1e9) << std::endl;
        std::cout << "Media de comparacoes de busca: " << (float)scomp/uwords << std::endl;

        InsertingStats.close();

        AVL::destroy(tree);                                                
        }


    return 0;
}