#ifndef QUERY2_H
#define QUERY2_H

#include "main.h"
#include "files.h"
#include "database_manager.h"
#include "utils.h"

/**
 * @brief Função de comparação para ordenar artistas por duração de discografia e, em caso de empate, pelo ID.
 * 
 * Esta função é usada para comparar dois artistas com base na duração total de sua discografia. 
 * Caso ambos tenham a mesma duração, a comparação é feita pelo ID do artista.
 * 
 * @param a Apontador para o ID do primeiro artista a ser comparado.
 * @param b Apontador para o ID do segundo artista a ser comparado.
 * @param user_data Apontador para o GHashTable que contém as durações das discografias dos artistas.
 * 
 * @return Um valor inteiro indicando a ordem dos artistas:
 *         - Valor negativo se o primeiro artista deve vir antes.
 *         - Valor positivo se o segundo artista deve vir antes.
 *         - Zero se os dois artistas forem equivalentes.
 */

gint compare_artists(gpointer a, gpointer b, gpointer user_data);

/**
 * @brief Os top N artistas com maior discografia
 * A query recebe como argumento o número de artistas que devem constar do output, podendo ainda
 * receber (ou não) um filtro opcional, o filtro de país, sendo que quando presente só devem ser considerados
 * artistas desse país. Deverá escrever para o ficheiro de resultado os campos que constam do exemplo
 * abaixo. O tamanho da discografia dos artistas é calculado pela soma da duração das suas músicas. Artistas
 * coletivos e individuais devem ser tratados de forma separada, ignorando relações que existam entre eles.
 * Em caso de empate, os artistas devem ser ordenados por ordem crescente de id (i.e., ids mais pequenos
 * devem surgir primeiro)
 * 
 * @param db_manager Apontador para o DataBaseManager
 * @param N número de artistas
 * @param country_filter País em questão
 * @param output Ficheiro que vai escrever a query
 * @param separator
 * 
 */
void query2(Database_Manager *db_manager, int N, char *country_filter, FILE *output, char separator);

#endif
