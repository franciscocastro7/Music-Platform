#include "../include/parser.h"

char **ParseCSV(FILE *csv)
{
    int initial_size = 4000;
    int current_size = initial_size;  // Tamanho inicial do array
    char **parsed_csv = malloc(current_size * sizeof(char *));
    if (parsed_csv == NULL)
    {
        printf("Erro ao alocar memória.\n");
        return NULL;
    }

    char *linha = malloc(4000 * sizeof(char));
    if (linha == NULL)
    {
        printf("Erro ao alocar memória para a linha.\n");
        free(parsed_csv);
        return NULL;
    }

    int i = 0;
    while (fgets(linha, 4000, csv) != NULL)
    {
        linha[strcspn(linha, "\n")] = 0;  // Remove o '\n' da linha

        // Se o número de linhas processadas atingir o tamanho atual, realoca mais memória
        if (i >= current_size)
        {
            current_size = (int)(current_size * 1.5);  // Cresce o tamanho em 50%
            char **temp_parsed_csv = realloc(parsed_csv, current_size * sizeof(char *));
            if (temp_parsed_csv == NULL)
            {
                printf("Erro ao realocar memória.\n");
                free(linha);
                free_parser(parsed_csv);  // Libera a memória já alocada
                return NULL;
            }
            parsed_csv = temp_parsed_csv;  // Atualiza o ponteiro para o novo bloco
        }

        parsed_csv[i] = strdup(linha);  // Copia a linha para a memória
        if (parsed_csv[i] == NULL)
        {
            printf("Erro ao duplicar a linha.\n");
            free(linha);
            parsed_csv[i] = NULL;  // Garante que a última posição seja válida
            free_parser(parsed_csv);  // Libera a memória já alocada
            return NULL;
        }

        i++;
    }

    free(linha);  // Libera a memória da linha temporária

    // Realoca para ajustar ao tamanho exato dos dados
    char **temp_parsed_csv = realloc(parsed_csv, (i + 1) * sizeof(char *));
    if (temp_parsed_csv != NULL)
    {
        parsed_csv = temp_parsed_csv;
    }
    parsed_csv[i] = NULL;  // Marca o fim do vetor

    return parsed_csv;
}

void free_parser(char **parser)
{
    if (parser == NULL) return;

    for (int i = 0; parser[i] != NULL; i++)
    {
        free(parser[i]);
    }
    free(parser);
}
