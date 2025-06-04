#pragma once

#include <iostream>
#include <cstring>
#include <filesystem>

/**
*@brief Essa função foi feita para validar os comandos passados pelo terminal.
*@param argc A quantidade de argumentos passados no terminal.
*@param argv A lista dos argumento passados no temrinal.
*@return Retorna true caso algum argumento seja invalido e falso caso estejam todos corretos.
*/
bool valCLI(int argc, char** argv);

void clearTerminal();
