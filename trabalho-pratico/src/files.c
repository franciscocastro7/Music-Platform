#include "../include/files.h"

FILE *open_files(char *path, char *filename)
{
    FILE *file;

    char *filepath;
    filepath = (char *)malloc(1000 * sizeof(char));
    if (filepath == NULL)
    {
        printf("Erro ao alocar memória\n");
        return NULL;
    }
    strcpy(filepath, path);
    strcat(filepath, filename);

    file = fopen(filepath, "r");
    free(filepath);

    if (file == NULL)
        puts("Erro na abertura de ficheiro\n");

    return file;
}

int print_header(FILE *csv, FILE *error_csv)
{
    char header[1000];
    if (fgets(header, sizeof(header), csv) == NULL)
    {
        printf("Erro ao ler o cabeçalho do arquivo CSV.\n");
        return 1;
    }
    fprintf(error_csv, "%s", header);

    return 0;
}
