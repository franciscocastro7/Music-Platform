#include "../include/validation.h"

int is_individual_artist_valid(char *type, char **id_constituent, int constituent_count)
{

    if (strcmp(type, "individual") == 0)
    {
        if (constituent_count > 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }

    return 1;
}

int validate_music_artists(Music *music, Artist_Manager *artist_table)
{

    char **artist_ids = get_music_artist_id(music);

    if (artist_ids == NULL)
    {
        free(artist_ids);
        return -1; 
    }


    for (int i = 0; artist_ids[i] != NULL; i++)
    {
        Artist *artist = g_hash_table_lookup(get_artist_table(artist_table), artist_ids[i]);

        if (artist == NULL)
        {
            for (int i = 0; artist_ids[i] != NULL; i++)
            {
                free(artist_ids[i]);
            }
            free(artist_ids);
            return 1;
        }
    }
    for (int i = 0; artist_ids[i] != NULL; i++)
    {
        free(artist_ids[i]);
    }
    free(artist_ids);
    return 0;
}

int validate_user_liked_musics(User *user, Music_Manager *music_table)
{
    char **liked_music_ids = get_user_liked_musics_id(user);
    if (liked_music_ids == NULL)
    {
        return 1;
    }

    for (int i = 0; liked_music_ids[i] != NULL; i++)
    {
        Music *music = g_hash_table_lookup(get_music_table(music_table), liked_music_ids[i]);

        if (music == NULL)
        {
            for (int i = 0; liked_music_ids[i] != NULL; i++)
            {
                free(liked_music_ids[i]);
            }
            free(liked_music_ids);
            return 1;
        }
    }
    for (int i = 0; liked_music_ids[i] != NULL; i++)
    {
        free(liked_music_ids[i]);
    }
    free(liked_music_ids);
    return 0;
}

int validate_music_album(Music *music, Album_Manager *album_table)
{
    char *album_id = get_music_album_id(music);
    if (album_id == NULL)
    {
        return -1; // ID do álbum é inválido ou inexistente
    }
    
    Album *album = g_hash_table_lookup(get_album_table(album_table), album_id);
    if (album == NULL)
    {
        free(album_id); // Libera a memória alocada para o ID do álbum
        return 1; // O álbum não existe na tabela
    }
    
    // Apenas uma vez é suficiente, pois album_id é uma única string
    free(album_id);
    return 0;
}

bool is_valid_duration(const char *duration) {
    if (duration == NULL) {
        return false;
    }

    int hours, minutes, seconds;
    // hh:mm:ss
    int matched = sscanf(duration, "%2d:%2d:%2d", &hours, &minutes, &seconds);
    
    // Verifica se o formato foi corretamente lido
    if (matched != 3) {
        return false;
    }


    if (hours < 0 || hours > 99) {
        return false; 
    }
    if (minutes < 0 || minutes > 59) {
        return false;
    }
    if (seconds < 0 || seconds > 59) {
        return false;
    }

    return true; // Hora válida
}

bool is_valid_date(char *date) {
    if (date == NULL) {
        return false;
    }

    if (strlen(date) != 10) {
        return false;
    }

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
            if (date[i] != '/') {
                return false;
            }
        } else {
            if (!isdigit(date[i])) {
                return false;
            }
        }
    }

    char year_str[5], month_str[3], day_str[3];
    strncpy(year_str, date, 4);
    year_str[4] = '\0';
    strncpy(month_str, date + 5, 2);
    month_str[2] = '\0';
    strncpy(day_str, date + 8, 2);
    day_str[2] = '\0';

    int year = atoi(year_str);
    int month = atoi(month_str);
    int day = atoi(day_str);

    if (month < 1 || month > 12) {
        return false;
    }

    if (day < 1 || day > 31) {
        return false;
    }

    int current_year = 2024;
    int current_month = 9;
    int current_day = 9;

    if (year > current_year || 
        (year == current_year && month > current_month) || 
        (year == current_year && month == current_month && day > current_day)) {
        return false;
    }

    return true;
}

bool is_valid_email(char *email) {
    if (email == NULL) {
        return false;
    }

    char *at = strchr(email, '@');
    if (at == NULL || at == email) {
        return false; 
    }

    char *dot = strrchr(at, '.');
    if (dot == NULL || dot == at + 1 || dot[1] == '\0') {
        return false; 
    }

    for (char *p = email; p < at; ++p) {
        if (!isalnum(*p)) {
            return false;
        }
    }

    for (char *p = at + 1; p < dot; ++p) {
        if (!islower(*p)) {
            return false;
        }
    }

    size_t rstring_len = strlen(dot + 1);
    if (rstring_len < 2 || rstring_len > 3) {
        return false;
    }

    for (char *p = dot + 1; *p; ++p) {
        if (!islower(*p)) {
            return false;
        }
    }

    return true;
}

void to_lowercase(char *str) {
    if (str) {
        for (int i = 0; str[i]; i++) {
            str[i] = tolower(str[i]);
        }
    }
}


