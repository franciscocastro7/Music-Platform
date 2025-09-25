#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include "main.h"
#include "history.h"
#include "usersmanager.h"
#include "musicsmanager.h"


typedef struct history_manager History_Manager; // Estrutura de dados de uma Hashtable de Históricos

/**
 * @brief Criar hashtable de History
 * 
 * A função tem como objetivo processar um array de strings contendo informações sobre historico @p parsed_history @p user_manager
 * @p music_manager @p history_errors e outros managers, cria uma estrutura de dados @c History_Manager que organiza esses históricos
 * em uma HashTable.
 * 
 * @param parsed_history -> Apontador para um array de parsed_history
 * @param user_manager -> apontador para uma hashtable de users
 * @param music_manager -> apontador para uma hashtable de musicas
 * @param history_errors -> apontador para um ficheiro de historicos (com erros)
 * @return @c History_Manager
 */

History_Manager *ParseHistory(char **parsed_history, User_Manager *user_manager, Music_Manager *music_manager, FILE *history_errors);



/**
 * @brief Função que devolve a Hashtable
 * 
 * @param history_manager -> Apontador para o manager
 * @return @c GHashtable
 */

GHashTable *get_history_table(History_Manager *history_manager);



/**
 * @brief Libera memória da Hashtable
 * 
 * @param album_table -> apontador para uma hashtable de Albuns
 * @return @c NULL
 */

void free_history_manager(History_Manager *history_manager);

#endif // HISTORYMANAGER_H