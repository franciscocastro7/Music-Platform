#include "../include/utils.h"

void remove_quotes(char *str) {
    size_t len = strlen(str);
    if (len > 1 && str[0] == '"' && str[len - 1] == '"') {
        for (size_t i = 1; i < len - 1; i++) {
            str[i - 1] = str[i];
        }
        str[len - 2] = '\0';
    }
}

void remove_brackets(char *str) {
    size_t len = strlen(str);

    if (len > 1 && str[0] == '[' && str[len - 1] == ']') {
        for (size_t i = 2; i < len - 2; i++) {
            str[i - 2] = str[i];
        }
        str[len - 4] = '\0';
    } else if (len > 1 && (str[0] == '[' && str[len - 1] == '\'')) {
        for (size_t i = 2; i < len - 1; i++) {
            str[i - 2] = str[i];
        }
        str[len - 3] = '\0';
    } else if (len > 1 && (str[0] == '\'' && str[len - 1] == ']')) {
        for (size_t i = 1; i < len - 1; i++) {
            str[i - 1] = str[i];
        }
        str[len - 3] = '\0';
    } else if (len > 1 && (str[0] == '\'' && str[len - 1] == '\'')) {
        for (size_t i = 1; i < len - 1; i++) {
            str[i - 1] = str[i];
        }
        str[len - 2] = '\0';
    }
}

char *format_duration(int total_seconds)
{
    int hours = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int seconds = total_seconds % 60;

    char *formatted_duration = malloc(16);
    snprintf(formatted_duration, 16, "%02d:%02d:%02d", hours, minutes, seconds);
    return formatted_duration;
}

int duration_to_seconds(char *duration)
{
    int hours, minutes, seconds;
    int result = sscanf(duration, "%d:%d:%d", &hours, &minutes, &seconds);
    if (result != 3)
    {
        printf("Erro ao converter duração: %s\n", duration);
        return -1;
    }
    return hours * 3600 + minutes * 60 + seconds;
}

int artist_id_igual(char **artists_ids, char *artist_id)
{
    for (int i = 0; artists_ids[i] != NULL; i++)
    {
        if 
        (strcmp(artists_ids[i], artist_id) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int get_year(char *timestamp)
{
    if (timestamp == NULL || strlen(timestamp) == 0)
    {
        return -1;
    }
    char year_str[5];
    strncpy(year_str, timestamp, 4);
    year_str[4] = '\0';

    int year = atoi(year_str);

    return year;
}

// Função de comparação para ordenar os artistas
int ordena_artists_id(gconstpointer a, gconstpointer b)
{
    int *data_a = (int *)a;
    int *data_b = (int *)b;

    if (data_b[1] != data_a[1]) 
    {
        return data_b[1] - data_a[1];
    }

    char *artist_id_a = (char *)data_a[2];
    char *artist_id_b = (char *)data_b[2];

    return strcmp(artist_id_a, artist_id_b);
}