#ifndef ARTISTS_H
#define ARTISTS_H
#include "main.h"
#include "utils.h"

typedef struct artist Artist; // Estrutura de um Artista


/**
 * @brief Função para criar um Artista
 * 
 * Função principal deste ficheiro. Esta função é uma função cujo o objetivo está na criação de uma estrutura (preenchida), 
 * um Artista. Ela recebe dois argumentos, @p *linha e @p *artists_errors que, como o nome indica, recebe uma linha e um ficheiro
 * de artistas (com erros), começa por alocar memória para a estrutura em questão e de seguida vai preenchendo os parametros da estrutura 
 * do album à medida que percorre a linha, devolvendo assim no final um @c Artista preenchido no final.
 * 
 * @param linha -> Apontador para linha de texto
 * @param artists_errors -> Apontador para um ficheiro de Artistas
 * @return A função devolve um Artista com os campos preenchidos pela informação presente na linha
 * @see struct artist
 */

Artist *create_artist_from_line(char *linha, FILE *artists_errors);



/**
 * @brief Função para libertar memória de um Artista
 * 
 * A função liberta a memoria alocada de cada um dos campos correspondentes à estrutura do Artista. Esta recebe um argumento,
 * @p *artist ou seja a estrutura de um Artista, e é do tipo @c void ou seja não devolve valores.
 * 
 * @param artist -> Apontador para um artista
 * @return @c NULL
 */

void free_artist(Artist *artist); 



/**
 * @brief Função que obtém o id de um Artista
 * 
 * A função faz parte da lista de funções getters, que nao passam de nada mais nada menos de funções que devolvem um
 * especifico parametro da estrutura em questão @p *artist, sendo neste caso um @c ID sendo este um valor do tipo @c char pointer
 * 
 * @param artist -> Apontador para um artista
 * @return @c char pointer
 */

char* get_artist_id(Artist *artist);



/**
 * @brief Função que obtém o nome de um Artista
 * 
 * A função faz parte da lista de funções getters, que nao passam de nada mais nada menos de funções que devolvem um
 * especifico parametro da estrutura em questão @p *artist, sendo neste caso um @c nome sendo este um valor do tipo @c char
 * 
 * @param artist -> Apontador para um artista
 * @return @c char pointer
 */

char* get_artist_name(Artist *artist);



/**
 * @brief Função que obtém a receita por stream de um Artista
 * 
 * A função faz parte da lista de funções getters, que nao passam de nada mais nada menos de funções que devolvem um
 * especifico parametro da estrutura em questão @p *artist, sendo neste caso um @c recipe_per_stream sendo este um valor do 
 * tipo @c float
 * 
 * @param artist -> Apontador para um artista
 * @return @c float
 */

float get_artist_recipe_per_stream(Artist *artist);



/**
 * @brief Função que obtém o país de um Artista
 * 
 * A função faz parte da lista de funções getters, que nao passam de nada mais nada menos de funções que devolvem um
 * especifico parametro da estrutura em questão @p *artist, sendo neste caso um @c país sendo este um valor do tipo @c char ppointer
 * 
 * @param artist -> Apontador para um artista
 * @return @c char pointer
 */

char* get_artist_country(Artist *artist);



/**
 * @brief Função que obtém o tipo de um Artista
 * 
 * A função faz parte da lista de funções getters, que nao passam de nada mais nada menos de funções que devolvem um
 * especifico parametro da estrutura em questão @p *artist, sendo neste caso um @c tipo sendo este um valor do tipo @c char pointer
 * que nos vai indicar se o artista é uma banda ou não
 * 
 * @param artist -> Apontador para um artista
 * @return @c char pointer
 */

char* get_artist_type(Artist *artist);



/**
 * @brief Função que obtém o os constituintes de um Artista
 * 
 * A função faz parte da lista de funções getters, que nao passam de nada mais nada menos de funções que devolvem um
 * especifico parametro da estrutura em questão @p *artist, sendo neste caso um @c ID sendo este um valor do tipo @c char pointer pointer
 * que caso o artista seja uma banda, vai ser um array com os varios constituintes caso contrário será @c NULL
 * 
 * @param artist -> Apontador para um artista
 * @return @c char pointer pointer
 */

char **get_artist_constituents(Artist *artist);



/**
 * @brief Função que cria o id de um Artista
 * 
 * A função faz parte da família de funções setters, que de forma breve são funções que recebem como argumento o parametro
 * de uma estrutura @p ID, sendo neste caso de um @p *artista alocam memoria na estrutura e colocam o respetivo parametro
 * na sua posição pertencente à estrutura. Esta função devolve @c void
 * 
 * @param artist -> Apontador para um artista
 * @param id -> apontador para um id
 * @return @c NULL
 * @note É feita uma cópia do ID
 */

void set_artist_id(Artist *artist, char *id);



/**
 * @brief Função que cria o nome de um Artista
 * 
 * A função faz parte da família de funções setters, que de forma breve são funções que recebem como argumento o parametro
 * de uma estrutura @p Nome, sendo neste caso de um @p *artista alocam memoria na estrutura e colocam o respetivo parametro
 * na sua posição pertencente à estrutura. Esta função devolve @c void
 * 
 * @param artist -> Apontador para um artista
 * @param name -> apontador para um nome
 * @return @c NULL
 * @note É feita uma cópia do nome
 */

void set_artist_name(Artist *artist, char *name);



/**
 * @brief Função que cria a receita de um Artista
 * 
 * A função faz parte da família de funções setters, que de forma breve são funções que recebem como argumento o parametro
 * de uma estrutura @p Receita, sendo neste caso de um @p *artista alocam memoria na estrutura e colocam o respetivo parametro
 * na sua posição pertencente à estrutura. Esta função devolve @c void
 * 
 * @param artist -> Apontador para um artista
 * @param recipe_per_stream -> float
 * @return @c NULL
 */

void set_artist_recipe_per_stream(Artist *artist, float recipe_per_stream);



/**
 * @brief Função que cria o país de onde é o Artista
 * 
 * A função faz parte da família de funções setters, que de forma breve são funções que recebem como argumento o parametro
 * de uma estrutura @p país, sendo neste caso de um @p *artista alocam memoria na estrutura e colocam o respetivo parametro
 * na sua posição pertencente à estrutura. Esta função devolve @c void
 * 
 * @param artist -> Apontador para um artista
 * @param country -> apontador para um país
 * @return @c NULL
 * @note É feita uma cópia do país
 */

void set_artist_country(Artist *artist, char *country);



/**
 * @brief Função que cria o tipo de um Artista
 * 
 * A função faz parte da família de funções setters, que de forma breve são funções que recebem como argumento o parametro
 * de uma estrutura @p Tipo, sendo neste caso de um @p *artista alocam memoria na estrutura e colocam o respetivo parametro
 * na sua posição pertencente à estrutura. Esta função devolve @c int
 * 
 * @param artist -> Apontador para um artista
 * @param type -> apontador para um tipo
 * @return @c int
 * @note É feita uma alocação de memória e é feita uma cópia do tipo
 */

int set_artist_type(Artist *artist, char *type);



/**
 * @brief Função que cria os constituintes de um Artista
 * 
 * A função faz parte da família de funções setters, que de forma breve são funções que recebem como argumento o parametro
 * de uma estrutura @p constituintes, sendo neste caso de um @p *artista alocam memoria na estrutura e colocam o respetivo parametro
 * na sua posição pertencente à estrutura. Esta função devolve @c void
 * 
 * @param artist -> Apontador para um artista
 * @param constituents -> Apontador para o array de constituintes
 * @param num_constituents -> Número de constituintes
 * @return @c NULL
 * @note É feita uma alocação de memória e é feita uma cópia dos constituintes
 */

void set_artist_constituents(Artist *artist, char **constituents, int num_constituents);



/**
 * @brief Aloca memória para um Artista
 * 
 * Esta função não é nada mais nada menos do que uma alocação de memória para a estrutura e os seus parametros, nao
 * recebendo qualquer argumento e devolvendo o @c Artista
 * 
 * @param NULL -> Não tem argumentos
 * @return @c Artista
 */

Artist *init_artist();


#endif // ARTISTS_H