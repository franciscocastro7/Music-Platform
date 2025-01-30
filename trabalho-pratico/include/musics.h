#ifndef MUSICS_H
#define MUSICS_H
#include "main.h"
#include "validation.h"
#include "artistsmanager.h"
#include "albumsmanager.h"

typedef struct music Music;


/**
 * @brief Inicializa uma nova música com valores padrão.
 * 
 * Todos os campos são inicializados como NULL ou 0, garantindo uma estrutura válida.
 * 
 * @return Um apontador para a estrutura Music inicializada ou NULL em caso de falha.
 */

Music *init_music();



/**
 * @brief Libera a memória alocada para uma música.
 * 
 * Esta função libera todos os campos dinâmicos dentro da estrutura `Music` e, em seguida, libera a própria estrutura.
 * 
 * @param music Apontador para a música a ser liberada.
 */

void free_music(Music *music);



/**
 * @brief Cria uma música a partir de uma linha de dados formatada.
 * 
 * A função parseia a linha fornecida, cria uma nova estrutura Music e preenche seus campos com os dados extraídos.
 * Também valida os artistas e o álbum associados.
 * 
 * @param linha String contendo os dados da música separados por ponto e vírgula.
 * @param artist_table Tabela de artistas para validação.
 * @param album_table Tabela de álbuns para validação.
 * @param musics_errors Arquivo onde os erros de validação serão registrados.
 * 
 * @return Um apontador para a nova música criada ou NULL se ocorrer um erro.
 */

Music *create_music_from_line(char *linha, Artist_Manager *artist_table, Album_Manager *album_table, FILE *musics_errors);




/**
 * @brief Obtém o ID da música.
 * 
 * @param music Apontador para a música.
 * @return Uma cópia do ID da música ou NULL se não estiver definido.
 */

char *get_music_id(Music *music);



/**
 * @brief Obtém o nome da música.
 * 
 * @param music Apontador para a música.
 * @return Uma cópia do nome da música ou NULL se não estiver definido.
 */

char *get_music_name(Music *music);



/**
 * @brief Obtém os IDs dos artistas associados à música.
 * 
 * @param music Apontador para a música.
 * @return Um array de strings contendo os IDs dos artistas ou NULL se não houver artistas.
 */

char **get_music_artist_id(Music *music);



/**
 * @brief Obtém o ID do álbum associado à música.
 * 
 * @param music Apontador para a música.
 * @return Uma cópia do ID do álbum ou NULL se não estiver definido.
 */

char *get_music_album_id(Music *music);



/**
 * @brief Obtém a duração da música.
 * 
 * @param music Apontador para a música.
 * @return Uma cópia da duração da música ou NULL se não estiver definida.
 */

char *get_music_duration(Music *music);



/**
 * @brief Obtém o gênero da música.
 * 
 * @param music Apontador para a música.
 * @return Uma cópia do gênero da música ou NULL se não estiver definido.
 */

char *get_music_genre(Music *music);



/**
 * @brief Obtém o ano de lançamento da música.
 * 
 * @param music Apontador para a música.
 * @return O ano de lançamento ou 0 se não estiver definido.
 */

int get_music_year(Music *music);



/**
 * @brief Define o ID da música.
 * 
 * Remove as aspas da string fornecida e aloca memória para armazenar o ID.
 * 
 * @param music Apontador para a música.
 * @param id String representando o ID da música.
 */

void set_music_id(Music *music, char *id);



/**
 * @brief Define o nome da música.
 * 
 * Aloca memória e copia a string fornecida como o nome da música.
 * 
 * @param music Apontador para a música.
 * @param name String representando o nome da música.
 */

void set_music_name(Music *music, char *name);



/**
 * @brief Define os IDs dos artistas associados à música.
 * 
 * Esta função processa uma string com IDs de artistas separados por vírgula, 
 * remove caracteres indesejados, e aloca memória para armazená-los como um array de strings.
 * 
 * @param music Apontador para a música.
 * @param artist_ids String contendo os IDs dos artistas separados por vírgula.
 * @param num_artists Número total de artistas na string fornecida.
 */

void set_music_artist_id(Music *music, char *artist_ids, int num_artists);



/**
 * @brief Define o ID do álbum associado à música.
 * 
 * Aloca memória e copia a string fornecida como o ID do álbum.
 * 
 * @param music Apontador para a música.
 * @param album_id String representando o ID do álbum.
 */

void set_music_album_id(Music *music, char *album_id);



/**
 * @brief Define a duração da música.
 * 
 * Remove as aspas da string fornecida, valida o formato da duração (como mm:ss), 
 * e aloca memória para armazená-la. Retorna sucesso ou falha com base na validade.
 * 
 * @param music Apontador para a música.
 * @param duration String representando a duração no formato mm:ss
 * 
 * @return 1 se a duração for válida e definida corretamente, ou 0 em caso de erro.
 */

int set_music_duration(Music *music, char *duration);



/**
 * @brief Define o gênero da música.
 * 
 * Aloca memória e copia a string fornecida como o gênero da música.
 * 
 * @param music Apontador para a música.
 * @param genre String representando o gênero da música.
 */

void set_music_genre(Music *music, char *genre);



/**
 * @brief Define o ano de lançamento da música.
 * 
 * Atribui diretamente o valor do ano à estrutura Music.
 * 
 * @param music Apontador para a música.
 * @param year Ano de lançamento da música.
 */

void set_music_year(Music *music, int year);



#endif
