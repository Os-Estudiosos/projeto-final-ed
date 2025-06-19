#pragma once

#include <iostream>
#include <cstring>
#include <filesystem>

/**
* @brief Essa função foi feita para validar os comandos passados pelo terminal.
* @param argc A quantidade de argumentos passados no terminal.
* @param argv A lista dos argumento passados no temrinal.
* @return Retorna true caso algum argumento seja invalido e falso caso estejam todos corretos.
*/
bool valCLI(int argc, char** argv);

/**
 * @brief Limpa o terminal.
 */
void clearTerminal();

/**
 * @brief Imprime no terminal a mensagem recebida.
 * @param message Mensagem a ser impressa.
 * @param breakLine Indica se haverá quebra de linha.
 * @param colorCode Código da cor da mensagem.
 */
void printMessage(std::string message, bool breakLine = 0, std::string colorCode = "");