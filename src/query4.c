#include "../include/query4.h"

#define CURRENT_DATE "2024-09-09"

/*// Função para calcular o início da semana (domingo) a partir de uma data no formato "YYYY/MM/DD HH:MM:SS"
char *get_week_start(char *timestamp)
{
    if (timestamp == NULL || strlen(timestamp) == 0) {
        printf("Timestamp inválido ou ausente\n");
        return NULL;
    }
    struct tm time_info = {0};
    
    // Ajuste no sscanf para o formato correto
    int result = sscanf(timestamp, "%d/%d/%d %d:%d:%d",
                        &time_info.tm_year, &time_info.tm_mon, &time_info.tm_mday,
                        &time_info.tm_hour, &time_info.tm_min, &time_info.tm_sec);

    // Verifica se todos os campos foram lidos corretamente
    if (result != 6)
    {
        printf("Erro ao converter timestamp: %s\n", timestamp);
        return NULL;
    }

    // Ajustar tm_year e tm_mon
    time_info.tm_year -= 1900;  // O tm_year começa a contar de 1900
    time_info.tm_mon -= 1;      // O tm_mon começa a contar de 0 (Janeiro)

    // Normaliza a estrutura de tempo
    if (mktime(&time_info) == -1)
    {
        printf("Erro ao normalizar a data: %s\n", timestamp);
        return NULL;
    }

    // Ajustar para o domingo da semana
    int days_to_sunday = time_info.tm_wday; // Domingo é 0
    time_info.tm_mday -= days_to_sunday;

    // Normaliza novamente para garantir consistência
    if (mktime(&time_info) == -1)
    {
        printf("Erro ao calcular o início da semana: %s\n", timestamp);
        return NULL;
    }

    // Converter o início da semana de volta para string no formato "YYYY/MM/DD"
    char *week_start = malloc(11); // "YYYY/MM/DD" + null terminator
    if (week_start != NULL)
    {
        strftime(week_start, 11, "%Y/%m/%d", &time_info);
    }
    return week_start;
}

int is_date_in_range(char *x_date, char *begin_date, char *end_date)
{
    // Estrutura para armazenar as datas convertidas
    struct tm tm_x = {0}, tm_begin = {0}, tm_end = {0};
    
    // Verifica se as entradas de data são válidas
    if (x_date == NULL || begin_date == NULL || end_date == NULL) {
        printf("Datas inválidas!\n");
        return 0;
    }

    // Converte as strings para as estruturas tm usando sscanf
    int result_x = sscanf(x_date, "%d/%d/%d", &tm_x.tm_year, &tm_x.tm_mon, &tm_x.tm_mday);
    int result_begin = sscanf(begin_date, "%d/%d/%d", &tm_begin.tm_year, &tm_begin.tm_mon, &tm_begin.tm_mday);
    int result_end = sscanf(end_date, "%d/%d/%d", &tm_end.tm_year, &tm_end.tm_mon, &tm_end.tm_mday);

    // Verifica se todos os campos foram lidos corretamente
    if (result_x != 3 || result_begin != 3 || result_end != 3)
    {
        printf("Erro ao converter as datas para o formato esperado\n");
        return 0;
    }

    // Ajusta os valores de tm_year e tm_mon
    tm_x.tm_year -= 1900;  // O tm_year começa a contar de 1900
    tm_x.tm_mon -= 1;      // O tm_mon começa a contar de 0 (Janeiro)

    tm_begin.tm_year -= 1900;
    tm_begin.tm_mon -= 1;

    tm_end.tm_year -= 1900;
    tm_end.tm_mon -= 1;

    // Converte as estruturas tm para timestamps para comparar as datas
    time_t time_x = mktime(&tm_x);
    time_t time_begin = mktime(&tm_begin);
    time_t time_end = mktime(&tm_end);

    // Verifica se houve erro na conversão
    if (time_x == -1 || time_begin == -1 || time_end == -1) {
        printf("Erro ao normalizar as datas\n");
        return 0;
    }

    // Verifica se a data X está no intervalo [begin_date, end_date], inclusivo
    return (time_x >= time_begin && time_x <= time_end);
}

int compare_artist_playtime(gconstpointer a, gconstpointer b, gpointer user_data)
{
    GHashTable *artist_playtime = (GHashTable *)user_data;

    Artist *artist_a = (Artist *)a;
    Artist *artist_b = (Artist *)b;

    char *id_a = get_artist_id(artist_a);
    char *id_b = get_artist_id(artist_b);

    // Verificar se os tempos de reprodução estão presentes na tabela
    int *playtime_a = g_hash_table_lookup(artist_playtime, id_a);
    int *playtime_b = g_hash_table_lookup(artist_playtime, id_b);

    if (playtime_a == NULL || playtime_b == NULL)
    {
        return 0;  // Pode retornar 0 ou outro valor apropriado
    }

    // Se você estiver armazenando os tempos de reprodução em segundos, compare diretamente os valores inteiros
    // Caso contrário, use a função duration_to_seconds para converter a string para segundos
    int playtime_sec_a = *playtime_a;  // Já está em segundos
    int playtime_sec_b = *playtime_b;  // Já está em segundos

    // Comparar tempo total de reprodução
    if (playtime_sec_a != playtime_sec_b)
    {
        return playtime_sec_b - playtime_sec_a; // Decrescente
    }

    // Comparar IDs em caso de empate
    return strcmp(id_a, id_b); // Crescente
}

GHashTable *aggregate_playtimes(GPtrArray *week_histories, GHashTable *music_table)
{
    GHashTable *artist_playtime = g_hash_table_new_full(g_str_hash, g_str_equal, free, free);
    for (guint i = 0; i < week_histories->len; i++) {
        History *history = g_ptr_array_index(week_histories, i);
        char *playtime = get_history_duration(history);
        if (!playtime || strlen(playtime) == 0) continue;

        int playtime_seconds = duration_to_seconds(playtime);
        if (playtime_seconds < 0) continue;

        Music *music = g_hash_table_lookup(music_table, get_history_music_id(history));
        if (!music) continue;

        char **artist_ids = get_music_artist_id(music);
        for (int j = 0; artist_ids[j] != NULL; j++) {
            char *artist_id = artist_ids[j];
            int *current_playtime = g_hash_table_lookup(artist_playtime, artist_id);
            int total_playtime = (current_playtime ? *current_playtime : 0) + playtime_seconds;

            int *updated_playtime = g_new(int, 1);
            *updated_playtime = total_playtime;
            g_hash_table_replace(artist_playtime, g_strdup(artist_id), updated_playtime);
        }
    }
    return artist_playtime;
}

GPtrArray *sort_artists(GHashTable *artist_playtime, GHashTable *artist_table)
{
    GPtrArray *sorted_artists = g_ptr_array_new_with_free_func((GDestroyNotify)free);
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, artist_playtime);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Artist *artist = g_hash_table_lookup(artist_table, key);
        if (artist) g_ptr_array_add(sorted_artists, artist);
    }
    g_ptr_array_sort_with_data(sorted_artists, compare_artist_playtime, artist_playtime);
    return sorted_artists;
}

GPtrArray* calculate_top_artists(GPtrArray *week_histories, GHashTable *music_table, GHashTable *artist_table)
{
    GHashTable *artist_playtime = aggregate_playtimes(week_histories, music_table);
    if (!artist_playtime) return NULL;

    GPtrArray *sorted_artists = sort_artists(artist_playtime, artist_table);
    g_hash_table_destroy(artist_playtime);
    return sorted_artists;
}


void calculate_top10_frequency(GPtrArray *all_sorted_artists, GHashTable *artist_frequency)
{
    guint limit = MIN(all_sorted_artists->len, 10);
    
    for (guint i = 0; i < limit; i++)
    {
        Artist *artist = g_ptr_array_index(all_sorted_artists, i);
        char *artist_id = get_artist_id(artist);
        if (artist_id == NULL || strlen(artist_id) == 0)
        {
            printf("ID do artista inválido\n");
            continue;
        }

        int *current_frequency = g_hash_table_lookup(artist_frequency, artist_id);
        if (current_frequency == NULL)
        {
            int *new_frequency = malloc(sizeof(int));
            if (new_frequency == NULL)
            {
                printf("Erro de alocação de memória para frequência\n");
               return;
            }
            *new_frequency = 1;
            g_hash_table_insert(artist_frequency, g_strdup(artist_id), new_frequency);
        }
        else
        {
            (*current_frequency)++;
        }
    }
}

void query4(Database_Manager *db_manager, char *begin_date, char *end_date, FILE *output, char separator)
{
    Artist_Manager *artist_manager = get_artist_manager(db_manager);
    Music_Manager *music_manager = get_music_manager(db_manager);
    History_Manager *history_manager = get_history_manager(db_manager);

    GHashTable *artist_table = get_artist_table(artist_manager);
    GHashTable *music_table = get_music_table(music_manager);
    GHashTable *history_table = get_history_table(history_manager);

    GHashTable *weeks_table = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)g_ptr_array_free);

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, history_table);

    while(g_hash_table_iter_next(&iter, &key, &value))
    {
        History *history = (History *)value;
        char *timestamp = get_history_timestamp(history);

        char *week_start = get_week_start(timestamp);

        if (week_start != NULL) {
            // Verifica se já existe um grupo para esta semana
            GPtrArray *week_histories = g_hash_table_lookup(weeks_table, week_start);   
            if (week_histories == NULL) {
                week_histories = g_ptr_array_new_with_free_func((GDestroyNotify)free_history);
                g_hash_table_insert(weeks_table, g_strdup(week_start), week_histories);
            }
            g_ptr_array_add(week_histories, history);
            free(week_start); // Libera memória após o uso
        }
        else
        {
            printf("Erro ao calcular o início da semana para o timestamp: %s\n", timestamp);
            return;
        }
    }

    // Geração dos artistas do top 10 para todas as semanas
    GHashTable *artist_frequency = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free);
    GHashTableIter week_iter;
    gpointer week_key, week_value;
    g_hash_table_iter_init(&week_iter, weeks_table);

    while (g_hash_table_iter_next(&week_iter, &week_key, &week_value))
    {
        GPtrArray *week_histories = (GPtrArray *)week_value;
        GPtrArray *sorted_artists = calculate_top_artists(week_histories, music_table, artist_table);
        if (sorted_artists == NULL)
        {
            printf("sorted_artist is NULL for week %s\n", (char *)week_key);
        }
    
        calculate_top10_frequency(sorted_artists, artist_frequency);

        g_ptr_array_free(sorted_artists, FALSE);

    }

    // Ordena o número de artistas por número de aparições no top 10
    GPtrArray *sorted_by_frequency = g_ptr_array_new();
    
    GHashTableIter frequency_iter;
    gpointer artist_id_key, frequency_value;
    g_hash_table_iter_init(&frequency_iter, artist_frequency);

    while (g_hash_table_iter_next(&frequency_iter, &artist_id_key, &frequency_value))
    {
        char *artist_id = (char *)artist_id_key;

        Artist *artist = g_hash_table_lookup(artist_table, artist_id);
        if (artist != NULL)
        {
            g_ptr_array_add(sorted_by_frequency, artist);
        }
        else
        {
            printf("Artista não encontrado para o id: %s\n", artist_id);
        }
    }

    g_ptr_array_sort_with_data(sorted_by_frequency, (GCompareDataFunc)compare_artist_playtime, artist_frequency);

    if (sorted_by_frequency->len > 0)
    {
        Artist *artist = g_ptr_array_index(sorted_by_frequency, 0);
        char *artist_id = get_artist_id(artist);
        char *artist_type = get_artist_type(artist);
        int *frequency = g_hash_table_lookup(artist_frequency, artist_id);

        fprintf(output, "%s%c%s%c%d\n", artist_id, separator, artist_type, separator, *frequency);
    }


    // Libera memória
    g_ptr_array_free(sorted_by_frequency, FALSE);
    g_hash_table_destroy(weeks_table);
    g_hash_table_destroy(artist_frequency);
}*/