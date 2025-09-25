#ifndef HISTORY_H
#define HISTORY_H

#include "main.h"
#include "musicsmanager.h"
#include "usersmanager.h"
#include "validation.h"

typedef struct history History; // Estrutura de dados do Histórico


/**
 * @brief Função para criar um Histórico
 * 
 * Função principal deste ficheiro. Esta função é uma função cujo o objetivo está na criação de uma estrutura (preenchida), 
 * um Histórico. Ela recebe quatro argumentos, @p *linha @p *user_table @p *music_table @p history_errors que, como o nome 
 * indica, recebe uma linha, uma hashtable de users, uma hashtable de musicas e um ficheiro referente ao historico (com erros),
 * começa por alocar memória para a estrutura em questão e de seguida vai preenchendo os parametros da estrutura 
 * do Histórico à medida que percorre a linha, devolvendo assim no final um @c Histórico preenchido.
 * 
 * @param linha -> Apontador para linha de texto
 * @param user_table -> Apontador para a hashtable de Users
 * @param music_table -> Apontador para a hashtable de Musicas
 * @param history_errors -> Apontador para o ficheiro
 * @return A função devolve um Histórico com os campos preenchidos pela informação presente na linha
 * @see struct history
 */

History *create_history_from_line(char *linha, User_Manager *user_table, Music_Manager *music_table, FILE *history_errors);



/**
 * @brief Função que devolve o valor do id de um Histórico
 * 
 * Esta função faz parte da família de funções do tipo "Getters", que o seu objetivo é apenas devolver um parametro
 * da estrutura de dados em causa sendo neste caso a estrutura @p History e o parametro @c ID
 * 
 * @param History -> Estrutura de dados do Histórico
 * @return @c char*
 */

char *get_history_id(History *history);



/**
 * @brief Função que devolve o valor do id do user de um Histórico
 * 
 * Esta função faz parte da família de funções do tipo "Getters", que o seu objetivo é apenas devolver um parametro
 * da estrutura de dados em causa sendo neste caso a estrutura @p History e o parametro @c ID do user
 * 
 * @param History -> Estrutura de dados do Histórico
 * @return @c char*
 */

char *get_history_user_id(History *history);



/**
 * @brief Função que devolve o valor do id da música de um Histórico
 * 
 * Esta função faz parte da família de funções do tipo "Getters", que o seu objetivo é apenas devolver um parametro
 * da estrutura de dados em causa sendo neste caso a estrutura @p History e o parametro @c ID de uma musica
 * 
 * @param History -> Estrutura de dados do Histórico
 * @return @c char*
 */

char *get_history_music_id(History *history);



/**
 * @brief Função que devolve o valor do timestamp de um Histórico
 * 
 * Esta função faz parte da família de funções do tipo "Getters", que o seu objetivo é apenas devolver um parametro
 * da estrutura de dados em causa sendo neste caso a estrutura @p History e o parametro @c TimeStamp
 * 
 * @param History -> Estrutura de dados do Histórico
 * @return @c char*
 */

char *get_history_timestamp(History *history);



/**
 * @brief Função que devolve o valor da duração de um Histórico
 * 
 * Esta função faz parte da família de funções do tipo "Getters", que o seu objetivo é apenas devolver um parametro
 * da estrutura de dados em causa sendo neste caso a estrutura @p History e o parametro @c Duração
 * 
 * @param History -> Estrutura de dados do Histórico
 * @return @c int
 */

char *get_history_duration(History *history);



/**
 * @brief Função que devolve o tipo de plataforma de um Histórico
 * 
 * Esta função faz parte da família de funções do tipo "Getters", que o seu objetivo é apenas devolver um parametro
 * da estrutura de dados em causa sendo neste caso a estrutura @p History e o parametro @c platform podendo este char ter
 * os valores "computador" ou "dispositivo móvel"
 * 
 * @param History -> Estrutura de dados do Histórico
 * @return @c char*
 */

char *get_history_platform(History *history);



/**
 * @brief Função que associa o id ao Histórico
 * 
 * A função faz parte da família de funções do tipo "Setters", que o seu objetivo é associar um parametro da estrutura,
 * à estrutura, neste caso estamos a falar de adicionar o @p ID ao @p History
 * 
 * @param history -> Estrutura de dados do Histórico
 * @param id
 * @return @c NULL 
 */

void set_history_id(History *history, char *id);



/**
 * @brief Função que associa o id do user ao Histórico
 * 
 * A função faz parte da família de funções do tipo "Setters", que o seu objetivo é associar um parametro da estrutura,
 * à estrutura, neste caso estamos a falar de adicionar o @p ID do user ao @p History
 * 
 * @param history -> Estrutura de dados do Histórico
 * @param user_id
 * @return @c NULL 
 */

void set_history_user_id(History *history, char *user_id);



/**
 * @brief Função que associa o id da música ao Histórico
 * 
 * A função faz parte da família de funções do tipo "Setters", que o seu objetivo é associar um parametro da estrutura,
 * à estrutura, neste caso estamos a falar de adicionar o @p ID da música ao @p History
 * 
 * @param history -> Estrutura de dados do Histórico
 * @param music_id
 * @return @c NULL 
 */

void set_history_music_id(History *history, char *music_id);



/**
 * @brief Função que associa o timestamp ao Histórico
 * 
 * A função faz parte da família de funções do tipo "Setters", que o seu objetivo é associar um parametro da estrutura,
 * à estrutura, neste caso estamos a falar de adicionar o @p Timestamp ao @p History
 * 
 * @param history -> Estrutura de dados do Histórico
 * @param timestamp
 * @return @c NULL 
 */

int set_history_timestamp(History *history, char *timestamp);



/**
 * @brief Função que associa a duração ao Histórico
 * 
 * A função faz parte da família de funções do tipo "Setters", que o seu objetivo é associar um parametro da estrutura,
 * à estrutura, neste caso estamos a falar de adicionar a @p Duration ao @p History
 * 
 * @param history -> Estrutura de dados do Histórico
 * @param duration
 * @return @c NULL 
 */

int set_history_duration(History *history, char *duration);



/**
 * @brief Função que associa a paltaforma ao Histórico
 * 
 * A função faz parte da família de funções do tipo "Setters", que o seu objetivo é associar um parametro da estrutura,
 * à estrutura, neste caso estamos a falar de adicionar o @p Platform ao @p History neste caso, devolvemos um inteiro para verificar
 * se foi bem sucedido
 * 
 * @param history -> Estrutura de dados do Histórico
 * @param platform
 * @return @c int
 */

int set_history_platform(History *history, char *platform);


/**
 * @brief Aloca memória para o Histórico
 * 
 * Esta função não é nada mais nada menos do que uma alocação de memória para a estrutura e os seus parametros, nao
 * recebendo qualquer argumento e devolvendo o @c Histórico
 * 
 * @param NULL -> Não tem argumentos
 * @return @c Histórico
 */

History *init_history();



/**
 * @brief Função para libertar memória de um Histórico
 * 
 * A função liberta a memoria alocada de cada um dos campos correspondentes à estrutura do Histórico. Esta recebe um argumento,
 * @p *history ou seja a estrutura de um Histórico, e é do tipo @c void ou seja não devolve valores.
 * 
 * @param history -> Apontador para um histórico
 * @return @c NULL
 */

void free_history(History *history);

#endif // HISTORY_H