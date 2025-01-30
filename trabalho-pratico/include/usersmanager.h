#ifndef USERSMANAGER_H
#define USERSMANAGER_H

#include "main.h"
#include "users.h"
#include "parser.h"
#include "utils.h"

typedef struct user_manager User_Manager;
typedef struct music_manager Music_Manager;

/**
 * @brief Cria e preenche um User_Manager a partir de um array de usuários.
 * 
 * Esta função processa um array de usuários (parsed_users) e cria um novo User_Manager. Para cada linha do array, 
 * um novo usuário é criado e adicionado à tabela de hash dentro do User_Manager.
 * A função também lida com erros durante a criação dos usuários e escreve essas falhas em um arquivo de erros.
 * 
 * @param parsed_users Array de strings contendo os dados dos usuários.
 * @param music_manager Apontador para o Music_Manager, usado para validação dos IDs das músicas.
 * @param users_errors Arquivo onde os erros dos usuários inválidos serão registrados.
 * 
 * @return Um apontador para o User_Manager preenchido ou `NULL` se ocorrer algum erro.
 */

User_Manager *ParseUsers(char **parsed_users, Music_Manager *music_manager, FILE *users_errors);



/**
 * @brief Retorna a tabela de usuários armazenada no User_Manager.
 * 
 * Esta função retorna a hashtable que contém os usuários do sistema. A hashtable mapeia o nome de usuário 
 * para o apontador do respectivo usuário.
 * 
 * @param user_manager Apontador para o User_Manager.
 * 
 * @return Hashtable de usuários.
 */

GHashTable *get_user_table(User_Manager *user_manager);



/**
 * @brief Libera a memória alocada para o User_Manager.
 * 
 * Esta função destrói a tabela de hash de usuários e libera a memória alocada para o User_Manager.
 * 
 * @param user_manager Apontador para o User_Manager a ser liberado.
 */

void free_user_manager(User_Manager *user_manager);


#endif
