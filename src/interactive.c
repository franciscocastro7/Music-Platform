#include "../include/interactive.h"
#include "../include/database_manager.h"
#include "../include/parser.h"
#include "../include/files.h"
#include "../include/interpreter.h"

int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");

    system("clear");
    printf("\t\t\t **** MODO INTERATIVO ****\n\n");
    printf("Bem-vindo ao modo Interativo! Para continuar, indique o caminho do diretório que contém os ficheiros CSV.\n");
    printf("Diretório: ");

    char path[150];
    if (!fgets(path, sizeof(path), stdin))
    {
        fprintf(stderr, "Erro ao ler o diretório.\n");
        return EXIT_FAILURE;
    }

    path[strcspn(path, "\n")] = '\0'; // Remove o '\n' do final

    printf("\n\t --- Abertura dos Ficheiros ---\n\n");

    FILE *artists_file = open_files(path, "/artists.csv");
    FILE *musics_file = open_files(path, "/musics.csv");
    FILE *albums_file = open_files(path, "/albums.csv");
    FILE *users_file = open_files(path, "/users.csv");
    FILE *history_file = open_files(path, "/history.csv");

    if (!artists_file || !musics_file || !albums_file || !users_file || !history_file)
    {
        fprintf(stderr, "Erro na abertura de pelo menos um dos ficheiros! Verifique o caminho.\n");
        return EXIT_FAILURE;
    }

    printf("\n\t --- Parsing dos Ficheiros ---\n\n");

    FILE *artists_errors = fopen("resultados/artists_errors.csv", "w");
    FILE *musics_errors = fopen("resultados/musics_errors.csv", "w");
    FILE *users_errors = fopen("resultados/users_errors.csv", "w");
    FILE *history_errors = fopen("resultados/history_errors.csv", "w");

    if (!artists_errors || !musics_errors || !users_errors || !history_errors)
    {
        perror("Erro ao abrir os arquivos de erros");
        fclose(artists_file);
        fclose(musics_file);
        fclose(albums_file);
        fclose(users_file);
        fclose(history_file);
        return EXIT_FAILURE;
    }

    char **parsed_artists = ParseCSV(artists_file);
    char **parsed_musics = ParseCSV(musics_file);
    char **parsed_albums = ParseCSV(albums_file);
    char **parsed_users = ParseCSV(users_file);
    char **parsed_history = ParseCSV(history_file);

    fclose(artists_file);
    fclose(musics_file);
    fclose(albums_file);
    fclose(users_file);
    fclose(history_file);

    if (!parsed_artists || !parsed_musics || !parsed_albums || !parsed_users || !parsed_history)
    {
        fprintf(stderr, "Erro no parsing dos arquivos CSV.\n");
        fclose(artists_errors);
        fclose(musics_errors);
        fclose(users_errors);
        fclose(history_errors);
        return EXIT_FAILURE;
    }

    Database_Manager *db_manager = create_database_manager(parsed_artists, parsed_musics, parsed_albums, parsed_users, parsed_history,
                                                            artists_errors, musics_errors, users_errors, history_errors);
    if (!db_manager)
    {
        fprintf(stderr, "Erro ao criar o gerenciador de banco de dados.\n");
        fclose(artists_errors);
        fclose(musics_errors);
        fclose(users_errors);
        fclose(history_errors);
        return EXIT_FAILURE;
    }

    fclose(artists_errors);
    fclose(musics_errors);
    fclose(users_errors);
    fclose(history_errors);

    // Inicia o modo interativo
    handle_inputs_interactive(db_manager);

    free_database_manager(db_manager);

    printf("Modo interativo encerrado. Até logo!\n");
    return EXIT_SUCCESS;
}