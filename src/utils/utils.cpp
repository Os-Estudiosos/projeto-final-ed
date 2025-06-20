#include "utils.h"

void clearTerminal()
{
    std::cout << "\033[2J\033[1;1H";
}

// Função auxiliar para imprimir mensagens formatadas no terminal com opção de cor e quebra de linha
void printMessage(std::string message, bool breakLine, std::string colorCode)
{
    std::cout << "\033[" << colorCode << "m" << message << "\033[m";
    if (breakLine) std::cout << std::endl;
}

bool valCLI(int argc, char** argv)
{
    if(argc != 4 || (strcmp(argv[1],"search") && strcmp(argv[1], "stats")))
    {
        std::cout << "Argumentos invalidos, por favor usar:\n" << argv[0]
        << " search <n_docs> <diretorio> \t \"para realizar busca por palavras\"\n" <<
        argv[0] << " stats <n_docs> <diretorio> \t \"para gerar estatisticas de desempenho\"\n";
        return true;
    }

    // a verificação do diretório pode ocorrer durante a função de leitura, mas podemos simplesmente
    // tentar abrir algum arquivo na pasta e ver se funciona
    FILE *fp;
    std::filesystem::path path = argv[3];
    path = path / "0.txt";
    std::filesystem::path p = std::filesystem::current_path();
    
    // Verifica se o caminho é absoluto
    if(!path.is_absolute())
    {
        path = p / path;        // Concatena o caminho absoluto com o caminho relativo dado
    }

    // Abre o arquivo no modo leitura
    // diferencia windows do linux
    #ifdef _WIN32
        fp = _wfopen(path.wstring().c_str(), L"r");
    #else
        fp = fopen(path.string().c_str(), "r");
    #endif
    
    if (fp == nullptr)
    {
        std::cout << "O diretorio passado, " << argv[3] << " nao e valido, use:\n" <<
        argv[0] << " " <<argv[1] << " " << argv[2] << " <diretorio> \t com um diretorio valido\n";
        return true;
    }
    // fecha o arquivo
    fclose(fp);

    // usando a biblioteca filesystem, contamos quantos arquivos existem na pasta,
    // considerando que eles estão nomeados em ordem crescente de 0 a n (n = quantidade de arquivos) 
    int archivesCount = 0;
    for (const auto& entry : std::filesystem::directory_iterator(argv[3]))
    {
        if (entry.is_regular_file())
        {
            archivesCount++;
        }
    }

    if(atoi(argv[2]) <= 0 || atoi(argv[2]) > archivesCount)
    {
        std::cout << "quantidade de documentos invalidas, por favor use:\n" <<
        argv[0] << " " <<argv[1] << " <n_docs> <diretorio> \t com 0 < n_docs < " << archivesCount << std::endl;
        return true;
    }
    return false;
}