#include "../include/query6.h"

/*void query6(Database_Manager *db_manager, char *user_id, int year, int N, FILE *output, char separator)
{
    Music_Manager *music_manager = get_music_manager(db_manager);
    History_Manager *history_manager = get_history_manager(db_manager);

    GHashTable *music_table = get_music_table(music_manager);
    GHashTable *history_table = get_history_table(history_manager);

    int tempo_ouvido = 0, musicas = 0;

    GHashTable *processed_music_ids = g_hash_table_new_full(g_str_hash, g_str_equal, free, NULL);
    GHashTable *album_count = g_hash_table_new_full(g_str_hash, g_str_equal, free, free);
    GHashTable *genre_count = g_hash_table_new_full(g_str_hash, g_str_equal, free, free);
    GHashTable *artist_info = g_hash_table_new_full(g_str_hash, g_str_equal, free ,free);
    GHashTable *day_play_count = g_hash_table_new_full(g_str_hash, g_str_equal, free, free);
    GHashTable *hour_play_time = g_hash_table_new_full(g_str_hash, g_str_equal, free, free);

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, history_table);

    while(g_hash_table_iter_next(&iter, &key, &value))
    {
        History *history = (History *)value;

        if (strcmp(user_id, get_history_user_id(history)) != 0)
        {
            continue;
        }

        char *timestamp = get_history_timestamp(history);
        int year_history = get_year(timestamp);
        if (year_history != year)
        {
            continue;
        }

        char *duration = get_history_duration(history);
        tempo_ouvido += duration_to_seconds(duration);

        char *music_id = get_history_music_id(history);

        if (!g_hash_table_contains(processed_music_ids, music_id))
        {
            g_hash_table_insert(processed_music_ids, strdup(music_id), NULL);
            musicas++;
        }

        Music *music = g_hash_table_lookup(music_table, music_id);

        if (music != NULL)
        {
            char day[11];
            strncpy(day, timestamp, 10);
            day[10] = '\0';

            int *day_count = g_hash_table_lookup(day_play_count, day);
            if (day_count == NULL)
            {
                int *new_count = malloc(sizeof(int));
                *new_count = 1;
                g_hash_table_insert(day_play_count, strdup(day), new_count);
            }
            else
            {
                (*day_count)++;
            }

            char hour[3];
            strncpy(hour, timestamp + 11, 2);
            hour[2] = '\0';

            int *hour_time = g_hash_table_lookup(hour_play_time, hour);
            int seconds = duration_to_seconds(duration);
            if (hour_time == NULL)
            {
                int *new_time = malloc(sizeof(int));
                *new_time = seconds;
                g_hash_table_insert(hour_play_time, strdup(hour), new_time);
            }
            else
            {
                (*hour_time) += seconds;
            }

            char *album_id = get_music_album_id(music);
            if (album_id != NULL)
            {
                int *count = g_hash_table_lookup(album_count, album_id);
                if (count == NULL)
                {
                    int *new_count = malloc(sizeof(int));
                    *new_count = 1;
                    g_hash_table_insert(album_count, strdup(album_id), new_count);
                }
                else
                {
                    (*count)++;
                }
            }

            char *genre = get_music_genre(music);
            remove_quotes(genre);
            if (genre != NULL)
            {
                int *count = g_hash_table_lookup(genre_count, genre);
                if (count == NULL)
                {
                    int *new_count = malloc(sizeof(int));
                    *new_count = 1;
                    g_hash_table_insert(genre_count, strdup(genre), new_count);
                }
                else
                {
                    (*count)++;
                }
            }

            char **artists_ids = get_music_artist_id(music);
            if (artists_ids != NULL)
            {
                for (int i = 0; artists_ids[i] != NULL; i++)
                {
                    char *artist_id = artists_ids[i];
                    int *existing_info = g_hash_table_lookup(artist_info, artist_id);

                    if (existing_info == NULL)
                    {
                        int *info = malloc(2 * sizeof(int));
                        if (info == NULL)
                        {
                            printf("Erro de alocação de memória para info\n");
                            g_strfreev(artists_ids);
                            g_hash_table_destroy(artist_info);
                            return;
                        }
                        info[0] = 1;
                        info[1] = duration_to_seconds(duration);
                        g_hash_table_insert(artist_info, strdup(artist_id), info);
                    }
                    else
                    {
                        existing_info[1] += duration_to_seconds(duration);

                        if (!g_hash_table_contains(processed_music_ids, music_id))
                        {
                            existing_info[0] += 1;
                        }
                    }
                }
                g_strfreev(artists_ids);
            }
        }
    }

    g_hash_table_destroy(processed_music_ids);

    if (tempo_ouvido == 0)
    {
        fprintf(output, "\n");
        g_hash_table_destroy(album_count);
        g_hash_table_destroy(genre_count);
        g_hash_table_destroy(artist_info);
        g_hash_table_destroy(day_play_count);
        g_hash_table_destroy(hour_play_time);
        return;
    }

    char *most_listened_artist = NULL;
    int max_listened_time = 0;
    GHashTableIter artist_iter;
    gpointer artist_key, artist_value;
    g_hash_table_iter_init(&artist_iter, artist_info);

    while (g_hash_table_iter_next(&artist_iter, &artist_key, &artist_value))
    {
        char *artist_id = (char *)artist_key;
        int *info = (int *)artist_value;

        int listened_time = info[1];

        if (listened_time > max_listened_time || 
            (listened_time == max_listened_time && 
            (most_listened_artist == NULL || strcmp(artist_id, most_listened_artist) < 0)))
        {
            max_listened_time = listened_time;
            most_listened_artist = artist_id;
        }
    }

    char *favorite_genre = NULL;
    int max_genre_count = 0;
    GHashTableIter genre_iter;
    gpointer genre_key, genre_value;
    g_hash_table_iter_init(&genre_iter, genre_count);
    while (g_hash_table_iter_next(&genre_iter, &genre_key, &genre_value))
    {
        int *count = (int *)genre_value;
        if (*count > max_genre_count || (*count == max_genre_count &&
            (favorite_genre == NULL || strcmp((char *)genre_key, favorite_genre) < 0)))
        {
            max_genre_count = *count;
            favorite_genre = (char *)genre_key;
        }
    }

    char *favorite_album = NULL;
    int max_album_count = 0;
    GHashTableIter album_iter;
    gpointer album_key, album_value;
    g_hash_table_iter_init(&album_iter, album_count);
    while (g_hash_table_iter_next(&album_iter, &album_key, &album_value))
    {
        int *count = (int *)album_value;
        if (*count > max_album_count || (*count == max_album_count && 
            (favorite_album == NULL  || strcmp((char *)album_key, favorite_album) < 0)))
        {
            max_album_count = *count;
            favorite_album = (char *)album_key;
        }
    }

    char *top_day = NULL;
    int max_plays = 0;

    GHashTableIter day_iter;
    gpointer day_key, day_value;
    g_hash_table_iter_init(&day_iter, day_play_count);
    while (g_hash_table_iter_next(&day_iter, &day_key, &day_value))
    {
        int *count = (int *)day_value;
        char *current_day = (char *)day_key;

        if (*count > max_plays || (*count == max_plays && 
            (top_day == NULL || strcmp(current_day, top_day) > 0)))
        {
            max_plays = *count;
            top_day = current_day;
        }
    }

    char *top_hour = NULL;
    int max_time = 0;

    GHashTableIter hour_iter;
    gpointer hour_key, hour_value;
    g_hash_table_iter_init(&hour_iter, hour_play_time);
    while (g_hash_table_iter_next(&hour_iter, &hour_key, &hour_value))
    {
        int *time = (int *)hour_value;
        char *current_hour = (char *)hour_key;

        if (*time > max_time || (*time == max_time && 
            (top_hour == NULL || strcmp(current_hour, top_hour) < 0)))
        {
            max_time = *time;
            top_hour = current_hour;
        }
    }

    char *tempo_total = format_duration(tempo_ouvido);

    fprintf(output, "%s%c%d%c%s%c%s%c%s%c%s%c%s\n", tempo_total, separator, musicas, separator, most_listened_artist, separator, top_day, separator, favorite_genre, separator, favorite_album, separator, top_hour);

    if (N != -1)
    {
        GList *sorted_artists = NULL;

        // Preencher a lista com os artistas e seus dados
        GHashTableIter artists_iter;
        gpointer artists_key, artists_value;
        g_hash_table_iter_init(&artists_iter, artist_info);
        while (g_hash_table_iter_next(&artists_iter, &artists_key, &artists_value))
        {
            char *artist_id = (char *)artists_key;
            int *info = (int *)artists_value;

            int *artist_data = malloc(3 * sizeof(int));
            artist_data[0] = info[0];  // Músicas distintas
            artist_data[1] = info[1];  // Tempo total
            artist_data[2] = (int)artist_id;

            sorted_artists = g_list_insert_sorted(sorted_artists, artist_data, ordena_artists_id);
        }

        // Imprimir até N artistas
        int printed = 0;
        for (GList *iter = sorted_artists; iter != NULL && printed < N; iter = iter->next)
        {
            int *artist_data = (int *)iter->data;
            char *formatted_time = format_duration(artist_data[1]);
            char *artist_id = (char *)artist_data[2];

            fprintf(output, "%s%c%d%c%s\n", artist_id, separator, artist_data[0], separator, formatted_time);
            free(formatted_time);

            printed++;
        }

        // Limpar a lista de artistas ordenados
        g_list_free_full(sorted_artists, free);
    }

    free(tempo_total);
    g_hash_table_destroy(album_count);
    g_hash_table_destroy(genre_count);
    g_hash_table_destroy(artist_info);
}*/