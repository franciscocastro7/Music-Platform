#include "../include/musicsmanager.h"

struct music_manager
{
    GHashTable *musics_table;
};

Music_Manager *ParseMusics(char **parsed_musics, Artist_Manager *artist_manager, Album_Manager *album_manager, FILE *musics_errors)
{
    if (parsed_musics == NULL)
    {
        printf("Array de músicas inválido.\n");
        return NULL;
    }

    Music_Manager *music_manager = malloc(sizeof(Music_Manager));
    if (music_manager == NULL)
    {
        printf("Erro ao alocar memória para music_manager.\n");
        return NULL;
    }

    // Inicializar a tabela de músicas
    music_manager->musics_table = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_music);

    int i = 0;
    while (parsed_musics[i] != NULL)
    {
        Music *new_music = create_music_from_line(parsed_musics[i], artist_manager, album_manager, musics_errors);
        if (new_music != NULL)
        {
            char *music_id = get_music_id(new_music);
            if (music_id)
            {
                g_hash_table_insert(music_manager->musics_table, g_strdup(music_id), new_music);
                free(music_id);
            }
            else
            {
                fprintf(musics_errors, "ID inválido");
                free(music_id);
                free_music(new_music);
            }
        }
        i++;
    }
    puts("Catálogo de músicas preenchido.");
    free_parser(parsed_musics);
    return music_manager;
}

// Retorna a tabela de músicas
GHashTable *get_music_table(Music_Manager *music_manager)
{
    return music_manager->musics_table;
}

void free_music_manager(Music_Manager *music_manager)
{
    if (music_manager != NULL)
    {
        g_hash_table_destroy(music_manager->musics_table); // Libera a tabela de músicas
        free(music_manager);                               // Libera a memória do manager
    }
}