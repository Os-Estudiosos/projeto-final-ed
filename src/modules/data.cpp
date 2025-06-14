#include "data.h"


std::vector<std::string> readArchive(std::string spath){
    std::filesystem::path path = spath;
    std::filesystem::path p = std::filesystem::current_path();
    if(!path.is_absolute()){
        path = p / path;
        std::cout << path <<std::endl;
    }
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

std::filesystem::path pathAbsStats() {
    std::filesystem::path atual = std::filesystem::current_path();
    std::filesystem::path caminhoBuild;

    // Procura no caminho atual a pasta "build"
    for (auto it = atual.begin(); it != atual.end(); ++it) {
        caminhoBuild /= *it;
        if (*it == "build") {
            break;
        }
    }

    if (caminhoBuild.filename() != "build") {
        // Se "build" não foi encontrada, considera que estamos no diretorio raiz do projeto
        caminhoBuild = atual / "build";
    }

    std::filesystem::path caminhoFinal = caminhoBuild / "stats/";
    return std::filesystem::absolute(caminhoFinal);
}