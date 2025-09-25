#include "../include/history.h"
#include "../include/historymanager.h"

struct history_manager
{
    GHashTable *history_table;
};

History_Manager *ParseHistory(char **parsed_history, User_Manager *user_manager, Music_Manager *music_manager, FILE *history_errors)
{
    if (parsed_history == NULL)
    {
        printf("Array de históricos inválido.\n");
        return NULL;
    }

    History_Manager *history_manager = malloc(sizeof(History_Manager));
    if (history_manager == NULL)
    {
        printf("Erro ao alocar memória para history_manager.\n");
        return NULL;
    }

    // Inicializar a tabela de históricos
    history_manager->history_table = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_history);

    int i = 0;
    while (parsed_history[i] != NULL)
    {
        // Criar um novo registro de histórico a partir da linha
        History *new_history = create_history_from_line(parsed_history[i], user_manager, music_manager, history_errors);
        if (new_history != NULL)
        {
            char *history_id = get_history_id(new_history);
            if (history_id)
            {
                g_hash_table_insert(history_manager->history_table, g_strdup(history_id), new_history);
                free(history_id);
            }
            else
            {
                fprintf(history_errors, "ID inválido: %s\n", parsed_history[i]);
                free(history_id);
                free_history(new_history);
            }
        }
        i++;
    }

    puts("Catálogo de históricos preenchido.");

    // Libera a memória de parsed_history apenas após o uso completo
    free_parser(parsed_history);
    
    return history_manager;
}

// Retorna a tabela de históricos
GHashTable *get_history_table(History_Manager *history_manager)
{
    return history_manager->history_table;
}

// Libera a memória do manager
void free_history_manager(History_Manager *history_manager)
{
    if (history_manager != NULL)
    {
        g_hash_table_destroy(history_manager->history_table); // Libera a tabela de históricos
        free(history_manager);                                // Libera o próprio manager
    }
}