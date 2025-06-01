#include "../data.h"

void printMessage(std::string message, bool breakLine = 0, std::string color_code = "") {
    std::cout << "\033[" << color_code << "m" << message << "\033[m";
    if (breakLine) std::cout << std::endl;
}

void read_archive_functioning() {
    try {
        printMessage("Testando a leitura de arquivos");
        std::vector<std::string> expectedOutput = {
            "BATATA",
            "BATATA",
            "BETERRABA",
            "ACUCAR",
            "FARINHA",
            "LEITE",
            "CONDENSADO",
            "PIPOCA",
            "BATATA",
            "MACARRAO",
            "GIRAFA",
            "GENGIBRE",
            "LEAO",
            "ZUBUMAFU",
            "Indonesia",
            "escondido",
            "Chico",
            "Buarque",
            "Buchada"
        };

        std::vector<std::string> words = readArchive("/mnt/Github/projeto-final-ed/src/tests/data/0.txt");
        
        for (int i = 0; i < expectedOutput.size(); i++) {
            if (expectedOutput[i] != words[i]) {
                std::cout << std::endl;
                throw std::runtime_error("A função não está lendo o texto corretamente");
            }
        }

        printMessage(" CONCLUÍDO", 1, "92");

    } catch (const std::runtime_error& err) {
        printMessage(" ERRO", 1, "91");
        printMessage(".......", 0);
        printMessage(err.what(), 1);
    }

    try {
        printMessage("Testando a leitura de arquivos vazios");

        std::vector<std::string> words = readArchive("/mnt/Github/projeto-final-ed/src/tests/data/1.txt");
        
        if (words.size() != 1) {
            throw std::runtime_error("A função leu algo que não deveria");
        }

        printMessage(" CONCLUÍDO", 1, "92");

    } catch (const std::runtime_error& err) {
        printMessage(" ERRO", 1, "91");
        printMessage(".......", 0);
        printMessage(err.what(), 1);
    }
}


int main() {
    std::cout << "============== FUNCIONAMENTO DA FUNÇÃO ==============" << std::endl;
    read_archive_functioning();

    return 0;
}
