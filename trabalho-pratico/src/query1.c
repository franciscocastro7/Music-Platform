#include "../include/query1.h"

void query1(Database_Manager *db_manager, char *user_id, char *artist_id, FILE *output, char separator)
{
    if (user_id != NULL && artist_id == NULL)
    {
        User_Manager *user_manager = get_user_manager(db_manager);
        GHashTable *users_table = get_user_table(user_manager);

        User *user = g_hash_table_lookup(users_table, user_id);

        if (user == NULL) 
        {
            fprintf(output, "\n");
            return;
        }

        char *email = get_user_email(user);
        char *first_name = get_user_first_name(user);
        char *last_name = get_user_last_name(user);
        int age = calculate_age(user);
        char *country = get_user_country(user);

        fprintf(output, "%s%c%s%c%s%c%d%c%s\n", 
                email, separator, first_name, separator, last_name, 
                separator, age, separator, country);

        free(email);
        free(first_name);
        free(last_name);
        free(country);
    }
    else
    {
        Artist_Manager *artist_manager = get_artist_manager(db_manager);
        History_Manager *history_manager = get_history_manager(db_manager);
        Music_Manager *music_manager = get_music_manager(db_manager);
        Album_Manager *album_manager = get_album_manager(db_manager);

        GHashTable *artists_table = get_artist_table(artist_manager);
        GHashTable *history_table = get_history_table(history_manager);
        GHashTable *music_table = get_music_table(music_manager);
        GHashTable *album_table = get_album_table(album_manager);

        Artist *artist = g_hash_table_lookup(artists_table, artist_id);

        if (artist == NULL)
        {
            fprintf(output, "\n");
            return;
        }

        char *name = get_artist_name(artist);
        remove_quotes(name);
        char *type = get_artist_type(artist);
        char *country = get_artist_country(artist);
        remove_quotes(country);
        float recipe_per_stream = get_artist_recipe_per_stream(artist);
        float total_recipe = 0.0;
        int num_albums_idividuais = 0, num_reproducoes = 0;

        GHashTable *processed_albums = g_hash_table_new(g_str_hash, g_str_equal);
        GHashTable *music_info = g_hash_table_new_full(g_str_hash, g_str_equal, free, free);

        GHashTableIter iter;
        gpointer key, value;

        g_hash_table_iter_init(&iter, history_table);
        while (g_hash_table_iter_next(&iter, &key, &value))
        {
            History *history = (History *)value;

            char *music_id = get_history_music_id(history);

            Music *music = g_hash_table_lookup(music_table, music_id);
            if (music != NULL)
            {
                char **music_artists_ids = get_music_artist_id(music);
                int num_artists = 0;
                while (music_artists_ids[num_artists] != NULL)
                {
                    num_artists++;
                }

                if (!artist_id_igual(music_artists_ids, artist_id))
                {
                    for (int i = 0; music_artists_ids[i] != NULL; i++) {
                        free(music_artists_ids[i]);
                    }
                    free(music_artists_ids);
                    free(music_id);
                    continue;
                }

                int *existing_value = g_hash_table_lookup(music_info, music_id);
                if (existing_value == NULL)
                {
                    int *info = malloc(2 * sizeof(int));
                    if (info == NULL)
                    {
                        printf("Erro de alocação de memória para info\n");
                        for (int i = 0; music_artists_ids[i] != NULL; i++) {
                            free(music_artists_ids[i]);
                        }
                        free(music_artists_ids);
                        free(music_id);
                        return;
                    }
                    info[0] = num_artists;
                    info[1] = 1;
                    g_hash_table_insert(music_info, strdup(music_id), info);
                }
                else
                {
                    existing_value[1] += 1;
                }

                char *album_id = get_music_album_id(music);
                Album *album = g_hash_table_lookup(album_table, album_id);

                char **album_artists_ids = get_album_artist_id(album);
                if (!artist_id_igual(album_artists_ids, artist_id))
                {
                    for (int i = 0; album_artists_ids[i] != NULL; i++) {
                        free(album_artists_ids[i]);
                    }
                    free(album_artists_ids);
                    free(album_id); // Libera memória aqui antes de continuar
                    continue;
                }
                if (!g_hash_table_contains(processed_albums, album_id))
                {
                    g_hash_table_insert(processed_albums, album_id, album_id);
                }
                else 
                {
                    free(album_id); // Libera se não for inserido na tabela
                }
                for (int i = 0; album_artists_ids[i] != NULL; i++) {
                    free(album_artists_ids[i]);
                }
                free(album_artists_ids);

                if (album != NULL)
                {
                    if (strcmp(type, "group") == 0 || (strcmp(type, "individual") == 0 && num_artists == 1))
                    {
                        num_reproducoes++;
                    }
                }
                for (int i = 0; music_artists_ids[i] != NULL; i++) {
                    free(music_artists_ids[i]);
                }
                free(music_artists_ids);
            }
            free(music_id);
        }

        total_recipe = num_reproducoes * recipe_per_stream;
        num_albums_idividuais = g_hash_table_size(processed_albums);

        if (strcmp(type, "individual") == 0)
        {
            GHashTableIter music_iter;
            gpointer music_key, music_value;

            g_hash_table_iter_init(&music_iter, music_info);
            while (g_hash_table_iter_next(&music_iter, &music_key, &music_value))
            {
                int *info = (int *)music_value;

                if (info[0] > 1)
                {
                    float calculo = (info[1] * recipe_per_stream) / info[0];
                    total_recipe += calculo;
                }
            }
        }

        fprintf(output, "%s%c%s%c%s%c%d%c%.2f\n", name, separator, type, separator, country, separator, num_albums_idividuais, separator, total_recipe);

        free(name);
        free(type);
        free(country);

        g_hash_table_destroy(processed_albums);
        g_hash_table_destroy(music_info);
    }
}

