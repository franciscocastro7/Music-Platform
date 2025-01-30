#ifndef MUSICSMANAGER_H
#define MUSICSMANAGER_H

#include "main.h"
#include "musics.h"
#include "artistsmanager.h"
#include "parser.h"

typedef struct music_manager Music_Manager;
typedef struct artist_manager Artist_Manager;
typedef struct album_manager Album_Manager;



/**
 * @brief Inicializa e preenche o Music Manager a partir de dados parseados.
 * 
 * Esta função processa um array de strings que contem dados das músicas,
 * cria estruturas do tipo Music, e os armazena em uma tabela hash dentro do gerenciador.
 * 
 * @param parsed_musics Array de strings que contem as informações das músicas parseadas.
 * @param artist_manager Apontador para o gerenciador de artistas, usado para validação de músicas.
 * @param album_manager Apontador para o gerenciador de álbuns, usado para validação de músicas.
 * @param musics_errors Arquivo onde os erros encontrados durante o parsing serão registrados.
 * @return Apontador para o Music_Manager inicializado, ou `NULL` em caso de falha.
 * 
 * @note Cada linha no array `parsed_musics` deve estar formatada corretamente para representar uma música.
 */

Music_Manager *ParseMusics(char **parsed_musics, Artist_Manager *artist_manager, Album_Manager *album_manager, FILE *musics_errors);



/**
 * @brief Retorna a Hashtable de Músicas
 * 
 * @param music_manager Apontador para o Music Manager
 * @return Apontador para a Hashtable
*/

GHashTable *get_music_table(Music_Manager *music_manager);



/**
 * @brief Libera a memória
 * 
 * Esta função destrói a Hashtable de músicas e libera a memória associada ao Music_Manager
 * 
 * @param music_manager Apontador para o Music Manager a ser liberado
 */

void free_music_manager(Music_Manager *music_table);

#endif
