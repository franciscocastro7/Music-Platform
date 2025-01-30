#include "../include/albums.h"

struct album
{
    char *id;
    char *title;
    char **artist_id;
    int year;
    //char **producers;
};

Album *create_album_from_line(char *linha, Artist_Manager *artist_table)
{
    Album *new_album = init_album();
    if (new_album == NULL)
    {
        printf("Erro ao alocar memória para álbum.\n");
        return NULL;
    }

    char *aux = strdup(linha);
    char *aux2 = aux; // Save for later freeing
    char *token;

    // Extrair id do álbum
    token = strsep(&aux, ";");
    remove_quotes(token);
    set_album_id(new_album, token);

    // Extrair título do álbum
    token = strsep(&aux, ";");
    remove_quotes(token);
    set_album_title(new_album, token);

    // Extrair artistas do álbum
    token = strsep(&aux, ";");
    if (token)
    {
        char *delimiter = ", ";
        int nr_artists = 0;
        char *count = strdup(token);  // Alocar para contar os artistas
        char *count_copy = count;
        char *piece;

        // Contar o número de artistas
        while ((piece = strsep(&count, delimiter)))
        {
            if (strlen(piece) == 0)
                continue;
            else
                nr_artists++;
        }

        free(count_copy);  // Liberar a memória de contagem
        remove_quotes(token);
        set_album_artist_id(new_album, token, nr_artists);  // Definir os ids dos artistas
    }

    // Extrair o ano do álbum
    token = strsep(&aux, ";");
    if (token)
    {
        remove_quotes(token);
        int year = atoi(token);
        set_album_year(new_album, year);
    }

    // Liberar a memória de aux2 após o uso
    free(aux2);

    return new_album;
}

// Getters
char *get_album_id(Album *album)
{
    return strdup(album->id);
}

char *get_album_title(Album *album)
{
    return strdup(album->title);
}

char **get_album_artist_id(Album *album)
{
    if (album->artist_id == NULL)
    {
        return NULL;
    }

    int count = 0;
    while (album->artist_id[count] != NULL)
    {
        count++;
    }

    char **copy = malloc((count + 1) * sizeof(char *));
    for (int i = 0; i < count; i++)
    {
        copy[i] = strdup(album->artist_id[i]);
    }
    copy[count] = NULL;

    return copy;
}

int get_album_year(Album *album)
{
    return album->year;
}

// Setters
void set_album_id(Album *album, char *id)
{
    remove_quotes(id);
    album->id = malloc(strlen(id) + 1);
    strcpy(album->id, id);
}

void set_album_title(Album *album, char *title)
{
    remove_quotes(title);
    album->title = malloc(strlen(title) + 1);
    strcpy(album->title, title);
}

void set_album_artist_id(Album *album, char *artist_ids, int num_artists)
{
    if (!artist_ids || num_artists <= 0)
    {
        album->artist_id = NULL;  // Caso inválido
        return;
    }

    // Alocar espaço para os IDs de artistas (com NULL no final)
    album->artist_id = malloc((num_artists + 1) * sizeof(char *));
    if (!album->artist_id)
    {
        return;
    }

    char *token = strdup(artist_ids);  // Criar uma cópia da string de IDs de artistas
    if (!token)
    {
        free(album->artist_id);
        album->artist_id = NULL;
        return;
    }

    char *original_token = token;  // Preservar ponteiro original para liberar mais tarde
    char *token_aux;
    int i = 0;

    while ((token_aux = strsep(&token, ", ")))  // Separar tokens
    {
        if (strlen(token_aux) == 0)  // Ignorar strings vazias
            continue;

        remove_brackets(token_aux);  // Limpar o ID do artista (se necessário)
        album->artist_id[i] = strdup(token_aux);  // Duplicar o ID do artista
        if (!album->artist_id[i])  // Verificar alocação
        {
            for (int j = 0; j < i; j++)  // Liberar IDs já alocados
            {
                free(album->artist_id[j]);
            }
            free(album->artist_id);
            free(original_token);
            album->artist_id = NULL;
            return;
        }
        i++;
    }

    album->artist_id[i] = NULL;  // Finalizar a lista com NULL
    free(original_token);  // Liberar a string duplicada
}



void set_album_year(Album *album, int year)
{
    album->year = year;
}

Album *init_album()
{
    Album *new_album = malloc(sizeof(Album));

    new_album->id = NULL;
    new_album->title = NULL;
    new_album->artist_id = NULL;
    new_album->year = 0;
    //new_album->producers = NULL;

    return new_album;
}

void free_album(Album *album)
{
    if (album == NULL)
        return;

    if (album->id != NULL)
    {
        free(album->id);
    }
    if (album->title != NULL)
    {
        free(album->title);
    }
    if (album->artist_id != NULL)
    {
        for (int i = 0; album->artist_id[i] != NULL; i++)
        {
            free(album->artist_id[i]);  // Free each artist ID
        }
        free(album->artist_id);  // Free the artist_id array itself
    }
    free(album);  // Finally free the album struct
}
