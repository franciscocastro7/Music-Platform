#ifndef TEST_H
#define TEST_H

#include "main.h"
#include <time.h>
#include "database_manager.h"
#include "query1.h"
#include "query2.h"
#include "query3.h"
#include "query4.h"
#include "query6.h"
#include <sys/resource.h>


/**
 * @brief Compara o conteúdo de dois arquivos linha por linha.
 * 
 * @param file1 Apontador para o primeiro arquivo.
 * @param file2 Apontador para o segundo arquivo.
 * @param linha Apontador para armazenar a linha onde foi encontrada a diferença.
 * 
 * @return 1 se os arquivos forem iguais, 0 caso contrário.
 */

int compare_files(FILE *file1, FILE *file2, int *linha);



/**
 * @brief Verifica o resultado de uma consulta com base no resultado esperado.
 * 
 * @param counter Número da consulta atual.
 * @param resul_esperados Diretório contendo os resultados esperados.
 * 
 * @return 1 se o resultado for igual ao esperado, 0 caso contrário.
 */

int check(int counter, char *resul_esperados);



/**
 * @brief Exibe uma mensagem indicando que não houve saída para o teste.
 * 
 * @param counter Número do teste.
 */

void noOutput(int counter);



/**
 * @brief Processa uma consulta de teste e salva o resultado no arquivo de saída.
 * 
 * @param command Comando da consulta a ser processada.
 * @param db_manager Apontador para o gerenciador de banco de dados.
 * @param query_id ID da consulta sendo executada.
 * @param output Apontador para o arquivo de saída.
 * @param execution_time Apontador para armazenar o tempo de execução da consulta.
 */

void process_query_test(char *command, Database_Manager *db_manager, int query_id, FILE *output, double *execution_time);



/**
 * @brief Função principal para executar o programa de testes.
 * 
 * Este programa:
 * - Carrega dados dos arquivos CSV fornecidos.
 * - Executa consultas lidas de um arquivo de entrada.
 * - Compara os resultados com os esperados.
 * - Gera relatórios de desempenho e uso de memória.
 * 
 * @param argc Número de argumentos fornecidos ao programa.
 * @param argv Array de strings contendo os argumentos do programa:
 *  - `argv[1]`: Caminho para o diretório contendo os arquivos CSV.
 *  - `argv[2]`: Caminho para o arquivo contendo os comandos de teste.
 *  - `argv[3]`: Caminho para o diretório contendo os resultados esperados.
 * 
 * @return 0 se o programa for executado com sucesso.
 */

int main(int argc, char *argv[]);

#endif