#include "data.h"

std::vector<std::string> readArchive(std::filesystem::path path)
{
    std::filesystem::path p = std::filesystem::current_path();
    
    // Verifica se o caminho é absoluto
    if(!path.is_absolute())
    {
        path = p / path;        // Concatena o caminho absoluto com o caminho relativo dado
    }
    
    std::vector<std::string> data;
    FILE *fp;
    
    // Abre o arquivo no modo leitura
    // diferencia windows do linux
    #ifdef _WIN32
        fp = _wfopen(path.wstring().c_str(), L"r");
    #else
        fp = fopen(path.string().c_str(), "r");
    #endif

    // Caso dê problema retorna erro informando qual arquivo não foi possível ler
    if (fp == nullptr) 
    {
        std::cerr << "Erro ao abrir o arquivo:" << path <<std::endl;
        exit(1);
    }
    std::string w;
    
    // Junta os char do arquivos para formar palavras
    char ch; // Variável auxiliar
    while ((ch = fgetc(fp)) != EOF) 
    {
        if(ch == ' ') // Quando encontrar um espaço a palavra termina
        {                  
            data.push_back(w);
            w = "";
            continue;
        }
        w += std::tolower(ch);
    }

    // A ultima palavra termina com o EOF (fim do arquivo), portanto ela não foi adicionada durante o while
    data.push_back(w);
    fclose(fp);
    return data;
}

std::filesystem::path pathAbsStats() 
{
    std::filesystem::path atual = std::filesystem::current_path();
    std::filesystem::path caminhoBuild;

    // Procura no caminho atual a pasta "build"
    for (auto it = atual.begin(); it != atual.end(); ++it) 
    {
        caminhoBuild /= *it;
        if (*it == "build") 
        {
            break;
        }
    }

    // Se "build" não foi encontrada, considera que estamos no diretorio raiz do projeto
    if (caminhoBuild.filename() != "build") 
    {
        caminhoBuild = atual / "build";
    }

    // Termina de montar o caminho absoluto e retorna
    std::filesystem::path caminhoFinal = caminhoBuild / "stats/";
    return std::filesystem::absolute(caminhoFinal);
}