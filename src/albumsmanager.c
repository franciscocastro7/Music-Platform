#include "../include/albumsmanager.h"

struct album_manager
{
    GHashTable *albums_table;
};

Album_Manager *ParseAlbums(char **parsed_albums, Artist_Manager *artist_manager)
{
    if (parsed_albums == NULL)
    {
        printf("Array de álbums inválido.\n");
        return NULL;
    }

    Album_Manager *album_manager = malloc(sizeof(Album_Manager));
    if (album_manager == NULL)
    {
        printf("Erro ao alocar memória para album_manager.\n");
        return NULL;
    }

    // Inicializar a tabela de álbums
    album_manager->albums_table = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_album);

    int i = 0;
    FILE *error_log = fopen("albums_errors.log", "a");
    if (!error_log)
    {
        printf("Erro ao abrir arquivo de log.\n");
        free(album_manager);
        return NULL;
    }

    while (parsed_albums[i] != NULL)
    {
        Album *new_album = create_album_from_line(parsed_albums[i], artist_manager);
        if (new_album != NULL)
        {
            char *album_id = get_album_id(new_album);
            if (album_id != NULL)
            {
                g_hash_table_insert(album_manager->albums_table, g_strdup(album_id), new_album);
                free(album_id);  // Libere a memória de album_id após inserção
            }
            else
            {
                fprintf(error_log, "ID inválido para o álbum: %s\n", parsed_albums[i]);
                free_album(new_album);  // Liberar o álbum se não tiver ID válido
            }
        }
        else
        {
            // Se create_album_from_line falhou, informe o erro
            fprintf(error_log, "Erro ao criar álbum a partir da linha: %s\n", parsed_albums[i]);
        }
        i++;
    }
    fclose(error_log);
    puts("Catálogo de álbums preenchido.");
    free_parser(parsed_albums);
    return album_manager;
}

// Retorna a tabela de álbums, com verificação de ponteiro NULL
GHashTable *get_album_table(Album_Manager *album_manager)
{
    if (album_manager == NULL)
    {
        printf("Erro: album_manager não inicializado.\n");
        return NULL;  // Evita segfault caso album_manager seja NULL
    }
    return album_manager->albums_table;
}

void free_album_manager(Album_Manager *album_manager)
{
    if (album_manager != NULL)
    {
        g_hash_table_destroy(album_manager->albums_table); // Libera a tabela de álbums
        free(album_manager);                               // Libera a memória do manager
    }
}
