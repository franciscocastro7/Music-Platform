#include "../include/artists.h"
#include "../include/validation.h"

struct artist
{
    char *id;
    char *name;
    //char *description;
    float recipe_per_stream;
    char **id_constituent;
    char *country;
    char *type;
};

Artist *create_artist_from_line(char *linha, FILE *artists_errors)
{
    Artist *new_artist = init_artist();
    if (new_artist == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória para artista.\n");
        return NULL;
    }

    char *aux = strdup(linha);
    if (aux == NULL)
    {
        fprintf(stderr, "Erro ao duplicar linha para processamento.\n");
        free_artist(new_artist);
        return NULL;
    }
    char *aux2 = aux; // Salvar o ponteiro original para liberar depois

    char *token;
    int constituent_count = 0;
    char **id_constituent = NULL;

    // Processa o ID do artista
    token = strsep(&aux, ";");
    remove_quotes(token);
    set_artist_id(new_artist, token);

    // Processa o nome do artista
    token = strsep(&aux, ";");
    set_artist_name(new_artist, token);

    // Ignora a descrição
    token = strsep(&aux, ";");

    // Processa receita por stream
    token = strsep(&aux, ";");
    if (token)
    {
        remove_quotes(token);
        float recipe_per_stream;
        if (sscanf(token, "%f", &recipe_per_stream) == 1)
        {
            set_artist_recipe_per_stream(new_artist, recipe_per_stream);
        }
    }

    // Processa constituintes
    token = strsep(&aux, ";");
    remove_quotes(token);
    if (token && strcmp(token, "[]") != 0)
    {
        id_constituent = malloc(10 * sizeof(char *));
        if (id_constituent == NULL)
        {
            fprintf(stderr, "Erro ao alocar memória para constituintes.\n");
            free(aux2);
            free_artist(new_artist);
            return NULL;
        }

        char *constituent_token = strtok(token, ",");
        while (constituent_token != NULL)
        {
            id_constituent[constituent_count] = strdup(constituent_token);
            if (id_constituent[constituent_count] == NULL)
            {
                fprintf(stderr, "Erro ao alocar memória para constituinte.\n");

                // Libera memória alocada até agora
                for (int i = 0; i < constituent_count; i++)
                {
                    free(id_constituent[i]);
                }
                free(id_constituent);
                free(aux2);
                free_artist(new_artist);
                return NULL;
            }
            constituent_count++;
            constituent_token = strtok(NULL, ",");
        }
        id_constituent[constituent_count] = NULL;
        set_artist_constituents(new_artist, id_constituent, constituent_count);
    }
    else
    {
        set_artist_constituents(new_artist, NULL, 0);
    }

    // Processa país
    token = strsep(&aux, ";");
    set_artist_country(new_artist, token);

    // Processa tipo do artista
    token = strsep(&aux, ";");
    remove_quotes(token);
    if (set_artist_type(new_artist, token) == 0)
    {
        fprintf(artists_errors, "%s\n", linha);

        // Libera memória em caso de tipo inválido
        if (id_constituent)
        {
            for (int i = 0; i < constituent_count; i++)
            {
                free(id_constituent[i]);
            }
            free(id_constituent);
        }
        free(aux2);
        free_artist(new_artist);
        return NULL;
    }

    // Validações adicionais
    if (!is_individual_artist_valid(new_artist->type, new_artist->id_constituent, constituent_count))
    {
        fprintf(artists_errors, "%s\n", linha);

        // Libera memória em caso de validação falhar
        if (id_constituent)
        {
            for (int i = 0; i < constituent_count; i++)
            {
                free(id_constituent[i]);
            }
            free(id_constituent);
        }
        free(aux2);
        free_artist(new_artist);
        return NULL;
    }

    // Libera memória temporária usada no processamento
    free(aux2);
    if (id_constituent)
    {
        for (int i = 0; i < constituent_count; i++)
        {
            free(id_constituent[i]);
        }
        free(id_constituent);
    }
    return new_artist;
}



char *get_artist_id(Artist *artist)
{
    if (artist == NULL || artist->id == NULL)
    {
        return NULL; // Retorna NULL se o artista ou o id for NULL
    }
    return strdup(artist->id);
}

char *get_artist_name(Artist *artist)
{
    return strdup(artist->name);
}

/*char *get_artist_description(Artist *artist)
{
    return strdup(artist->description);
}*/

float get_artist_recipe_per_stream(Artist *artist)
{
    return artist->recipe_per_stream;
}

char *get_artist_country(Artist *artist)
{
    return strdup(artist->country);
}

char **get_artist_constituents(Artist *artist)
{
    if (artist->id_constituent == NULL)
    {
        return NULL;
    }

    int count = 0;
    while (artist->id_constituent[count] != NULL)
    {
        count++;
    }

    char **copy = malloc((count + 1) * sizeof(char *));
    if (copy == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < count; i++)
    {
        copy[i] = strdup(artist->id_constituent[i]);
    }
    copy[count] = NULL;

    return copy;
}

char *get_artist_type(Artist *artist)
{
    return strdup(artist->type);
}

void set_artist_id(Artist *artist, char *id) {
    if (!id || strlen(id) == 0) { // Verifica se id é NULL ou vazio
        artist->id = NULL; // Define como NULL se não for válido
        return;
    }
    artist->id = malloc(strlen(id) + 1);
    if (artist->id)
        strcpy(artist->id, id);
}

void set_artist_name(Artist *artist, char *name) {
    if (!name || strlen(name) == 0) { // Verifica se name é NULL ou vazio
        artist->name = NULL; // Define como NULL se não for válido
        return;
    }
    artist->name = malloc(strlen(name) + 1);
    if (artist->name)
        strcpy(artist->name, name);
}

/*void set_artist_description(Artist *artist, char *description) {
    if (!description || strlen(description) == 0) { // Verifica se description é NULL ou vazio
        artist->description = NULL; // Define como NULL se não for válido
        return;
    }
    artist->description = malloc(strlen(description) + 1);
    if (artist->description)
        strcpy(artist->description, description);
}*/

void set_artist_recipe_per_stream(Artist *artist, float recipe_per_stream) {
    // Para valores numéricos, não é necessário validar se é "nulo".
    artist->recipe_per_stream = recipe_per_stream;
}

void set_artist_country(Artist *artist, char *country) {
    if (!country || strlen(country) == 0) { // Verifica se country é NULL ou vazio
        artist->country = NULL; // Define como NULL se não for válido
        return;
    }
    artist->country = malloc(strlen(country) + 1);
    if (artist->country)
        strcpy(artist->country, country);
}

void set_artist_constituents(Artist *artist, char **constituents, int num_constituents) {
    if (!constituents || num_constituents <= 0) { // Verifica se constituents é NULL ou vazio
        artist->id_constituent = NULL; // Define como NULL se não for válido
        return;
    }

    artist->id_constituent = malloc((num_constituents + 1) * sizeof(char *));
    if (!artist->id_constituent)
        return;

    for (int i = 0; i < num_constituents; i++) {
        if (constituents[i]) {
            artist->id_constituent[i] = malloc(strlen(constituents[i]) + 1);
            if (artist->id_constituent[i])
                strcpy(artist->id_constituent[i], constituents[i]);
        } else {
            artist->id_constituent[i] = NULL; // Define como NULL se um constituinte for inválido
        }
    }
    artist->id_constituent[num_constituents] = NULL; // Termina com NULL
}

int set_artist_type(Artist *artist, char *type) {
    if (!type || strlen(type) == 0) // Verifica se type é NULL ou vazio
        return 0; // Valor inválido

    // Validação dos valores permitidos para 'type' (case-insensitive)
    if (strcasecmp(type, "individual") == 0 || strcasecmp(type, "group") == 0) {
        free(artist->type); // Libera memória previamente alocada
        artist->type = strdup(type); // Duplica o valor original fornecido
        if (!artist->type)
            return 0; // Verifica falha na alocação
        return 1; // Sucesso
    }
    return 0; // Valor inválido
}

Artist *init_artist()
{
    Artist *new_artist = malloc(sizeof(Artist));

    new_artist->id = NULL;
    new_artist->name = NULL;
    //new_artist->description = NULL;
    new_artist->recipe_per_stream = 0;
    new_artist->id_constituent = NULL;
    new_artist->country = NULL;
    new_artist->type = NULL;

    return new_artist;
}


void free_artist(Artist *artist)
{
    if (artist == NULL)
        return;
    if (artist->id)
    {
        free(artist->id);
    }
    if (artist->name)
    {
        free(artist->name);
    }
    /*if (artist->description)
    {
        free(artist->description);
    }*/
    if (artist->id_constituent != NULL)
    {
        for (int i = 0; artist->id_constituent[i] != NULL; i++)
        {
            free(artist->id_constituent[i]);
        }
        free(artist->id_constituent);
    }

    if (artist->country)
    {
        free(artist->country);
    }
    if (artist->type)
    {
        free(artist->type);
    }
    free(artist);
}