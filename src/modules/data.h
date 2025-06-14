#pragma once

#include <iostream>
#include <vector>
#include <cstring>
#include <filesystem>
#include <fstream>

/**
* @brief Garantindo que nenhuma letra será maiuscula, acrescenta todas elas em um vetor de string.
* @param path O caminho indicando qual arquivo será aberto.
* @return Retorna um vetor com as palavras presentes no arquivo.
* @note A função considera como palavra qualquer sequencia de char separados por espaços.
*/
std::vector<std::string> readArchive(std::string path);

/**
 * @brief verifica a estrutura correta para gerar o caminho correto para build/stats
 * @return retorna o caminho absoluto correto para criar a pasta
 */
std::filesystem::path pathAbsStats();