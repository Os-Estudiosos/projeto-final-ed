#include "modules/rbt/rbt.h"
#include "modules/data.h"
#include "utils/utils.h"

#include <fstream>
#include <filesystem>


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
            
            for (long unsigned int j = 0; j < words.size(); j++) {
                RBT::insert(tree, words[j], i);
            }
        }

        std::string word_to_search = "";

        while(true) {
            std::cout << "========================\033[96m PESQUISA COM INDICE INVERTIDO \033[m========================" << std::endl;
            std::cout << "(Se quiser sair, digite . e de enter)" << std::endl;
            std::cout << "Digite a palavra que gostaria de procurar:" << std::endl;
            std::cout << "--> ";
            std::cin >> word_to_search;
            std::cout << std::endl;

            if (word_to_search == ".") {
                std::cout << "Encerrando o programa" << std::endl;
                break;
            }

            SearchResult result = search(tree, word_to_search);
            
            if (result.found) {
                std::cout << "Sua palavra foi \033[92mENCONTRADA\033[m!" << std::endl;
                std::cout << "Ela se localiza nos documentos: ";

                for (long unsigned int d = 0; d < result.documentIds.size() - 1; d++) {
                    std::cout << result.documentIds[d] << ", ";
                }
                std::cout << result.documentIds[result.documentIds.size() - 1];
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
        clearTerminal();

        BinaryTree* tree = RBT::create();

        std::filesystem::create_directories("./build/stats/RBT/");
        std::ofstream InsertingStats("./build/stats/RBT/RBTInsertStats_"+std::to_string(n_docs)+"archives.csv");

        std::cout << "\033[37mDependendo de quantos documentos você está fazendo a leitura, isso pode levar um tempinho\033[m" << std::endl;
        std::cout << "\033[36mCalculando as estatísticas de Inserção\033[m" << std::endl;

        std::stringstream insert_string;
        insert_string << "word;time;comparisions\n";
        
        int comparacoes = 0;
        long int time = 0;
        int cwords = 0;
        int c = 0;
        for (int i = 0; i < n_docs; i++) {
            // if std::cout<<"Documento "<<i<<"\n";
            std::string archive_path = path + std::to_string(i) + ".txt";
            std::vector<std::string> words = readArchive(archive_path);
            c = words.size();
            cwords += c;

            for (long unsigned int j = 0; j < words.size(); j++) {
                InsertResult result = RBT::insert(tree, words[j], i);
                // int actual_height = computeHeight(tree->root);
                // int actual_min_height = computeMinHeight(tree->root);
                insert_string << words[j] << "; " << result.executionTime << "; " << result.numComparisons << std::endl;

                time +=result.executionTime;
                comparacoes += result.numComparisons;
            }
        }
        
        InsertingStats << insert_string.str();

        std::vector<std::string> words;
        int uwords = countNodes(tree, &words);

        std::cout << "=====================\033[36mESTATÍSTICAS DE INSERÇÃO\033[m=====================" << std::endl;
        std::cout << "Tempo de Inserção: " << (float)time/1e9 << " segundos" << std::endl;
        std::cout << "Total de palavras inseridas: " << cwords << std::endl;
        std::cout << "Palavras unicas: " << uwords << std::endl;
        std::cout << "Total de comparacoes: " << comparacoes << std::endl;
        std::cout << "Media de comparacoes: " << (float)comparacoes/cwords << std::endl;
        std::cout << "Altura: " << tree->height <<std::endl;
        std::cout << "Menor altura: " << computeMinHeight(tree->root) << std::endl;
        std::cout << std::endl;

        std::cout << "\033[36mCalculando as estatísticas de Busca\033[m" << std::endl;
        std::ofstream SearchingStats("./build/stats/rbt/rbtSearchStats_"+std::to_string(n_docs)+"archives.csv");

        std::stringstream search_string;
        search_string << "word; time; comparisions; word_height" << std::endl;

        SearchResult result;
        std::string toSearch;
        long int stime = 0;
        int scomp = 0;
        for(int i = 0; i < uwords; i++){
            toSearch = words[i];
            result = search(tree, toSearch);
            stime += result.executionTime;
            scomp += result.numComparisons;

            search_string << words[i] << "; " << result.executionTime << "; " << result.numComparisons << "; " << result.numComparisons+1 << std::endl;
        }

        SearchingStats << search_string.str();

        std::cout << "=====================\033[36mESTATÍSTICAS DE BUSCA\033[m=====================" << std::endl;
        std::cout << "Media tempo de busca: " << (float)stime/(uwords*1e9) << " segundos" << std::endl;
        std::cout << "Media de comparacoes de busca: " << (float)scomp/uwords << std::endl;

        InsertingStats.close();
        SearchingStats.close();
        RBT::destroy(tree);
    }

    return 0;
}