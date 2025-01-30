#include "../include/history.h"

struct history
{
    char *id;
    char *user_id;
    char *music_id;
    char *timestamp;
    char *duration;
    char *platform;
};

History *create_history_from_line(char *linha, User_Manager *user_table, Music_Manager *music_table, FILE *history_errors)
{
    History *new_history = init_history();
    if (new_history == NULL)
        return NULL;

    char *aux = strdup(linha);
    char *aux2 = aux;
    char *token;

    // ID do History
    token = strsep(&aux, ";");
    remove_quotes(token);
    set_history_id(new_history, token);

    // ID do Usuário
    token = strsep(&aux, ";");
    remove_quotes(token);
    set_history_user_id(new_history, token);

    // ID da Música
    token = strsep(&aux, ";");
    remove_quotes(token);
    set_history_music_id(new_history, token);

    // Timestamp
    token = strsep(&aux, ";");
    remove_quotes(token);
    if (set_history_timestamp(new_history, token) == 0)
    {
        fprintf(history_errors, "%s\n", linha);
        free(aux2);
        free_history(new_history);
        return NULL;
    }

    // Duração
    token = strsep(&aux, ";");
    remove_quotes(token);
    if (set_history_duration(new_history, token) == 0)
    {
        fprintf(history_errors, "%s\n", linha);
        free(aux2);
        free_history(new_history);
        return NULL;
    }

    // Platform com Validação
    token = strsep(&aux, ";");
    remove_quotes(token);
    if (!set_history_platform(new_history, token))
    {
        // Se o platform for inválido, grava o erro no arquivo e retorna NULL
        fprintf(history_errors, "%s\n", linha);
        free(aux2);
        free_history(new_history);
        return NULL;
    }

    // Finaliza o parsing
    free(aux2);
    return new_history;
}

// Getters
char *get_history_id(History *history)
{
    return strdup(history->id);
}

char *get_history_user_id(History *history)
{
    return strdup(history->user_id);
}

char *get_history_music_id(History *history)
{
    return strdup(history->music_id);
}

char *get_history_timestamp(History *history)
{
    return strdup(history->timestamp);
}

char *get_history_duration(History *history)
{
    return history->duration;
}

char *get_history_platform(History *history)
{
    return strdup(history->platform);
}


// Função auxiliar para extrair o ano de um timestamp no formato "YYYY-MM-DD HH:MM:SS"
int extract_year_from_timestamp(const char *timestamp)
{
    if (!timestamp)
        return -1; // Retorna -1 para timestamps inválidos

    int year;
    sscanf(timestamp, "%4d", &year); // Extrai os primeiros 4 caracteres como ano
    return year;
}

// Função 1: Obter a lista de músicas que um usuário ouviu em um determinado ano
char **get_user_music_list(History **histories, int total_histories, const char *user_id, int year, int *result_size)
{
    char **music_list = NULL;
    *result_size = 0;

    for (int i = 0; i < total_histories; i++)
    {
        History *history = histories[i];
        if (!history)
            continue;

        if (strcmp(get_history_user_id(history), user_id) == 0 && extract_year_from_timestamp(get_history_timestamp(history)) == year)
        {
            // Adiciona o ID da música à lista
            music_list = realloc(music_list, (*result_size + 1) * sizeof(char *));
            music_list[*result_size] = strdup(get_history_music_id(history));
            (*result_size)++;
        }
    }

    return music_list;
}

/*int get_music_play_time(History **histories, int total_histories, const char *music_id)
{
    int total_time = 0;

    for (int i = 0; i < total_histories; i++)
    {
        History *history = histories[i];
        if (!history)
            continue;

        if (strcmp(get_history_music_id(history), music_id) == 0)
        {
            total_time += get_history_duration(history);
        }
    }

    return total_time;
}

char *get_music_play_hour(History **histories, int total_histories, const char *music_id)
{
    int total_seconds = get_music_play_time(histories, total_histories, music_id);

    int hours = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int seconds = total_seconds % 60;

    char *formatted_time = malloc(9 * sizeof(char)); // HH:MM:SS precisa de 8 caracteres + '\0'
    sprintf(formatted_time, "%02d:%02d:%02d", hours, minutes, seconds);

    return formatted_time;
}*/


// Setters
void set_history_id(History *history, char *id)
{
    remove_quotes(id);
    history->id = malloc(strlen(id) + 1);
    strcpy(history->id, id);
}

void set_history_user_id(History *history, char *user_id)
{
    remove_quotes(user_id);
    history->user_id = malloc(strlen(user_id) + 1);
    strcpy(history->user_id, user_id);
}

void set_history_music_id(History *history, char *music_id)
{
    remove_quotes(music_id);
    history->music_id = malloc(strlen(music_id) + 1);
    strcpy(history->music_id, music_id);
}

int set_history_timestamp(History *history, char *timestamp)
{
    remove_quotes(timestamp);
    
    // Separar a data e a hora
    char *space_ptr = strchr(timestamp, ' ');
    if (!space_ptr) {
        return 0; // Retorna 0 se não houver separador entre data e hora
    }

    // Dividir em data e hora
    *space_ptr = '\0';
    char *date_part = timestamp;
    char *time_part = space_ptr + 1;

    // Validar a data e a hora
    if (!is_valid_date(date_part) || !is_valid_duration(time_part)) {
        *space_ptr = ' '; // Restaurar o separador original
        return 0; // Retorna 0 se a data ou a hora forem inválidas
    }

    // Restaurar o separador original e alocar memória para o timestamp
    *space_ptr = ' ';
    history->timestamp = malloc(strlen(timestamp) + 1);
    if (!history->timestamp) {
        return 0; // Retorna 0 em caso de falha na alocação
    }
    
    // Copiar o timestamp inteiro
    strcpy(history->timestamp, timestamp);

    return 1; // Retorna 1 se tudo estiver válido
}

int set_history_duration(History *history, char *duration)
{
    remove_quotes(duration);
    if (is_valid_duration(duration))
    {
        history->duration = malloc(strlen(duration) + 1);
        if (history->duration == NULL)
        {
            printf("Erro ao alocar memória para a duração.\n");
            return 0;
        }
        strcpy(history->duration, duration);
        return 1;
    }
    else
    {
        return 0;
    }
}

int set_history_platform(History *history, char *platform)
{
    if (!platform || !history)
        return 0; // Verifica valores nulos

    // Validação dos valores permitidos (case-insensitive)
    if (strcasecmp(platform, "mobile") == 0 || strcasecmp(platform, "desktop") == 0)
    {
        // Libera memória previamente alocada, se necessário
        free(history->platform);

        // Duplica o valor original fornecido
        history->platform = strdup(platform);
        if (!history->platform)
            return 0; // Verifica falha na alocação

        return 1; // Sucesso
    }

    return 0; // Valor inválido
}

History *init_history()
{
    History *new_history = malloc(sizeof(History));
    if (new_history == NULL)
    {
        printf("Erro ao alocar memória para histórico.\n");
        return NULL;
    }

    new_history->id = NULL;
    new_history->user_id = NULL;
    new_history->music_id = NULL;
    new_history->timestamp = NULL;
    new_history->duration = NULL;
    new_history->platform = NULL;

    return new_history;
}

// Função para liberar memória de um histórico
void free_history(History *history)
{
    if (history == NULL)
        return;

    if (history->id != NULL)
        free(history->id);
    if (history->user_id != NULL)
        free(history->user_id);
    if (history->music_id != NULL)
        free(history->music_id);
    if (history->timestamp != NULL)
        free(history->timestamp);
    if (history->duration != NULL)
        free(history->duration);
    if (history->platform != NULL)
        free(history->platform);

    free(history);
}
