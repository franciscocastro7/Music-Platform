#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "main.h"
#include "parser.h"
#include "artists.h"
#include "artistsmanager.h"
#include "musics.h"
#include "musicsmanager.h"
#include "files.h"
#include "query1.h"
#include "query2.h"
#include "database_manager.h"
#include "query3.h"
#include "query4.h"
#include "query6.h"

/**
 * @brief Processa os comandos do arquivo de entrada em modo batch.
 * 
 * Lê cada linha do arquivo de comandos, processa o comando correspondente
 * e chama a função process_query para executar as queries no Database_Manager
 * 
 * @param inputs Apontador para o arquivo de entrada contendo os comandos.
 * @param db_manager Apontador para o Database Manager.
 */

void handle_inputs(FILE *inputs, Database_Manager *db_manager);



/**
 * @brief Processa um comando individual e executa a query correspondente
 * 
 * Divide o comando recebido em partes, identifica o tipo de query a ser executada
 * e chama a função específica correspondente. Os resultados são escritos no terminal
 * ou em um arquivo, dependendo do modo de execução.
 * 
 * @param command String contendo o comando a ser processado.
 * @param db_manager Apontador para o Database Manager.
 * @param count Número do comando (usado para nomear arquivos de saída no modo batch).
 * @param interactive_mode Indica se o comando está sendo executado em modo interativo (true) ou batch (false).
 */

void process_query(char *command, Database_Manager *db_manager, int count, bool interactive_mode);



/**
 * @brief Processa os comandos inseridos pelo usuário em modo interativo.
 * 
 * Lê comandos inseridos no terminal pelo usuário, executa as queries correspondentes
 * e exibe os resultados diretamente no terminal. O modo interativo continua até que o
 * comando "exit" seja inserido.
 * 
 * @param db_manager Apontador para o Database Manager.
 */

void handle_inputs_interactive(Database_Manager *db_manager);

#endif