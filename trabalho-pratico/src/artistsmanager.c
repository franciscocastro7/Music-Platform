#include "../include/artistsmanager.h"

struct artist_manager
{
    GHashTable *artists_table;
};

Artist_Manager *ParseArtists(char **parsed_artists, FILE *artists_errors)
{
    if (parsed_artists == NULL)
    {
        printf("Array de artistas inválido.\n");
        return NULL;
    }

    Artist_Manager *artist_manager = malloc(sizeof(Artist_Manager));
    if (artist_manager == NULL)
    {
        printf("Erro ao alocar memória para artist_manager.\n");
        return NULL;
    }

    // Inicializar a tabela de artistas
    artist_manager->artists_table = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_artist);

    int i = 0;
    while (parsed_artists[i] != NULL) {
        Artist *new_artist = create_artist_from_line(parsed_artists[i], artists_errors);

        if (new_artist != NULL) {
            char *artist_id = get_artist_id(new_artist);

            if (artist_id != NULL) {
                g_hash_table_insert(artist_manager->artists_table, g_strdup(artist_id), new_artist);
                free(artist_id);
            } else {
                //fprintf(artists_errors, "ID inválido para artista na linha %d\n", i + 1);
                free_artist(new_artist); // Libera todos os recursos associados ao artista
            }
        } else {
            //fprintf(artists_errors, "Falha ao criar artista na linha %d\n", i + 1);
        }

        i++;
    }
    puts("Catálogo de artistas preenchido.");
    free_parser(parsed_artists);
    return artist_manager;
}

// Alteração: função agora retorna a tabela de artistas
GHashTable *get_artist_table(Artist_Manager *artist_manager)
{
    return artist_manager->artists_table;
}

void free_artist_manager(Artist_Manager *artist_manager)
{
    if (artist_manager != NULL)
    {
        g_hash_table_destroy(artist_manager->artists_table); // Libera a tabela de artistas
        free(artist_manager);                                // Libera a memória do manager
    }
}