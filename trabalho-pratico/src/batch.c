#include "../include/batch.h"

void batch(char **argv)
{
    // Abrir arquivo artists.csv e seu arquivo de erros
    FILE *artists = open_files(argv[1], "/artists.csv");
    if (artists == NULL)
    {
        printf("Erro ao abrir o arquivo artists.csv\n");
        return;
    }

    FILE *artists_errors = fopen("resultados/artists_errors.csv", "w");
    if (artists_errors == NULL)
    {
        puts("Erro ao abrir o ficheiro de erros de artists\n");
        fclose(artists);
        return;
    }

    // Abrir arquivo musics.csv e seu arquivo de erros
    FILE *musics = open_files(argv[1], "/musics.csv");
    if (musics == NULL)
    {
        printf("Erro ao abrir o arquivo musics.csv\n");
        fclose(artists);
        fclose(artists_errors);
        return;
    }

    FILE *musics_errors = fopen("resultados/musics_errors.csv", "w");
    if (musics_errors == NULL)
    {
        puts("Erro ao abrir o ficheiro de erros de musics\n");
        fclose(artists);
        fclose(artists_errors);
        fclose(musics);
        return;
    }

    // Abrir arquivo albums.csv e seu arquivo de erros
    FILE *albums = open_files(argv[1], "/albums.csv");
    if (albums == NULL)
    {
        printf("Erro ao abrir o arquivo albums.csv\n");
        fclose(artists);
        fclose(artists_errors);
        fclose(musics);
        fclose(musics_errors);
        return;
    }

    // Abrir arquivo users.csv e seu arquivo de erros
    FILE *users = open_files(argv[1], "/users.csv");
    if (users == NULL)
    {
        printf("Erro ao abrir o arquivo users.csv\n");
        fclose(artists);
        fclose(artists_errors);
        fclose(musics);
        fclose(musics_errors);
        fclose(albums);
        return;
    }

    FILE *users_errors = fopen("resultados/users_errors.csv", "w");
    if (users_errors == NULL)
    {
        puts("Erro ao abrir o ficheiro de erros de users\n");
        fclose(artists);
        fclose(artists_errors);
        fclose(musics);
        fclose(musics_errors);
        fclose(albums);
        fclose(users);
        return;
    }

    // Abrir arquivo history.csv e seu arquivo de erros
    FILE *history = open_files(argv[1], "/history.csv");
    if (history == NULL)
    {
        printf("Erro ao abrir o arquivo history.csv\n");
        fclose(artists);
        fclose(artists_errors);
        fclose(musics);
        fclose(musics_errors);
        fclose(albums);
        fclose(users);
        fclose(users_errors);
        return;
    }

    FILE *history_errors = fopen("resultados/history_errors.csv", "w");
    if (history_errors == NULL)
    {
        puts("Erro ao abrir o ficheiro de erros de history\n");
        fclose(artists);
        fclose(artists_errors);
        fclose(musics);
        fclose(musics_errors);
        fclose(albums);
        fclose(users);
        fclose(users_errors);
        fclose(history);
        return;
    }

    // Abrir arquivo de inputs
    FILE *inputs = open_files(argv[2], "");
    if (inputs == NULL)
    {
        printf("Erro ao abrir inputs\n");
        fclose(artists);
        fclose(artists_errors);
        fclose(musics);
        fclose(musics_errors);
        fclose(albums);
        fclose(users);
        fclose(users_errors);
        fclose(history);
        fclose(history_errors);
        return;
    }

    // Imprimir headers nos arquivos de erros
    print_header(musics, musics_errors);
    print_header(users, users_errors);
    print_header(artists, artists_errors);
    print_header(history, history_errors);

    // Parse dos CSVs
    char **parsed_artists = ParseCSV(artists);
    char **parsed_musics = ParseCSV(musics);
    char **parsed_albums = ParseCSV(albums);
    char **parsed_users = ParseCSV(users);
    char **parsed_history = ParseCSV(history);

    fclose(artists);
    fclose(musics);
    fclose(albums);
    fclose(users);
    fclose(history);

    // Inicializar o Database_Manager com todos os managers
    Database_Manager *db_manager = create_database_manager(parsed_artists, parsed_musics, parsed_albums, parsed_users, parsed_history,
                                                           artists_errors, musics_errors, users_errors, history_errors);

    // Processar os comandos do arquivo de inputs
    handle_inputs(inputs, db_manager);

    // Fechar os arquivos de erros
    fclose(artists_errors);
    fclose(musics_errors);
    fclose(users_errors);
    fclose(history_errors);
    fclose(inputs);

    // Liberar a memória do Database_Manager
    free_database_manager(db_manager);
}