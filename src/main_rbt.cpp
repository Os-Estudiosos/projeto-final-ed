#include "modules/rbt/rbt.h"
#include "modules/data.h"
#include "utils/tree_utils.h"
#include "utils/utils.h"

#include <iostream>
#include <string>
#include <chrono>
#include <fstream>

using namespace RBT;
using namespace std;

int main(int argc, char* argv[])
{
    if (valCLI(argc, argv)){
        return 0;
    }

    string command_type = argv[1];
    int n_docs = stoi(argv[2]);
    string path = argv[3];

    if (command_type == "search") {
        clearTerminal();

        BinaryTree* tree = create();

        for (int i = 0; i < n_docs; i++) {
            string archive_path = path + to_string(i) + ".txt";
            vector<string> words = readArchive(archive_path);
            
            for (int j = 0; j < words.size(); j++) {
                insert(tree, words[j], i);
            }
        }

        string word_to_search = "";
        int c;

        while(true) {
            cout << "========================\033[96m PESQUISA COM ÍNDICE INVERTIDO \033[m========================" << endl;
            cout << "(Se quiser sair, aperte digite Q e dê enter)" << endl;
            cout << "Digite a palavra que gostaria de procurar:" << endl;
            cout << "--> ";
            cin >> word_to_search;
            cout << endl;

            if (word_to_search == "q" || word_to_search == "Q") {
                cout << "Encerrando o programa" << endl;
                break;
            }

            SearchResult result = search(tree, word_to_search);
            
            if (result.found) {
                cout << "Sua palavra foi \033[92mENCONTRADA\033[m!" << endl;
                cout << "Ela se localiza nos documentos: ";

                for (int d = 0; d < result.documentIds.size(); d++) {
                    cout << result.documentIds[d] << ", ";
                }
                cout << endl;

                cout << "Aperte Enter para procurar outra palavra" << endl;

                cin.ignore();
                cin.get();
            } else {
                cout << "Sua palavra \033[91mnão\033[m foi encontrada :(. Aperte Enter para procurar outra palavra" << endl;
                cin.ignore();
                cin.get();
            }
            clearTerminal();
        }

        destroy(tree);
    } else if (command_type == "stats") {
        BinaryTree* tree = create();

        ofstream InsertingStats("./src/stats/inserting_stats_"+to_string(n_docs)+".csv");

        InsertingStats << "time; comparisions; height; min_height" << endl;

        for (int i = 0; i < n_docs; i++) {
            string archive_path = path + to_string(i) + ".txt";
            vector<string> words = readArchive(archive_path);
            
            for (int j = 0; j < words.size(); j++) {
                InsertResult result = insert(tree, words[j], i);
                int actual_height = computeHeight(tree->root);
                int actual_min_height = computeMinHeight(tree->root);

                cout << result.executionTime << endl;

                InsertingStats << result.executionTime << "; " << result.numComparisons << "; " << actual_height << "; " << actual_min_height << endl;
            }
        }

        InsertingStats.close();

        destroy(tree);
    }

    return 0;
}