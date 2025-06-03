#include "data.h"

std::vector<std::string> readArchive(std::string path){
    char ch;
    std::vector<std::string> data;
    FILE *fp;
    fp = fopen(path.c_str(), "r");

    if (fp == nullptr) {
        std::cerr << "Erro ao abrir o arquivo:" << path <<std::endl;
        exit(1);
    }
    std::string w;
    while ((ch = fgetc(fp)) != EOF) {
        if(ch == ' '){
            data.push_back(w);
            w = "";
            continue;
        }
        w += std::tolower(ch);
    }
    // a ultima palavra termina com o EOF (fim do arquivo), portanto ela não foi adicionada durante o while
    data.push_back(w);
    fclose(fp);
    return data;
}
