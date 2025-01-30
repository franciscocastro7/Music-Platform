#ifndef QUERY1_H
#define QUERY1_H

#include "main.h"
#include "users.h"
#include "artists.h"
#include "files.h"
#include "database_manager.h"


/**
 * @brief Executa a Query 1: Retorna informações sobre um user user ou artista especificado.
 * 
 * Listar o resumo de um utilizador ou artista, consoante o identificador recebido por argumento. 
 * A query recebe como argumento o identificador único de um utilizador ou artista, sendo garantido
 * que não existem identificadores repetidos entre as diferentes entidades. Deverá ser retornada uma
 * linha vazia caso o id não conste do sistema
 * 
 * @param db_manager Apontador para o Database Manager
 * @param user_id String que contem o ID do usuário a ser pesquisado.
 * @param output Apontador para o arquivo onde o resultado será escrito.
 * @param separator Caractere utilizado para separar os campos na saída.
 */

void query1(Database_Manager *db_manager, char *user_id, char *artist_id, FILE *output, char separator);

#endif
