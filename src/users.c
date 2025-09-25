#include "../include/users.h"

struct date
{
    int year;
    int month;
    int day;
};

struct user
{
    char *username;
    char *email;
    char *first_name;
    char *last_name;
    Date *birth_date;
    char *country;
    char *subscription_type;
    char **liked_musics_id;
};

User *create_users_from_line(char *linha, Music_Manager *music_table, FILE *users_errors)
{
    User *new_user = init_user();
    if (new_user == NULL)
    {
        printf("Erro ao alocar memória para o usuário.\n");
        return NULL;
    }

    char *aux = strdup(linha);
    char *aux2 = aux;

    int length = strlen(aux2);
    if (aux2[length - 1] == '\n')
    {
        aux2[length - 1] = '\0';
    }

    char *token;

    token = strsep(&aux, ";");
    set_user_username(new_user, token);

    token = strsep(&aux, ";");
    remove_quotes(token);
    if (set_user_email(new_user, token) == 0)
    {
        fprintf(users_errors, "%s\n", linha);
        free(aux2);
        free_user(new_user);
        return NULL;
    }

    token = strsep(&aux, ";");
    set_user_first_name(new_user, token);

    token = strsep(&aux, ";");
    set_user_last_name(new_user, token);

    token = strsep(&aux, ";");
    if (token)
    {
        remove_quotes(token);
        if (set_user_birth_date(new_user, token) == 0)
        {
            fprintf(users_errors, "%s\n", linha);
            free_user(new_user);
            free(aux2);
            return NULL;
        }
    }

    token = strsep(&aux, ";");
    set_user_country(new_user, token);

    token = strsep(&aux, ";");
    remove_quotes(token);
    if (set_user_subscription_type(new_user, token) == 0)
    {
        fprintf(users_errors, "%s\n", linha);
        free(aux2);
        free_user(new_user);
        return NULL;
    }

    token = strsep(&aux, ";");
    if (token)
    {
        // Contagem de IDs de músicas para alocação
        int music_count = 0;
        char *count = strdup(token);
        char *count_copy = count;
        char *piece;

        // número de músicas
        while ((piece = strsep(&count, ", ")))
        {
            if (strlen(piece) == 0)
                continue;
            else
                music_count++;
        }

        free(count_copy);
        remove_quotes(token);
        set_user_liked_musics_id(new_user, token, music_count);
    }

    // Validação dos liked_musics_id
    if (validate_user_liked_musics(new_user, music_table) != 0)
    {
        fprintf(users_errors, "%s\n", linha);
        free(aux2);
        free_user(new_user);
        return NULL;
    }

    free(aux2);
    return new_user;
}

char *get_user_username(User *user)
{
    return strdup(user->username);
}

char *get_user_email(User *user)
{
    return strdup(user->email);
}

char *get_user_first_name(User *user)
{
    return strdup(user->first_name);
}

char *get_user_last_name(User *user)
{
    return strdup(user->last_name);
}

Date *get_user_birth_date(User *user)
{
    return user->birth_date;
}

int get_user_birth_year(User *user)
{
    return user->birth_date->year;
}

int get_user_birth_month(User *user)
{
    return user->birth_date->month;
}

int get_user_birth_day(User *user)
{
    return user->birth_date->day;
}

char *get_user_country(User *user)
{
    return strdup(user->country);
}

char *get_user_subscription_type(User *user)
{
    return strdup(user->subscription_type);
}

char **get_user_liked_musics_id(User *user)
{
    if (user->liked_musics_id == NULL)
    {
        return NULL;
    }
    int count = 0;
    while (user->liked_musics_id[count] != NULL)
    {
        count++;
    }

    char **copy = malloc((count + 1) * sizeof(char *));
    for (int i = 0; i < count; i++)
    {
        copy[i] = strdup(user->liked_musics_id[i]);
    }
    copy[count] = NULL;

    return copy;
}

void set_user_username(User *user, char *username)
{
    remove_quotes(username);
    user->username = malloc(strlen(username) + 1);
    strcpy(user->username, username);
}

int set_user_email(User *user, char *email)
{
    if (!is_valid_email(email))
    {
        return 0;
    }

    user->email = malloc(strlen(email) + 1);
    if (user->email == NULL)
    {
        return 0;
    }

    strcpy(user->email, email);
    return 1;
}

void set_user_first_name(User *user, char *first_name)
{
    remove_quotes(first_name);
    user->first_name = malloc(strlen(first_name) + 1);
    strcpy(user->first_name, first_name);
}

void set_user_last_name(User *user, char *last_name)
{
    remove_quotes(last_name);
    user->last_name = malloc(strlen(last_name) + 1);
    strcpy(user->last_name, last_name);
}

int set_user_birth_date(User *user, char *birth_date)
{

    if (!is_valid_date(birth_date))
    {
        return 0;
    }

    int year = 0;
    int month = 0;
    int day = 0;

    if ((sscanf(birth_date, "%04d/%02d/%02d", &year, &month, &day)) == 3)
    {
        user->birth_date = malloc(sizeof(struct date));
        if (user->birth_date == NULL)
        {
            return 0;
        }
        user->birth_date->year = year;
        user->birth_date->month = month;
        user->birth_date->day = day;
    }

    return 1;
}

void set_user_country(User *user, char *country)
{
    remove_quotes(country);
    user->country = malloc(strlen(country) + 1);
    strcpy(user->country, country);
}

int set_user_subscription_type(User *user, char *subscription_type)
{
    to_lowercase(subscription_type);

    if (strcmp(subscription_type, "premium") == 0 || strcmp(subscription_type, "normal") == 0)
    {
        user->subscription_type = strdup(subscription_type);
        return 1;
    }
    else
        return 0;
}

void set_user_liked_musics_id(User *user, char *liked_musics_ids, int num_musics)
{
    user->liked_musics_id = malloc((num_musics + 1) * sizeof(char *));

    char *token = strdup(liked_musics_ids);
    char *token_aux = token;
    int i = 0;

    while ((token_aux = strsep(&liked_musics_ids, ", ")))
    {
        if (strlen(token_aux) == 0)
        {
            continue;
        }

        remove_brackets(token_aux);
        user->liked_musics_id[i] = strdup(token_aux);
        i++;
    }

    user->liked_musics_id[i] = NULL; // Termina o array com NULL
    free(token);
}

int calculate_age(User *birth_date)
{
    if (birth_date == NULL)
        return -1;

    int current_year = 2024;
    int current_month = 9;
    int current_day = 9;
    Date *date = get_user_birth_date(birth_date);
    if (date == NULL)
        return -1;

    int age = current_year - date->year;

    if (date->month > current_month ||
        (date->month == current_month && date->day > current_day))
    {
        age--;
    }

    return age;
}


User *init_user()
{
    User *new_user = malloc(sizeof(User));

    new_user->username = NULL;
    new_user->email = NULL;
    new_user->first_name = NULL;
    new_user->last_name = NULL;
    new_user->birth_date = NULL;
    new_user->country = NULL;
    new_user->subscription_type = NULL;
    new_user->liked_musics_id = NULL;

    return new_user;
}

void free_user(User *user)
{
    if (user == NULL)
        return;

    if (user->username)
    {
        free(user->username);
    }
    if (user->email)
    {
        free(user->email);
    }
    if (user->first_name)
    {
        free(user->first_name);
    }
    if (user->last_name)
    {
        free(user->last_name);
    }

    if (user->birth_date)
    {
        free(user->birth_date);
    }
    if (user->country)
    {
        free(user->country);
    }
    if (user->subscription_type)
    {
        free(user->subscription_type);
    }

    if (user->liked_musics_id)
    {
        for (int i = 0; user->liked_musics_id[i] != NULL; i++)
        {
            free(user->liked_musics_id[i]);
        }
        free(user->liked_musics_id);
    }

    free(user);
}