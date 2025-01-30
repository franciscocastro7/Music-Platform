#ifndef ALBUMSMANAGER_H
#define ALBUMSMANAGER_H

#include "main.h"
#include "albums.h"
#include "artistsmanager.h"
#include "parser.h"

typedef struct album_manager Album_Manager; // Estrutura de uma Hashtable de Albuns


/**
 * @brief Criar hashtable de Albums
 * 
 * A função tem como objetivo processar um array de strings contendo informações sobre álbuns @p parsed_albums e 
 * criar uma estrutura de dados @c Album_Manager que organiza esses álbuns em uma HashTable. A tabela utiliza IDs únicos 
 * dos álbuns como chave e as informações do álbum como valor.
 * 
 * @param parsed_albums -> Apontador para um array de parsed_albums
 * @param artist_table -> apontador para uma hashtable de Artistas
 * @return @c Album_Manager
 */

Album_Manager *ParseAlbums(char **parsed_albums, Artist_Manager *artist_table);



/**
 * @brief Função precaução
 * 
 * Esta função serve para caso o album_manager seja NULL o programa nao dar segmentation fault, de resto devolve a hashtable
 * normalmente.
 * 
 * @param album_manager -> Apontador para o manager
 * @return @c GHashtable
 */

GHashTable *get_album_table(Album_Manager *album_manager);



/**
 * @brief Libera memória da Hashtable
 * 
 * @param album_table -> apontador para uma hashtable de Albuns
 * @return @c NULL
 */

void free_album_manager(Album_Manager *album_table);


#endif