#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdbool.h>
#include "main.h"
#include "musics.h"
#include "artists.h"
#include "artistsmanager.h"
#include "musicsmanager.h"
#include "users.h"
#include "usersmanager.h"
#include "albumsmanager.h"

typedef struct artist Artist;
typedef struct music Music;
typedef struct user User;
typedef struct album Album;



/**
 * @brief Valida se um artista individual é válido.
 * 
 * Verifica se o tipo de artista é "individual" e se o número de constituintes é zero,
 * retornando 1 se válido e 0 caso contrário.
 * 
 * @param type String representando o tipo do artista ("individual" ou "group").
 * @param id_constituent Apontador para um array de IDs de constituintes do artista.
 * @param constituent_count Número de constituintes associados ao artista.
 * @return 1 se o artista individual for válido, 0 caso contrário.
 */

int is_individual_artist_valid(char *type, char **id_constituent, int constituent_count);



/**
 * @brief Valida os artistas associados a uma música.
 * 
 * Verifica se todos os IDs de artistas associados à música existem na tabela de artistas.
 * Libera os recursos alocados após a validação.
 * 
 * @param music Apontador para a estrutura `Music` representando a música a ser validada.
 * @param artist_table Apontador para o gerenciador de artistas.
 * @return -1 se os IDs de artistas forem inválidos, 1 se algum artista não existir, 0 se todos os artistas forem válidos.
 */

int validate_music_artists(Music *music, Artist_Manager *artist_table);



/**
 * @brief Valida as músicas curtidas por um usuário.
 * 
 * Verifica se todos os IDs de músicas curtidas por um usuário existem na tabela de músicas.
 * Libera os recursos alocados após a validação.
 * 
 * @param user Apontador para o User representando o usuário a ser validado.
 * @param music_table Apontador para o gerenciador de músicas.
 * @return 1 se alguma música não existir na tabela, 0 se todas as músicas forem válidas.
 */

int validate_user_liked_musics(User *user, Music_Manager *music_table);



/**
 * @brief Valida o álbum associado a uma música.
 * 
 * Verifica se o ID do álbum associado à música existe na tabela de álbuns.
 * Libera os recursos alocados após a validação.
 * 
 * @param music Apontador para o objeto `Music` representando a música a ser validada.
 * @param album_table Apontador para o gerenciador de álbuns.
 * @return -1 se o ID do álbum for inválido, 1 se o álbum não existir na tabela, 0 se o álbum for válido.
 */

int validate_music_album(Music *music, Album_Manager *album_table);



/**
 * @brief Verifica se uma duração no formato "hh:mm:ss" é válida.
 * 
 * A função valida se a string fornecida segue o formato "hh:mm:ss" e se os valores de 
 * horas, minutos e segundos estão dentro dos intervalos permitidos.
 * 
 * @param duration Apontador para uma string representando a duração a ser validada.
 *                 O formato esperado é "hh:mm:ss".
 * @return `true` se a duração for válida, `false` caso contrário.
 * 
 * @note
 * - Horas devem estar no intervalo de 0 a 99.
 * - Minutos e segundos devem estar no intervalo de 0 a 59.
 * - Strings nulas ou mal formatadas não são válidas.
 * 
 * @example
 * - is_valid_duration("02:30:45") retorna `true`.
 * - is_valid_duration("99:59:59") retorna `true`.
 * - is_valid_duration("25:61:00") retorna `false` (minutos inválidos).
 * - is_valid_duration(NULL) retorna `false` (string nula).
 */

bool is_valid_duration(const char *duration);


/**
 * @brief Verifica se uma data fornecida está no formato válido e dentro de um intervalo de tempo aceitável.
 * 
 * O formato aceito para a data é "YYYY/MM/DD", onde:
 * - YYYY é o ano (quatro dígitos).
 * - MM é o mês (dois dígitos, de 01 a 12).
 * - DD é o dia (dois dígitos, de 01 a 31).
 * 
 * Além disso, a data não pode ser futura em relação à data atual
 * 
 * @param date Apontador para uma string que contem a data a ser validada.
 * @return `true` se a data for válida, ou `false` caso contrário.
 */

bool is_valid_date(char *date);



/**
 * @brief Valida um endereço de e-mail baseado em regras simples de sintaxe
 * 
 * @param email Apontador para uma string contendo o endereço de e-mail a ser validado.
 * @return `true` se o e-mail for válido, ou `false` caso contrário.
 */

bool is_valid_email(char *email);



/**
 * @brief Converte uma string para letras minúsculas.
 * 
 * Esta função percorre a string fornecida e converte todos os caracteres alfabéticos 
 * para suas respectivas letras minúsculas.
 * 
 * @param str Apontador para a string que será modificada. A string deve ser terminada em `\0`.
 */

void to_lowercase(char *str);

#endif


