#ifndef UTILS_H
#define UTILS_H
#include "main.h"

void remove_quotes(char *str);
void remove_brackets(char *str);

/**
 * @brief Calcula a duração total em segundos a partir de uma string no formato "hh:mm:ss".
 * 
 * Esta função recebe uma string representando a duração no formato "hh:mm:ss" e converte
 * para um valor inteiro, que é o total de segundos. Se o formato estiver incorreto, a função retorna -1.
 * 
 * @param duration A string que contem a duração no formato "hh:mm:ss".
 * 
 * @return O total de segundos representado pela duração fornecida, ou -1 se o formato for inválido.
 * 
 * @example
 * int total_seconds = calculate_duration("02:30:45"); // Resultado: 9045
 */

char *format_duration(int total_seconds);

int duration_to_seconds(char *duration);

int artist_id_igual(char **artists_ids, char *artist_id);

int get_year(char *timestamp);

int ordena_artists_id(gconstpointer a, gconstpointer b);

#endif 