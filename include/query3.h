#ifndef QUERY3_H
#define QUERY3_H

#include "database_manager.h"
#include <stdio.h>

/**
 * @brief Converte um array de strings para uma lista ligada (GList).
 * 
 * Esta função converte um array de strings para uma lista ligada
 * do tipo `GList`. Cada elemento da lista contém uma cópia de uma string do array original.
 * 
 * @param array O array de strings a ser convertido.
 * 
 * @return A lista ligada resultante, onde cada elemento é uma cópia de uma string do array.
 */

GList *array_to_glist(char **array);



/**
 * @brief Função de comparação para ordenar géneros de música com base no número de gostos.
 * 
 * Esta função é usada para comparar dois géneros de música com base no número de gostos. 
 * Se os géneros tiverem o mesmo número de gostos, a comparação é feita lexicograficamente pelo nome do género.
 * 
 * @param a Apontador para o primeiro género de música a ser comparado.
 * @param b Apontador para o segundo género de música a ser comparado.
 * @param user_data Apontador para o `GHashTable` contendo os números de gostos de cada género.
 * 
 * @return Um valor inteiro indicando a ordem dos géneros:
 *         - Valor negativo se o primeiro género deve vir antes.
 *         - Valor positivo se o segundo género deve vir antes.
 *         - Zero se os dois géneros forem equivalentes.
 */


gint compare_genres(const void *a, const void *b, gpointer user_data);


/**
 * @brief Realiza uma consulta para contar o número de gostos por género, para usuários dentro de uma faixa etária.
 * 
 * Esta função realiza a consulta de todos os usuários dentro de uma faixa etária especificada, coleta os géneros de 
 * música que eles mais gostaram e imprime a quantidade de gostos por género, ordenada do mais popular para o menos popular.
 * 
 * @param db_manager
 * @param min_age A idade mínima para os usuários considerados na consulta.
 * @param max_age A idade máxima para os usuários considerados na consulta.
 * @param output O arquivo de saída onde os resultados serão impressos.
 * @param separator O caractere separador a ser usado no formato de saída.
 * 
 * @example
 * query3(db_manager, 18, 25, output, ',');
 */
void query3(Database_Manager *db_manager, int min_age, int max_age, FILE *output, char separator);



/**
 * @brief Libera a memória alocada para um array de IDs de músicas curtidas por um usuário.
 * 
 * Esta função percorre o array de IDs de músicas curtidas e libera a memória de cada elemento.
 * Após isso, libera o array em si.
 * 
 * @param liked_musics_id O array de IDs de músicas curtidas a ser liberado.
 */

void free_user_liked_musics_id(char **liked_musics_id);



#endif
