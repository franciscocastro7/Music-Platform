#include "../include/database_manager.h"
#include "../include/parser.h"
#include "../include/files.h"
#include "../include/interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "../include/test.h"

int compare_files(FILE *file1, FILE *file2, int *linha)
{
    int f1, f2;
    int same = 1;
    *linha = 1;

    while (((f1 = fgetc(file1)) != EOF) && ((f2 = getc(file2)) != EOF))
    {
        if (f1 != f2)
        {
            same = 0;
            break;
        }
        if (f1 == '\n')
        {
            (*linha)++;
        }
    }
    if (same)
    {
        if (fgetc(file1) == EOF && fgetc(file2) == EOF)
            same = 1;
        else
            same = 0;
    }
    return same;
}

int check(int counter, char *resul_esperados)
{
    int passed = 0;
    char command[500], filepath[500], resultfile[500];
    snprintf(command, sizeof(command), "command%d_output.txt", counter);
    snprintf(resultfile, sizeof(resultfile), "resultados/%.480s", command);
    snprintf(filepath, sizeof(filepath), "%.250s/%.200s", resul_esperados, command);

    FILE *esperados = fopen(filepath, "r");
    FILE *resultados = fopen(resultfile, "r");

    if (!esperados || !resultados)
    {
        printf("Erro ao abrir os arquivos para o Test %d\n", counter);
        if (esperados)
            fclose(esperados);
        if (resultados)
            fclose(resultados);
        return 0;
    }

    int linha = 1;
    if (compare_files(esperados, resultados, &linha))
    {
        passed = 1;
    }
    else
    {
        printf("    Discrepância na query %d: linha %d de 'resultados/command%d_output.txt'\n", counter, linha, counter);
    }

    fclose(esperados);
    fclose(resultados);
    return passed;
}

void noOutput(int counter)
{
    printf("Test %d not found\n", counter);
}

void process_query_test(char *command, Database_Manager *db_manager, int query_id, FILE *output, double *execution_time)
{
    clock_t start = clock();

    char *command_copy = strdup(command);
    if (command_copy == NULL)
    {
        perror("Erro ao duplicar comando");
        return;
    }

    char *query_number = strtok(command_copy, " ");
    if (query_number == NULL)
    {
        free(command_copy);
        return;
    }

    char outputFile[100];
    snprintf(outputFile, sizeof(outputFile), "resultados/command%d_output.txt", query_id);

    FILE *out_file = fopen(outputFile, "w");
    if (out_file == NULL)
    {
        perror("Erro ao abrir o arquivo de saída");
        free(command_copy);
        return;
    }

    query_id = atoi(query_number);
    char separator = (strstr(query_number, "S") != NULL) ? '=' : ';';

    switch (query_id)
    {
    case 1:
    {
        char *argumento = strtok(NULL, " "); // Obtém o argumento da query 1
        if (argumento)
        {
            char first = argumento[0];
            if (first == 'U')
            {
                query1(db_manager, argumento, NULL, output, separator);
            }
            else
            {
                query1(db_manager, NULL, argumento, output, separator);
            }
        }
        else
        {
            fprintf(output, "Erro: ID de usuário não fornecido para Query 1\n");
        }
        break;
    }
    case 2:
    {
        char *numero = strtok(NULL, " ");
        char *country_filter = strtok(NULL, "\n");

        if (numero)
        {
            int N = atoi(numero);
            query2(db_manager, N, country_filter, out_file, separator);
        }
        else
        {
            fprintf(out_file, "Erro: N de artistas não fornecido para Query 2\n");
        }
        break;
    }
    case 3:
    {
        char *min_age_str = strtok(NULL, " ");
        char *max_age_str = strtok(NULL, " ");

        if (min_age_str && max_age_str)
        {
            int min_age = atoi(min_age_str);
            int max_age = atoi(max_age_str);
            query3(db_manager, min_age, max_age, out_file, separator);
        }
        else
        {
            fprintf(out_file, "Erro: Idades não fornecidas corretamente para Query 3\n");
        }
        break;
    }
    /*case 4:
    {
        char *begin_date = strtok(NULL, " ");
        char *end_date = strtok(NULL, " ");

        if (begin_date && end_date)
        {
            query4(db_manager, begin_date, end_date, out_file, separator);
        }
        else
        {
            query4(db_manager, NULL, NULL, output, separator);
        }
        break;
    }
    case 6:
    {
        char *user_id = strtok(NULL, " ");
        char *year_str = strtok(NULL, " ");
        char *n_str = strtok(NULL, " ");
        int year = (year_str != NULL) ? atoi(year_str) : -1;
        int N = (n_str != NULL) ? atoi(n_str) : -1;

        if (user_id && year > 0)
        {
            query6(db_manager, user_id, year, N, output, separator);
        } 
        else 
        {
            fprintf(output, "Erro: ID de usuário ou year não fornecidos para Query6\n");
        }
        break;
    }*/
    default:
        fprintf(out_file, "Erro: Query não reconhecida: %s\n", command);
        break;
    }

    clock_t end = clock();
    *execution_time += ((double)(end - start)) / CLOCKS_PER_SEC;

    fclose(out_file);
    free(command_copy);
}

int main(int argc, char *argv[])
{
    if (argc == 4)
    {
        clock_t start_total = clock();

        FILE *artists = open_files(argv[1], "/artists.csv");
        FILE *artists_errors = fopen("resultados/artists_errors.csv", "w");
        FILE *musics = open_files(argv[1], "/musics.csv");
        FILE *musics_errors = fopen("resultados/musics_errors.csv", "w");
        FILE *albums = open_files(argv[1], "/albums.csv");
        FILE *users = open_files(argv[1], "/users.csv");
        FILE *users_errors = fopen("resultados/users_errors.csv", "w");
        FILE *history = open_files(argv[1], "/history.csv");
        FILE *history_errors = fopen("resultados/history_errors.csv", "w");
        FILE *inputs = open_files(argv[2], "");

        print_header(musics, musics_errors);
        print_header(users, users_errors);
        print_header(artists, artists_errors);
        print_header(history, history_errors);

        char **parsed_artists = ParseCSV(artists);
        char **parsed_musics = ParseCSV(musics);
        char **parsed_users = ParseCSV(users);
        char **parsed_history = ParseCSV(history);
        char **parsed_albums = ParseCSV(albums);

        fclose(artists);
        fclose(musics);
        fclose(albums);
        fclose(users);
        fclose(history);

        Database_Manager *db_manager = create_database_manager(parsed_artists, parsed_musics, parsed_albums, parsed_users, parsed_history,
                                                               artists_errors, musics_errors, users_errors, history_errors);
        fclose(artists_errors);
        fclose(musics_errors);
        fclose(users_errors);
        fclose(history_errors);

        system("clear");
        puts("\t\t\t\t\t\t\t **** MODO DE TESTES ****\n");

        double query_times[6] = {0};
        double total_execution_time = 0;
        char **arrays[6] = {NULL, NULL, NULL, NULL, NULL, NULL};
        int counts[6] = {0};

        char *command = malloc(100 * sizeof(char));
        if (!command)
        {
            perror("Erro ao alocar memória para comando");
        }
        while (fgets(command, 100, inputs))
        {
            command[strcspn(command, "\n")] = 0;

            if (strlen(command) == 0)
                continue;

            char first_char = command[0];
            int index = first_char - '1';
            counts[index]++;

            arrays[index] = realloc(arrays[index], counts[index] * sizeof(char *));
            if (arrays[index] == NULL)
            {
                perror("Erro ao realocar memória");
                free(command);
                fclose(inputs);
                break;
            }

            arrays[index][counts[index] - 1] = strdup(command);
            if (arrays[index][counts[index] - 1] == NULL)
            {
                perror("Erro ao duplicar linha");
                free(command);
                fclose(inputs);
                break;
            }
        }

        free(command);
        fclose(inputs);

        int counter = 0;
        for (int i = 0; i < 6; i++)
        {
            printf("Query%d:\n", i + 1);
            int passed = 0;
            for (int j = 0; j < counts[i]; j++)
            {
                counter++;

                char *outputFile = malloc(50 * sizeof(char));
                if (outputFile == NULL)
                {
                    perror("Erro ao alocar memória");
                    break;
                }

                snprintf(outputFile, 50, "resultados/command%d_output.txt", counter);
                FILE *output = fopen(outputFile, "w");
                if (output == NULL)
                {
                    perror("Erro ao abrir o arquivo");
                    free(outputFile);
                    break;
                }

                process_query_test(arrays[i][j], db_manager, counter, output, &query_times[i]);
                fclose(output);

                if (check(counter, argv[3]))
                {
                    passed++;
                }
            }
            printf("Q%d: %d de %d testes ok!\n", i + 1, passed, counts[i]);
            free(arrays[i]);
        }

        clock_t end_total = clock();
        total_execution_time = ((double)(end_total - start_total)) / CLOCKS_PER_SEC;

        struct rusage r_usage;
        getrusage(RUSAGE_SELF, &r_usage);
        printf("\nMemória utilizada: %ld MB\n", (r_usage.ru_maxrss)/1024);
        printf("Tempos de execução:\n");
        for (int i = 0; i < 6; i++)
        {
            printf("    Q%d: %.2f ms\n", i + 1, query_times[i] * 1000);
        }

        printf("\nTempo total de execução: %.2f segundos\n", total_execution_time);

        free_database_manager(db_manager);
    }
    else
    {
        printf("O número de argumentos está incorreto.\n");
    }

    return 0;
}