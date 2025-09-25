#include "../include/main.h"
#include "../include/batch.h"
#include "../include/interactive.h"

int main(int argc, char *argv[])
{

    if (argc == 1)
    {
        //interactive();
    }

    else if (argc == 3)
    {
        puts("\nDiretório Resultados criado\n");
        puts("Número de argumentos válidos! (3)\n");
        batch(argv);
    }
    else
    {
        printf("\nNumero de argumentos invalido (%i).\n", argc);
        return -1; // Inválido
    }

    return 0;
}
