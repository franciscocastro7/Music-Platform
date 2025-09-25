#include "../include/interpreter.h"

void handle_inputs(FILE *inputs, Database_Manager *db_manager)
{
    char *command = malloc(sizeof(char) * 100);
    if (!command)
    {
        perror("Erro ao alocar memória para o comando");
        return;
    }

    int count = 1;

    // Processa cada linha do arquivo
    while (fgets(command, 100, inputs))
    {
        // Remove a nova linha no final do comando, se existir
        command[strcspn(command, "\n")] = 0;

        if (strlen(command) > 0)
        {
            process_query(command, db_manager, count, false); // `interactive_mode = false`
            count++;
        }
    }

    free(command);
}

void process_query(char *command, Database_Manager *db_manager, int count, bool interactive_mode)
{
    char *command_copy = strdup(command); // Duplicar o comando para manipulação
    if (command_copy == NULL)
    {
        perror("Erro ao duplicar comando");
        return;
    }

    char *query_number = strtok(command_copy, " "); // Extrai o número da query
    if (query_number == NULL)
    {
        free(command_copy);
        return;
    }

    // Configura o destino do output
    char outputFile[100];
    sprintf(outputFile, "resultados/command%d_output.txt", count); // Nome do arquivo de saída
    FILE *output = (interactive_mode) ? stdout : fopen(outputFile, "w");
    if (!interactive_mode && output == NULL) // Verifica erros no modo batch
    {
        perror("Erro ao abrir o arquivo de saída");
        free(command_copy);
        return;
    }

    int query_id = atoi(query_number); // Converte o número da query para inteiro
    char separator = (strstr(query_number, "S") != NULL) ? '=' : ';'; // Define o separador de saída

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
        char *numero = strtok(NULL, " "); // Obtém o número N
        char *country_filter = strtok(NULL, "\n"); // Obtém o filtro de país

        if (numero)
        {
            int N = atoi(numero);
            query2(db_manager, N, country_filter, output, separator);
        }
        else
        {
            fprintf(output, "Erro: N de artistas não fornecido para Query 2\n");
        }
        break;
    }
    case 3:
    {
        char *min_age_str = strtok(NULL, " "); // Idade mínima
        char *max_age_str = strtok(NULL, " "); // Idade máxima

        if (min_age_str && max_age_str)
        {
            int min_age = atoi(min_age_str);
            int max_age = atoi(max_age_str);
            query3(db_manager, min_age, max_age, output, separator);
        }
        else
        {
            fprintf(output, "Erro: Idades não fornecidas corretamente para Query 3\n");
        }
        break;
    }
    /*case 4:
    {
        char *begin_date = strtok(NULL, " "); // Data inicial
        char *end_date = strtok(NULL, " "); // Data final

        if (begin_date && end_date)
        {
            query4(db_manager, begin_date, end_date, output, separator);
        }
        else
        {
            query4(db_manager, NULL, NULL, output, separator);
        }
        break;
    } */ /*
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
        fprintf(output, "Erro: Query não reconhecida: %s\n", command);
        break;
    }

    if (!interactive_mode) // Fecha o arquivo no modo batch
    {
        fclose(output);
    }

    free(command_copy); // Libera a memória alocada
}

void handle_inputs_interactive(Database_Manager *db_manager)
{
    char *command = malloc(sizeof(char) * 100);
    if (!command)
    {
        perror("Erro ao alocar memória para o comando");
        return;
    }

    int count = 1;

    printf("Input => ");
    fflush(stdout);
    while (fgets(command, 100, stdin) && strcmp(command, "exit\n") != 0)
    {
        command[strcspn(command, "\n")] = 0; // Remove o '\n' do final do comando

        if (strlen(command) > 0)
        {
            printf("\nProcessando comando...\n");
            fflush(stdout);

            // Executa a query e imprime o resultado no terminal
            process_query(command, db_manager, count, true); // `interactive_mode = true`

            printf("\nComando processado!\n");
            count++;
        }
        else
        {
            printf("Comando vazio! Por favor, insira um comando válido.\n");
        }

        printf("Input => ");
        fflush(stdout);
    }

    free(command);
}