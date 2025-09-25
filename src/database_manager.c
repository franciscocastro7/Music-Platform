#include "../include/database_manager.h"

struct database_manager {
    Artist_Manager *artist_manager;
    Music_Manager *music_manager;
    Album_Manager *album_manager;
    User_Manager *user_manager;
    History_Manager *history_manager;
};

Database_Manager *create_database_manager(char **parsed_artists, char **parsed_musics, char **parsed_albums, char **parsed_users, char **parsed_history,
                                          FILE *artists_errors, FILE *musics_errors, FILE *users_errors, FILE *history_errors) {
    // Aloca memória para o Database_Manager
    Database_Manager *db_manager = malloc(sizeof(Database_Manager));
    if (db_manager == NULL) {
        printf("Erro ao alocar memória para Database_Manager.\n");
        return NULL;
    }

    // Inicializa cada um dos managers na ordem correta
    db_manager->artist_manager = ParseArtists(parsed_artists, artists_errors);

    // Inicializa Album_Manager antes de Music_Manager
    db_manager->album_manager = ParseAlbums(parsed_albums, db_manager->artist_manager);

    db_manager->music_manager = ParseMusics(parsed_musics, db_manager->artist_manager, db_manager->album_manager, musics_errors);

    db_manager->user_manager = ParseUsers(parsed_users, db_manager->music_manager, users_errors);

    db_manager->history_manager = ParseHistory(parsed_history, db_manager->user_manager, db_manager->music_manager, history_errors);

    return db_manager;
}

void free_database_manager(Database_Manager *db_manager) {
    if (db_manager != NULL) {
        free_artist_manager(db_manager->artist_manager);
        free_music_manager(db_manager->music_manager);
        free_album_manager(db_manager->album_manager);
        free_user_manager(db_manager->user_manager);
        free_history_manager(db_manager->history_manager);
        free(db_manager);
    }
}

Artist_Manager *get_artist_manager(Database_Manager *db_manager) {
    return db_manager->artist_manager;
}

Music_Manager *get_music_manager(Database_Manager *db_manager) {
    return db_manager->music_manager;
}

Album_Manager *get_album_manager(Database_Manager *db_manager) {
    return db_manager->album_manager;
}

User_Manager *get_user_manager(Database_Manager *db_manager) {
    return db_manager->user_manager;
}

History_Manager *get_history_manager(Database_Manager *db_manager) {
    return db_manager->history_manager;
}

