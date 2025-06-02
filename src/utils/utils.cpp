#include "utils.h"

bool valCLI(int argc, char** argv){
    if(argc != 4 || (strcmp(argv[1],"search") && strcmp(argv[1], "stats"))){
        std::cout<<"Argumentos invalidos, por favor usar:\n"<< argv[0]
        << " search <n_docs> <diretorio> \t \"para realizar busca por palavras\"\n" <<
        argv[0] <<" stats <n_docs> <diretorio> \t \"para gerar estatisticas de desempenho\"\n";
        return true;
    }
    if(atoi(argv[2]) <= 0 || atoi(argv[2]) >10103){
        std::cout<<"quantidade de documentos invalidas, por favor use:\n" <<
        argv[0] << " " <<argv[1] << " <n_docs> <diretorio> \t com 0 < n_docs < 10103\n";
        return true;
    }
    // a verificação do diretório pode ocorrer durante a função de leitura, mas podemos simplesmente
    // tentar abrir algum arquivo na pasta e ver se funciona
    FILE *fp;
    std::string path = argv[3];
    path += "0.txt";
    fp = fopen(path.c_str(), "r");
    if (fp == nullptr) {
        std::cout<<"O diretório passado, "<< argv[3]<<" não é valido, use:\n" <<
        argv[0] << " " <<argv[1] << " " << argv[2] << " <diretorio> \t com um diretório válido\n";
        return true;
    }
    fclose(fp);
    return false;
}

int main(int argc, char** argv){
    if(valCLI(argc, argv)){
        std::cout<<"Argumentos errados"<<std::endl;
        return 1;
    }

    std::cout<<"Argumentos ok"<<std::endl;
    return 0;
}