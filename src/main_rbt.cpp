#include "modules/rbt/rbt.h"
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

        BinaryTree* tree = RBT::create();

        for (int i = 0; i < n_docs; i++) {
            std::string archive_path = path + std::to_string(i) + ".txt";
            std::vector<std::string> words = readArchive(archive_path);
            
            for (int j = 0; j < words.size(); j++) {
                RBT::insert(tree, words[j], i);
            }
        }

        std::string word_to_search = "";
        int c;

        while(true) {
            std::cout << "========================\033[96m PESQUISA COM INDICE INVERTIDO \033[m========================" << std::endl;
            std::cout << "(Se quiser sair, aperte digite . e de enter)" << std::endl;
            std::cout << "Digite a palavra que gostaria de procurar:" << std::endl;
            std::cout << "--> ";
            std::cin >> word_to_search;
            std::cout << std::endl;

            if (word_to_search == "q" || word_to_search == "Q") {
                std::cout << "Encerrando o programa" << std::endl;
                break;
            }

            SearchResult result = RBT::search(tree, word_to_search);
            
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
                std::cout << "Sua palavra \033[91mnao\033[m foi encontrada :(. Aperte Enter para procurar outra palavra" << std::endl;
                std::cin.ignore();
                std::cin.get();
            }
            clearTerminal();
        }

        RBT::destroy(tree);
    } else if (command_type == "stats") {
        BinaryTree* tree = RBT::create();

        std::ofstream InsertingStats("./src/stats/inserting_stats_"+ std::to_string(n_docs)+".csv");

        InsertingStats << "time; comparisions; height; min_height" << std::endl;

        for (int i = 0; i < n_docs; i++) {
            std::string archive_path = path + std::to_string(i) + ".txt";
            std::vector<std::string> words = readArchive(archive_path);
            
            for (int j = 0; j < words.size(); j++) {
                InsertResult result = RBT::insert(tree, words[j], i);
                int actual_height = computeHeight(tree->root);
                int actual_min_height = computeMinHeight(tree->root);

                std::cout << result.executionTime << std::endl;

                InsertingStats << result.executionTime << "; " << result.numComparisons << "; " << actual_height << "; " << actual_min_height << std::endl;
            }
        }

        InsertingStats.close();

        RBT::destroy(tree);
    }

    return 0;
}