#ifndef PARSER_H
#define PARSER_H

#include "main.h"

/**
 * @brief Parseia um arquivo CSV e armazena cada linha como uma string em um array dinâmico.
 * 
 * Esta função lê um arquivo CSV linha por linha, remove o caractere de nova linha (`\n`) 
 * e armazena cada linha em um array dinâmico. Caso a quantidade de linhas exceda o tamanho
 * inicial do array, o espaço é automaticamente realocado para comportar mais dados.
 * 
 * @param csv Apontador para o arquivo CSV a ser parseado.
 * @return Um array dinâmico de strings contendo cada linha do CSV ou `NULL` em caso de erro.
 */

char **ParseCSV(FILE *csv);



/**
 * @brief Libera a memória alocada para um array de strings gerado pelo ParseCSV
 * 
 * Esta função percorre o array de strings, liberando a memória de cada string individualmente
 * antes de liberar o próprio array
 * 
 * @param parser Apontador para o array de strings a ser liberado
 * 
 * @note A função não faz nada se o ponteiro fornecido for NULL
 */

void free_parser(char ** parser);

#endif