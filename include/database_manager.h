#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include "artistsmanager.h"
#include "musicsmanager.h"
#include "albumsmanager.h"
#include "usersmanager.h"
#include "historymanager.h"


typedef struct database_manager Database_Manager; // Estrutura do Database_Manager

/**
 * @brief Função que Cria e Inicializa o Database_Manager
 * 
 * A função create_database_manager é responsável por criar e inicializar um objeto Database_Manager, que gerencia 
 * os diferentes componentes da base de dados, como artistas, álbuns, músicas, utilizadores e histórico. 
 * Essa estrutura unifica o gerenciamento e facilita a interação entre os diferentes módulos do sistema, é feita uma alocação
 * de memória e depois sao iniciados os managers.
 * 
 * @param parsed_artists
 * @param parsed_musics
 * @param parsed_albums
 * @param parsed_users
 * @param parsed_history
 * @param artists_errors
 * @param music_errors
 * @param users_errors
 * @param history_errors
 * @return @c Database_Manager
 */

Database_Manager *create_database_manager(char **parsed_artists, char **parsed_musics, char **parsed_albums, char **parsed_users, char **parsed_history,
                                          FILE *artists_errors, FILE *musics_errors, FILE *users_errors, FILE *history_errors);



/**
 * @brief Libera memória de cada manager
 * 
 * @param db_manager
 * @return @c NULL
 */

void free_database_manager(Database_Manager *db_manager);



/**
 * @brief Função que obtém o Artist_Manager
 * 
 * A função faz parte da lista de funções getters, que nao passam de nada mais nada menos de funções que devolvem um
 * especifico parametro da estrutura em questão @p *db_manager, sendo neste caso um @c Artist_Manager sendo este um valor do tipo @c Artist_Manager
 * 
 * @param db_manager -> Apontador para um Database Manager
 * @return @c Artist_Manager
 */

Artist_Manager *get_artist_manager(Database_Manager *db_manager);



/**
 * @brief Função que obtém o Music_Manager
 * 
 * A função faz parte da lista de funções getters, que nao passam de nada mais nada menos de funções que devolvem um
 * especifico parametro da estrutura em questão @p *db_manager, sendo neste caso um @c Music_Manager sendo este um valor do tipo @c Music_Manager
 * 
 * @param db_manager -> Apontador para um Database Manager
 * @return @c Music_Manager
 */

Music_Manager *get_music_manager(Database_Manager *db_manager);



/**
 * @brief Função que obtém o Album Manager
 * 
 * A função faz parte da lista de funções getters, que nao passam de nada mais nada menos de funções que devolvem um
 * especifico parametro da estrutura em questão @p *db_manager, sendo neste caso um @c Album_Manager sendo este um valor do tipo @c Album_Manager
 * 
 * @param db_manager -> Apontador para um Database Manager
 * @return @c Album_Manager
 */

Album_Manager *get_album_manager(Database_Manager *db_manager);



/**
 * @brief Função que obtém o User Manager
 * 
 * A função faz parte da lista de funções getters, que nao passam de nada mais nada menos de funções que devolvem um
 * especifico parametro da estrutura em questão @p *db_manager, sendo neste caso um @c User_Manager sendo este um valor do tipo @c User_Manager
 * 
 * @param db_manager -> Apontador para um Database Manager
 * @return @c User_Manager
 */

User_Manager *get_user_manager(Database_Manager *db_manager);



/**
 * @brief Função que obtém o History Manager
 * 
 * A função faz parte da lista de funções getters, que nao passam de nada mais nada menos de funções que devolvem um
 * especifico parametro da estrutura em questão @p *db_manager, sendo neste caso um @c History_Manager sendo este um valor do tipo @c History_Manager
 * 
 * @param db_manager -> Apontador para um Database Manager
 * @return @c History_Manager
 */

History_Manager *get_history_manager(Database_Manager *db_manager);

#endif // DATABASE_MANAGER_H
