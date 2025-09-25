#ifndef USERS_H
#define USERS_H

#include "main.h"
#include "validation.h"
#include "musicsmanager.h"
#include "musics.h"
#include "database_manager.h"
#include "artists.h"
#include "usersmanager.h"
#include "utils.h"


typedef struct user User; // Estrutura de dados de um User
typedef struct date Date; // Estrutura de dados de uma data


/**
 * @brief Cria um usuário a partir de uma linha do arquivo CSV.
 * 
 * Esta função cria um novo usuário a partir de uma linha do arquivo CSV. A linha é dividida
 * em tokens utilizando o separador de campo (`;`). Cada campo é associado ao respectivo atributo do usuário.
 * Caso haja algum erro na criação do usuário ou em algum campo inválido, a linha é registrada no arquivo de erros
 * e o usuário não é criado.
 * 
 * @param linha A linha do arquivo CSV contendo as informações do usuário.
 * @param music_table A tabela de músicas, usada para validação dos IDs de músicas curtidas pelo usuário.
 * @param users_errors O arquivo de erros onde as linhas com falhas são registradas.
 * 
 * @return Um Apontador para o novo usuário criado
 */

User *create_users_from_line(char *linha, Music_Manager *music_table, FILE *users_errors);



/**
 * @brief Retorna o nome de usuário do usuário.
 * 
 * Esta função retorna uma cópia do nome de usuário do usuário.
 * 
 * @param user Apontador para o usuário.
 * 
 * @return Cópia do nome de usuário.
 */

char *get_user_username(User *user);



/**
 * @brief Retorna o e-mail do usuário.
 * 
 * Esta função retorna uma cópia do e-mail do usuário.
 * 
 * @param user Apontador para o usuário.
 * 
 * @return Cópia do e-mail do usuário.
 */

char *get_user_email(User *user);



/**
 * @brief Retorna o primeiro nome do usuário.
 * 
 * Esta função retorna uma cópia do primeiro nome do usuário.
 * 
 * @param user Apontador para o usuário.
 * 
 * @return Cópia do primeiro nome do usuário.
 */

char *get_user_first_name(User *user);



/**
 * @brief Retorna o ultimo nome do usuário.
 * 
 * Esta função retorna uma cópia do ultimo nome do usuário.
 * 
 * @param user Apontador para o usuário.
 * 
 * @return Cópia do ultimo nome do usuário.
 */

char *get_user_last_name(User *user);



/**
 * @brief Retorna a data de nascimento do usuário.
 * 
 * Esta função retorna o ponteiro para a estrutura `Date` que representa a data de nascimento do usuário.
 * 
 * @param user Apontador para o usuário.
 * 
 * @return Apontador para a data de nascimento do usuário.
 */

Date* get_user_birth_date(User *user);



/**
 * @brief Retorna o ano de nascimento do usuário.
 * 
 * Esta função retorna o ano de nascimento do usuário.
 * 
 * @param user Apontador para o usuário.
 * 
 * @return O ano de nascimento do usuário.
 */
int get_user_birth_year(User *user);



/**
 * @brief Retorna o mês de nascimento do usuário.
 * 
 * Esta função retorna o mês de nascimento do usuário.
 * 
 * @param user Apontador para o usuário.
 * 
 * @return O mês de nascimento do usuário.
 */

int get_user_birth_month(User *user);




/**
 * @brief Retorna o dia de nascimento do usuário.
 * 
 * Esta função retorna o dia de nascimento do usuário.
 * 
 * @param user Apontador para o usuário.
 * 
 * @return O dia de nascimento do usuário.
 */
int get_user_birth_day(User *user);

/**
 * @brief Retorna o país do usuário.
 * 
 * Esta função retorna uma cópia do país do usuário.
 * 
 * @param user Apontador para o usuário.
 * 
 * @return Cópia do país do usuário.
 */
char *get_user_country(User *user);



/**
 * @brief Retorna o tipo de assinatura do usuário.
 * 
 * Esta função retorna uma cópia do tipo de assinatura do usuário.
 * 
 * @param user Apontador para o usuário.
 * 
 * @return Cópia do tipo de assinatura do usuário.
 */

char *get_user_subscription_type(User *user);



/**
 * @brief Retorna uma cópia dos IDs das músicas curtidas pelo usuário.
 * 
 * Esta função retorna uma cópia do array de IDs de músicas curtidas pelo usuário.
 * O array retornado deve ser liberado após o uso.
 * 
 * @param user Apontador para o usuário.
 * 
 * @return Cópia dos IDs das músicas curtidas ou `NULL` se não houver músicas curtidas.
 */

char **get_user_liked_musics_id(User *user);



/**
 * @brief Define o nome de usuário do usuário.
 * 
 * Esta função define o nome de usuário do usuário.
 * 
 * @param user Apontador para o usuário.
 * @param username O nome de usuário a ser definido.
 */

void set_user_username(User *user, char *username);



/**
 * @brief Define o e-mail do usuário.
 * 
 * Esta função define o e-mail do usuário, validando-o primeiro.
 * 
 * @param user Apontador para o usuário.
 * @param email O e-mail a ser definido.
 * 
 * @return `1` se o e-mail for válido e for definido corretamente, `0` caso contrário.
 */

int set_user_email(User *user, char *email);



/**
 * @brief Define o primeiro nome do usuário.
 * 
 * Esta função define o primeiro nome do usuário.
 * 
 * @param user Apontador para o usuário.
 * @param first_name O primeiro nome a ser definido.
 */

void set_user_first_name(User *user, char *first_name);



/**
 * @brief Define o ultimo nome do usuário.
 * 
 * Esta função define o ultimo nome do usuário.
 * 
 * @param user Apontador para o usuário.
 * @param last_name O ultimo nome a ser definido.
 */

void set_user_last_name(User *user, char *last_name);



/**
 * @brief Define a data de nascimento do usuário.
 * 
 * Esta função define a data de nascimento do usuário, validando-a primeiro.
 * 
 * @param user Apontador para o usuário.
 * @param birth_date A data de nascimento a ser definida, no formato "YYYY/MM/DD".
 * 
 * @return `1` se a data for válida e for definida corretamente, `0` caso contrário.
 */

int set_user_birth_date(User *user, char *birth_date);



/**
 * @brief Define o país do usuário.
 * 
 * Esta função define o país do usuário.
 * 
 * @param user Apontador para o usuário.
 * @param country O país a ser definido.
 */

void set_user_country(User *user, char *country);



/**
 * @brief Define o tipo de assinatura do usuário.
 * 
 * Esta função define o tipo de assinatura do usuário, validando se é "premium" ou "normal".
 * 
 * @param user Apontador para o usuário.
 * @param subscription_type O tipo de assinatura a ser definido.
 * 
 * @return `1` se o tipo de assinatura for válido e for definido corretamente, `0` caso contrário.
 */

int set_user_subscription_type(User *user, char *subscription_type);



/**
 * @brief Define os IDs das músicas curtidas pelo usuário.
 * 
 * Esta função define os IDs das músicas curtidas pelo usuário.
 * 
 * @param user Apontador para o usuário.
 * @param liked_musics_ids String contendo os IDs das músicas curtidas, separados por vírgula.
 * @param num_musics Número de músicas a serem definidas.
 */

void set_user_liked_musics_id(User *user, char *liked_musics_ids, int num_musics);



/**
 * @brief Calcula a idade de um usuário com base na sua data de nascimento.
 * 
 * Esta função calcula a idade de um usuário com base na sua data de nascimento, levando em consideração
 * a data atual. A idade é calculada subtraindo o ano de nascimento do ano atual. 
 * Se a data de nascimento ainda não tiver ocorrido no ano atual, a função subtrai um ano da idade calculada.
 * 
 * @param birth_date Apontador para o usuário, cujo campo de data de nascimento será utilizado para o cálculo.
 * 
 * @return A idade calculada ou `-1` em caso de erro (se o usuário ou sua data de nascimento forem `NULL`).
 */

int calculate_age(User *birth_date);



/**
 * @brief Aloca memória para um User
 * 
 * Esta função não é nada mais nada menos do que uma alocação de memória para a estrutura e os seus parametros, nao
 * recebendo qualquer argumento e devolvendo o @c User
 * 
 * @param NULL -> Não tem argumentos
 * @return @c User
 */

User *init_user();



/**
 * @brief Função para libertar memória de um User
 * 
 * A função liberta a memoria alocada de cada um dos campos correspondentes à estrutura do User. Esta recebe um argumento,
 * @p *user ou seja a estrutura de um User, e é do tipo @c void ou seja não devolve valores.
 * 
 * @param user -> Apontador para um User
 * @return @c NULL
 */

void free_user(User *user);

#endif // USERS_H
