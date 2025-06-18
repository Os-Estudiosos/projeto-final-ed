#include "modules/avl/avl.h"
#include "modules/data.h"
#include "utils/utils.h"

int main(int argc, char* argv[])
{
    if (valCLI(argc, argv))
    {
        return 0;
    }

    std::string commandType = argv[1];
    int numDocs = std::stoi(argv[2]);
    std::string path = argv[3];

    if (commandType == "search")
    {
        clearTerminal();

        BinaryTree* tree = AVL::create();

        for (int i = 0;i < numDocs;i++)
        {
            std::string archivePath = path + std::to_string(i) + ".txt";
            std::vector<std::string> words = readArchive(archivePath);
            int size = words.size();
            
            for (int j = 0;j < size;j++)
            {
                AVL::insert(tree, words[j], i);
            }
        }

        std::string wordToSearch = "";
    
        while (true)
        {
            std::cout << "========================\033[96m PESQUISA COM INDICE INVERTIDO \033[m========================" << std::endl;
            std::cout << "(Se quiser sair, digite . e de enter)" << std::endl;
            std::cout << "Digite a palavra que gostaria de procurar:" << std::endl;
            std::cout << "--> ";
            std::cin >> wordToSearch;
            std::cout << std::endl;

            if (!strcmp(wordToSearch.c_str(), "."))
            {
                std::cout << "Encerrando o programa" << std::endl;
                break;
            }

            SearchResult result = search(tree, wordToSearch);
            
            if (result.found)
            {
                std::cout << "Sua palavra foi \033[92mENCONTRADA\033[m!" << std::endl;
                std::cout << "Ela se localiza nos documentos: ";
                int size = result.documentIds.size();

                for (int i = 0;i < size - 1;i++)
                {
                    std::cout << result.documentIds[i] << ", ";
                }
                std::cout << result.documentIds[size - 1];

                std::cout << std::endl;
                std::cout << "Aperte Enter para procurar outra palavra" << std::endl;
                std::cin.ignore();
                std::cin.get();
            } else
            {
                std::cout << "Sua palavra \033[91nao\033[m foi encontrada :(. Aperte Enter para procurar outra palavra" << std::endl;
                std::cin.ignore();
                std::cin.get();
            }
            clearTerminal();
        }
        AVL::destroy(tree);

    } else if (commandType == "stats")
    {
        clearTerminal();

        BinaryTree* tree = AVL::create();

        std::filesystem::path pathStats = pathAbsStats();
        std::filesystem::create_directories(pathStats / "avl/");
        std::ofstream InsertingStats(pathStats.string() + "avl/avlInsertStats_" + std::to_string(numDocs) + "archives.csv");

        std::cout << "\033[37mDependendo de quantos documentos você está fazendo a leitura, isso pode levar um tempinho\033[m" << std::endl;
        std::cout << "\033[36mCalculando as estatísticas de Inserção\033[m" << std::endl;

        std::stringstream insertString;
        insertString << "word;time;comparisions;treeHeight;nodes\n";
        
        int comparacoes = 0;
        long long time = 0;
        int cwords = 0;
        int size = 0;
        for (int i = 0;i < numDocs;i++)
        {
            std::string archivePath = path + std::to_string(i) + ".txt";
            std::vector<std::string> words = readArchive(archivePath);
            size = words.size();
            cwords += size;
            for (int j = 0;j < size;j++)
            {
                InsertResult result = AVL::insert(tree, words[j], i);
                insertString << words[j] << ";" << result.executionTime << ";" << result.numComparisons << ";"<< tree->height << ";" << tree->nodeCount << std::endl;
                time +=result.executionTime;
                comparacoes += result.numComparisons;
            }
        }
        
        InsertingStats << insertString.str();
        std::vector<std::string> words;
        int uniqueWords = countNodes(tree, &words);

        std::cout << "=====================\033[36mESTATÍSTICAS DE INSERÇÃO\033[m=====================" << std::endl;
        std::cout << "Tempo de Inserção: " << (float)time/1e9 << " segundos" << std::endl;
        std::cout << "Total de palavras inseridas: " << cwords << std::endl;
        std::cout << "Palavras unicas: " << uniqueWords << std::endl;
        std::cout << "Total de comparacoes: " << comparacoes << std::endl;
        std::cout << "Media de comparacoes: " << (float)comparacoes/cwords << std::endl;
        std::cout << "Altura: " << computeHeight(tree->root) << std::endl;
        std::cout << "Menor altura: " << computeMinHeight(tree->root) << std::endl;
        std::cout << std::endl;

        std::cout << "\033[36mCalculando as estatísticas de Busca\033[m" << std::endl;
        std::ofstream SearchingStats(pathStats.string() + "avl/avlSearchStats_" + std::to_string(numDocs) + "archives.csv");

        std::stringstream searchString;
        searchString << "word;time;comparisions;word_height" << std::endl;

        SearchResult result;
        std::string toSearch;
        long int sumTime = 0;
        int sumComparisons = 0;
        for(int i = 0;i < uniqueWords;i++)
        {
            toSearch = words[i];
            result = search(tree, toSearch);
            sumTime += result.executionTime;
            sumComparisons += result.numComparisons;
            searchString << words[i] << ";" << result.executionTime << ";" << result.numComparisons << ";" << result.numComparisons + 1 << std::endl;
        }

        SearchingStats << searchString.str();

        std::cout << "=====================\033[36mESTATÍSTICAS DE BUSCA\033[m=====================" << std::endl;
        std::cout << "Media tempo de busca: " << (float)sumTime/(uniqueWords*1e9) << " segundos" << std::endl;
        std::cout << "Media de comparacoes de busca: " << (float)sumComparisons/uniqueWords << std::endl;

        InsertingStats.close();
        SearchingStats.close();

        AVL::destroy(tree);
    }
    return 0;
}