#ifndef ARTISTSMANAGER_H
#define ARTISTSMANAGER_H

#include "main.h"
#include "artists.h"
#include "parser.h"


typedef struct artist_manager Artist_Manager; // HashTable de Artistas

/**
 * @brief Criar hashtable de Albums
 * 
 * A função tem como objetivo processar um array de strings contendo informações sobre artistas @p parsed_artists e 
 * criar uma estrutura de dados @c Artists_Manager que organiza esses artistas em uma HashTable. A tabela utiliza IDs únicos 
 * dos artistas como chave e as informações do artista como valor.
 * 
 * @param parsed_artists -> Apontador para um array de parsed_albums
 * @param artists_errors -> apontador para um ficheiro de artistas
 * @return @c Artist_Manager
 */

Artist_Manager *ParseArtists(char **parsed_artists, FILE *artists_errors);



/**
 * @brief Função que devolve a Hashtable
 * 
 * @param artist_manager -> Apontador para o manager
 * @return @c GHashtable
 */

GHashTable *get_artist_table(Artist_Manager *artist_manager);



/**
 * @brief Libera memória da Hashtable
 * 
 * @param artist_table -> apontador para uma hashtable de Artistas
 * @return @c NULL
 */

void free_artist_manager(Artist_Manager *artist_table);

#endif 
