#include "../include/users.h"
#include "../include/usersmanager.h"

struct user_manager
{
    GHashTable *users_table;
};

User_Manager *ParseUsers(char **parsed_users, Music_Manager *music_manager, FILE *users_errors)
{
    if (parsed_users == NULL)
    {
        printf("Array de users inválido.\n");
        return NULL;
    }

    User_Manager *user_manager = malloc(sizeof(User_Manager));
    if (user_manager == NULL)
    {
        printf("Erro ao alocar memória para music_manager.\n");
        return NULL;
    }

    user_manager->users_table = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_user);
    int i = 0;

    while (parsed_users[i] != NULL)
    {
        User *new_user = create_users_from_line(parsed_users[i], music_manager, users_errors);
        if (new_user != NULL)
        {
            char *username = get_user_username(new_user);
            if (username != NULL)
            {
                char *username_copy = g_strdup(username);
                if (username_copy)
                {
                    g_hash_table_insert(user_manager->users_table, username_copy, new_user);
                }
                else
                {
                    printf("Erro ao duplicar o username do usuário.\n");
                    free_user(new_user); 
                }
                free(username);
            }
            else
            {
                printf("Erro ao obter username do usuário.\n");
                free_user(new_user);
            }
        }
        i++;
    }
    puts("Catálogo de users preenchido.");
    free_parser(parsed_users);
    return user_manager;
}

GHashTable *get_user_table(User_Manager *user_manager)
{
    return user_manager->users_table;
}

void free_user_manager(User_Manager *user_manager)
{
    if (user_manager != NULL)
    {
        g_hash_table_destroy(user_manager->users_table); // Libera a tabela de músicas
        free(user_manager);                              // Libera a memória do manager
    }
}