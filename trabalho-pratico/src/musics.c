#include "../include/musics.h"

struct music
{
    char *id;
    char *name;
    char **artist_id;
    char *album_id;
    char *duration;
    char *genre;
    int year;
    //char *lyrics;
};

Music *create_music_from_line(char *linha, Artist_Manager *artist_table, Album_Manager *album_table, FILE *musics_errors)
{
    Music *new_music = init_music();
    if (new_music == NULL)
    {
        printf("Erro ao alocar memória para música.\n");
        return NULL;
    }

    char *aux = strdup(linha);
    char *aux2 = aux; // Guardar para liberar memória depois
    char *token;

    token = strsep(&aux, ";");
    remove_quotes(token);
    set_music_id(new_music, token);

    token = strsep(&aux, ";");
    set_music_name(new_music, token);

    token = strsep(&aux, ";");
    if (token)
    {
        char *delimiter = ", ";
        int nr_artists = 0;

        char *count = strdup(token);
        char *count_copy = count;
        char *piece;

        while ((piece = strsep(&count, delimiter)))
        {
            if (strlen(piece) == 0)
                continue;
            else
                nr_artists++;
        }

        free(count_copy);
        remove_quotes(token);
        set_music_artist_id(new_music, token, nr_artists);
    }

    token = strsep(&aux, ";");
    remove_quotes(token);
    set_music_album_id(new_music, token);

    token = strsep(&aux, ";");
    remove_quotes(token);
    if (set_music_duration(new_music, token) == 0)
    {
        fprintf(musics_errors, "%s\n", linha);
        free(aux2);
        free_music(new_music);
        return NULL;
    }

    token = strsep(&aux, ";");
    set_music_genre(new_music, token);

    token = strsep(&aux, ";");
    if (token)
    {
        remove_quotes(token);
        int year = atoi(token);
        set_music_year(new_music, year);
    }

    token = strsep(&aux, ";");
    //set_music_lyrics(new_music, token); // Processa as letras

    // Validação dos artistas associados
    if (validate_music_artists(new_music, artist_table) != 0)
    {
        fprintf(musics_errors, "%s\n", linha);
        free(aux2);
        free_music(new_music);
        return NULL;
    }

    // Validação do álbum associado
    if (validate_music_album(new_music, album_table) != 0)
    {
        fprintf(musics_errors, "%s\n", linha);
        free(aux2);
        free_music(new_music);
        return NULL;
    }

    free(aux2);
    return new_music;
}

char *get_music_id(Music *music)
{
    return music->id ? strdup(music->id) : NULL;
}

char *get_music_name(Music *music)
{
    return music->name ? strdup(music->name) : NULL;
}

char **get_music_artist_id(Music *music)
{
    if (music->artist_id == NULL)
    {
        return NULL;
    }

    int count = 0;
    while (music->artist_id[count] != NULL)
    {
        count++;
    }

    char **copy = malloc((count + 1) * sizeof(char *));
    if (copy == NULL) return NULL; // Verifica falha de alocação

    for (int i = 0; i < count; i++)
    {
        copy[i] = strdup(music->artist_id[i]);
    }
    copy[count] = NULL;

    return copy;
}

char *get_music_album_id(Music *music)
{
    return music->album_id ? strdup(music->album_id) : NULL;
}

char *get_music_duration(Music *music)
{
    return music->duration ? strdup(music->duration) : NULL;
}

char *get_music_genre(Music *music)
{
    return music->genre ? strdup(music->genre) : NULL;
}

int get_music_year(Music *music)
{
    return music->year;
}

/*char *get_music_lyrics(Music *music)
{
    if (music == NULL || music->lyrics == NULL) {
        return NULL; // Ou uma string vazia, dependendo do comportamento esperado
    }

    return strdup(music->lyrics); // Agora, duplicar a string sem riscos
}*/

// Setters
void set_music_id(Music *music, char *id)
{
    remove_quotes(id);
    music->id = malloc(strlen(id) + 1);
    if (music->id) {
        strcpy(music->id, id);
    }
}

void set_music_name(Music *music, char *name)
{
    music->name = malloc(strlen(name) + 1);
    if (music->name) {
        strcpy(music->name, name);
    }
}

void set_music_artist_id(Music *music, char *artist_ids, int num_artists)
{
    music->artist_id = malloc((num_artists + 1) * sizeof(char *)); // Corrigido o cálculo de alocação
    if (music->artist_id == NULL) return; // Verifica falha de alocação

    char *token = strdup(artist_ids);
    if (token == NULL) return; // Verifica falha de alocação

    int i = 0;
    char *token_aux = NULL;
    while ((token_aux = strsep(&artist_ids, ", ")))
    {
        if (strlen(token_aux) == 0)
            continue;
        remove_brackets(token_aux);
        music->artist_id[i] = strdup(token_aux);
        if (music->artist_id[i] == NULL) return; // Verifica falha de alocação
        i++;
    }
    music->artist_id[i] = NULL;
    free(token);
}

void set_music_album_id(Music *music, char *album_id)
{
    if (album_id != NULL)
    {
        music->album_id = malloc(strlen(album_id) + 1);
        if (music->album_id != NULL)
        {
            strcpy(music->album_id, album_id);
        }
    }
}

int set_music_duration(Music *music, char *duration)
{
    remove_quotes(duration);
    if (is_valid_duration(duration))
    {
        music->duration = malloc(strlen(duration) + 1);
        if (music->duration == NULL)
        {
            printf("Erro ao alocar memória para a duração.\n");
            return 0;
        }
        strcpy(music->duration, duration);
        return 1;
    }
    else
    {
        return 0;
    }
}

void set_music_genre(Music *music, char *genre)
{
    music->genre = malloc(strlen(genre) + 1);
    if (music->genre) {
        strcpy(music->genre, genre);
    }
}

void set_music_year(Music *music, int year)
{
    music->year = year;
}

/*void set_music_lyrics(Music *music, char *lyrics)
{
    music->lyrics = malloc(strlen(lyrics) + 1);
    strcpy(music->lyrics, lyrics);
}*/

Music *init_music()
{
    Music *new_music = malloc(sizeof(Music));

    new_music->id = NULL;
    new_music->name = NULL;
    new_music->artist_id = NULL;
    new_music->album_id = NULL; // Inicializa o novo campo
    new_music->duration = NULL;
    new_music->genre = NULL;
    new_music->year = 0;
    //new_music->lyrics = NULL;

    return new_music;
}

void free_music(Music *music)
{
    if (music == NULL)
        return;

    if (music->id != NULL)
    {
        free(music->id);
    }
    if (music->name != NULL)
    {
        free(music->name);
    }
    if (music->artist_id != NULL)
    {
        for (int i = 0; music->artist_id[i] != NULL; i++)
        {
            free(music->artist_id[i]);
        }
        free(music->artist_id);
    }

    if (music->album_id != NULL) // Libera album_id
    {
        free(music->album_id);
    }

    if (music->duration != NULL)
    {
        free(music->duration);
    }
    if (music->genre != NULL)
    {
        free(music->genre);
    }
    /*if (music->lyrics != NULL)
    {
        free(music->lyrics);
    }*/

    free(music);
}

