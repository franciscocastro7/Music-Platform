#ifndef ALBUMS_H
#define ALBUMS_H
#include "main.h"
#include "artistsmanager.h"
#include "utils.h"



typedef struct album Album; // Estrutura de um Album

/**
 * @brief Função para criar um Album
 * 
 * Função principal deste ficheiro. Esta função é uma função cujo o objetivo está na criação de uma estrutura (preenchida), 
 * um Album. Ela recebe dois argumentos, @p *linha e @p *artis_table que, como o nome indica, recebe uma linha e uma hashtable
 * de artistas, começa por alocar memória para a estrutura em questão e de seguida vai preenchendo os parametros da estrutura 
 * do album à medida que percorre a linha, devolvendo assim um @c Album preenchido no final.
 * 
 * @param linha -> Apontador para linha de texto
 * @param artis_table -> Apontador para uma hashtable de Artistas
 * @return A função devolve um Albúm com os campos preenchidos pela informação presente na linha
 * @see struct album
 */

Album *create_album_from_line(char *linha, Artist_Manager *artis_table);



/**
 * @brief Função para libertar memória de um Album
 * 
 * A função liberta a memoria alocada de cada um dos campos correspondentes à estrutura do Album. Esta recebe um argumento,
 * @p *album ou seja a estrutura de um Album, e é do tipo @c void ou seja não devolve valores.
 * 
 * @param album -> Apontador para um album
 * @return @c NULL
 */

void free_album(Album *album);



/**
 * @brief Função que obtém o id de um Album
 * 
 * A função faz parte da lista de funções getters, que nao passam de nada mais nada menos de funções que devolvem um
 * especifico parametro da estrutura em questão @p *album, sendo neste caso um @c ID sendo este um valor do tipo @c char
 * 
 * @param album -> Apontador para um album
 * @return @c char
 */

char *get_album_id(Album *album);



/**
 * @brief Função que obtém o título de um Album
 * 
 * A função faz parte da lista de funções getters, que nao passam de nada mais nada menos de funções que devolvem um
 * especifico parametro da estrutura em questão @p *album, sendo neste caso um @c title sendo este um valor do tipo @c char
 * 
 * @param album -> Apontador para um album
 * @return @c char
 */

char *get_album_title(Album *album);



/**
 * @brief Função que obtém o id do artista de um Album
 * 
 * A função faz parte da lista de funções getters, que nao passam de nada mais nada menos de funções que devolvem um
 * especifico parametro da estrutura em questão @p *album, sendo neste caso um @c ID (do artista a quem o album pertence) 
 * sendo este um valor do tipo @c char
 * 
 * @param album -> Apontador para um album
 * @return @c char
 */

char **get_album_artist_id(Album *album);



/**
 * @brief Função que obtém o ano de um Album
 * 
 * A função faz parte da lista de funções getters, que nao passam de nada mais nada menos de funções que devolvem um
 * especifico parametro da estrutura em questão @p *album, sendo neste caso o @c Ano sendo este um valor do tipo @c int
 * 
 * @param album -> Apontador para um album
 * @return @c int
 */

int get_album_year(Album *album);



/**
 * @brief Função que cria o id do Album
 * 
 * A função faz parte da família de funções setters, que de forma breve são funções que recebem como argumento o parametro
 * de uma estrutura @p ID, sendo neste caso de um album @p *album, e alocam memoria na estrutura e colocam o respetivo parametro
 * na sua posição pertencente à estrutura. Esta função devolve @c void
 * 
 * @param album -> Apontador para um album
 * @param id -> apontador para um id
 * @return @c NULL
 * @note É feita uma alocação de memória e é feita uma cópia do ID
 */

void set_album_id(Album *album, char *id);



/**
 * @brief Função que cria o título do Album
 * 
 * A função faz parte da família de funções setters, que de forma breve são funções que recebem como argumento o parametro
 * de uma estrutura @p Título, sendo neste caso de um album @p *album, e alocam memoria na estrutura e colocam o respetivo parametro
 * na sua posição pertencente à estrutura. Esta função devolve @c void
 * 
 * @param album -> Apontador para um album
 * @param id -> apontador para um título
 * @return @c NULL
 * @note É feita uma alocação de memória e é feita uma cópia do título
 */

void set_album_title(Album *album, char *title);



/**
 * @brief Função que cria o id do artista do Album
 * 
 * A função faz parte da família de funções setters, que de forma breve são funções que recebem como argumento o parametro
 * de uma estrutura @p ID (de um artista) e o número de artistas @p num_artists, sendo neste caso de um album @p *album, 
 * e alocam memoria na estrutura e colocam o respetivo parametro na sua posição pertencente à estrutura. Esta função devolve @c void
 * 
 * @param album -> Apontador para um album
 * @param artsts_ids -> apontador para um id de um artista
 * @param num_artists -> número de artistas
 * @return @c NULL
 */

void set_album_artist_id(Album *album, char *artist_ids, int num_artists);



/**
 * @brief Função que cria o Ano do Album
 * 
 * A função faz parte da família de funções setters, que de forma breve são funções que recebem como argumento o parametro
 * de uma estrutura @p Ano, sendo neste caso de um album @p *album, e alocam memoria na estrutura e colocam o respetivo parametro
 * na sua posição pertencente à estrutura. Esta função devolve @c void
 * 
 * @param album -> Apontador para um album
 * @param year -> Um inteiro referente ao Ano
 * @return @c NULL
 */

void set_album_year(Album *album, int year);



/**
 * @brief Aloca memória para um Album
 * 
 * Esta função não é nada mais nada menos do que uma alocação de memória para a estrutura e os seus parametros, nao
 * recebendo qualquer argumento e devolvendo o @c Album
 * 
 * @param NULL -> Não tem argumentos
 * @return @c Album
 */

Album *init_album();


#endif