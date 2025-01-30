#ifndef FILES_H
#define FILES_H

#include "main.h"

/**
 * @brief Abertura de Ficheiros
 * 
 * Função simples cujo objetivo é apenas abrir ficheiros, aloca memoria e abre o ficheiro através do seu path e do seu nome
 * 
 * @param path -> apontador para o caminho para o ficheiro
 * @param filename -> apontador para o nome do ficheiro
 * @return @c FILE*
 */

FILE* open_files(char *path, char *filename);



/**
 * @brief Print do cabeçalho do ficheiro
 * 
 * @param csv
 * @param error_csv
 * @return @c int
 * @note retorna um int (0) caso tudo ocorra conforme esperado, caso contrário devolve 1
 */

int print_header(FILE *csv, FILE *error_csv);

#endif