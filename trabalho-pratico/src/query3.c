#include "../include/query3.h"
#include "../include/database_manager.h"
#include "../include/usersmanager.h"
#include "../include/musicsmanager.h"
#include "../include/users.h"


// Passa o array para lista ligada
GList *array_to_glist(char **array)
{
    GList *list = NULL;
    for (int i = 0; array[i] != NULL; i++)
    {
        list = g_list_append(list, g_strdup(array[i]));
    }
    return list;
}

// Compara os géneros
gint compare_genres(const void *a, const void *b, gpointer user_data)
{
    GHashTable *genre_likes = (GHashTable *)user_data;

    char *genre_a = (char *)a;
    char *genre_b = (char *)b;

    int likes_a = *(int *)g_hash_table_lookup(genre_likes, genre_a);
    int likes_b = *(int *)g_hash_table_lookup(genre_likes, genre_b);

    if (likes_a != likes_b)
        return likes_b - likes_a;

    return strcmp(genre_a, genre_b);
}

void query3(Database_Manager *db_manager, int min_age, int max_age, FILE *output, char separator)
{
    User_Manager *user_manager = get_user_manager(db_manager);
    Music_Manager *music_manager = get_music_manager(db_manager);

    GHashTable *users_table = get_user_table(user_manager);
    GHashTable *musics_table = get_music_table(music_manager);

    GHashTable *genre_likes = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free);

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, users_table);

    int user_found = 0;

    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        User *user = (User *)value;
        int age = calculate_age(user);

        if (age < min_age || age > max_age)
            continue;
        user_found = 1;

        char **liked_musics_array = get_user_liked_musics_id(user);
        GList *liked_musics = array_to_glist(liked_musics_array);
        free_user_liked_musics_id(liked_musics_array);

        for (GList *l = liked_musics; l != NULL; l = l->next)
        {
            char *music_id = (char *)l->data;
            Music *music = g_hash_table_lookup(musics_table, music_id);
            if (!music)
                continue;

            char *genre = get_music_genre(music);
            if (!genre)
                continue;

            int *likes_count = g_hash_table_lookup(genre_likes, genre);
            if (!likes_count)
            {
                likes_count = malloc(sizeof(int));
                *likes_count = 0;
                g_hash_table_insert(genre_likes, g_strdup(genre), likes_count);
            }
            (*likes_count)++;
            free(genre);
        }

        g_list_free_full(liked_musics, g_free);
    }

    if (!user_found)
    {
        fprintf(output, "\n");
        g_hash_table_destroy(genre_likes);
        return;
    }

    GList *genre_list = NULL;
    g_hash_table_iter_init(&iter, genre_likes);
    while (g_hash_table_iter_next(&iter, &key, &value))
    {
        genre_list = g_list_prepend(genre_list, key);
    }

    genre_list = g_list_sort_with_data(genre_list, compare_genres, genre_likes);

    for (GList *g = genre_list; g != NULL; g = g->next)
    {
        char *genre = (char *)g->data;
        int *likes_ptr = g_hash_table_lookup(genre_likes, genre);
        int likes = *likes_ptr;
        remove_quotes(genre);
        fprintf(output, "%s%c%d\n", genre, separator, likes);
    }

    g_list_free(genre_list);
    g_hash_table_destroy(genre_likes);
}

void free_user_liked_musics_id(char **liked_musics_id)
{
    if (liked_musics_id == NULL)
        return;

    int i = 0;
    while (liked_musics_id[i] != NULL)
    {
        free(liked_musics_id[i]);
        i++;
    }

    free(liked_musics_id);
}
