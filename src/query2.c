#include "../include/query2.h"
#include "../include/database_manager.h"
#include "../include/artistsmanager.h"
#include "../include/musicsmanager.h"
#include "../include/artists.h"
#include "../include/musics.h"

// Função de comparação para ordenar artistas por duração e, em caso de empate, pelo ID
gint compare_artists(gpointer a, gpointer b, gpointer user_data)
{
    GHashTable *discography_duration = (GHashTable *)user_data;
    char *artist_id_a = (char *)a;
    char *artist_id_b = (char *)b;

    int duration_a = *(int *)g_hash_table_lookup(discography_duration, artist_id_a);
    int duration_b = *(int *)g_hash_table_lookup(discography_duration, artist_id_b);

    if (duration_a != duration_b)
        return duration_b - duration_a;
    return strcmp(artist_id_a, artist_id_b);
}

void query2(Database_Manager *db_manager, int N, char *country_filter, FILE *output, char separator)
{
    if (N == 0)
    {
        fprintf(output, "\n");
        return;
    }

    Artist_Manager *artist_manager = get_artist_manager(db_manager);
    Music_Manager *music_manager = get_music_manager(db_manager);

    gboolean has_country_filter = (country_filter != NULL && strlen(country_filter) > 0);

    GHashTable *artists_table = get_artist_table(artist_manager);
    GHashTable *musics_table = get_music_table(music_manager);

    GHashTable *discography_duration = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free);

    // Itera sobre as músicas e calcula a duração total para cada artista
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, musics_table);

    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        Music *music = (Music *)value;

        // Obtém e calcula a duração
        char *duration = get_music_duration(music);
        int duration_in_seconds = duration_to_seconds(duration);
        free(duration); // Libera a duração duplicada
        if (duration_in_seconds < 0)
        {
            continue;
        }

        // Obtém os IDs dos artistas
        char **artist_ids = get_music_artist_id(music);
        for (int i = 0; artist_ids[i] != NULL; i++)
        {
            char *artist_id = artist_ids[i];
            Artist *artist = g_hash_table_lookup(artists_table, artist_id);

            if (!artist)
            {
                continue;
            }

            // Aplica o filtro de país, se necessário
            char *country = get_artist_country(artist);
            if (has_country_filter && strcmp(country, country_filter) != 0)
            {
                free(country); // Libera o país duplicado
                continue;
            }
            free(country); // Libera o país duplicado mesmo sem filtro

            // Calcula a duração total
            int *total_duration = g_hash_table_lookup(discography_duration, artist_id);
            if (!total_duration)
            {
                total_duration = malloc(sizeof(int));
                *total_duration = 0;
                g_hash_table_insert(discography_duration, g_strdup(artist_id), total_duration);
            }
            *total_duration += duration_in_seconds;
        }

        for (int i = 0; artist_ids[i] != NULL; i++)
        {
            free(artist_ids[i]);
        }
        free(artist_ids);
    }

    // Converte a hashtable em lista ligada
    GList *artist_list = NULL;
    g_hash_table_iter_init(&iter, discography_duration);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        artist_list = g_list_prepend(artist_list, key);
    }

    // Ordena os artistas por duração de discografia e, em caso de empate, pelo ID
    artist_list = g_list_sort_with_data(artist_list, (GCompareDataFunc)compare_artists, discography_duration);

    // Escreve os N artistas com maior discografia no arquivo de saída
    int count = 0;
    for (GList *a = artist_list; a != NULL && count < N; a = a->next, count++)
    {
        char *artist_id = (char *)a->data;
        Artist *artist = g_hash_table_lookup(artists_table, artist_id);
        int *duration = g_hash_table_lookup(discography_duration, artist_id);
        char *artist_name = get_artist_name(artist);
        remove_quotes(artist_name);
        char *artist_type = get_artist_type(artist);
        char *artist_country = get_artist_country(artist);
        remove_quotes(artist_country);

        char *formatted_duration = format_duration(*duration);
        fprintf(output, "%s%c%s%c%s%c%s\n",
                artist_name, separator, artist_type, separator,
                formatted_duration, separator, artist_country);

        free(formatted_duration);
        free(artist_name);
        free(artist_type);
        free(artist_country);
    }
//
    g_list_free(artist_list);
    g_hash_table_destroy(discography_duration);
}