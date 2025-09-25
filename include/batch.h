#ifndef BATCH_H
#define BATCH_H

#include "main.h"
#include "parser.h"
#include "artists.h"
#include "artistsmanager.h"
#include "musics.h"
#include "musicsmanager.h"
#include "files.h"
#include "users.h"
#include "usersmanager.h"
#include "interpreter.h"
#include "database_manager.h"
#include "history.h"
#include "historymanager.h"
#include "albumsmanager.h"


/**
 * @brief Abertura de Arquivos, verificar erros e processar a batch de dados
 * 
 * A função batch é responsável por processar diversos ficheiros CSV contendo dados sobre artistas, músicas, álbuns, 
 * utilizadores e histórico. Ela realiza o processamento desses ficheiros para inicializar um gerenciador de base de dados 
 * Database_Manager e executa comandos com base nos inputs fornecidos
 * 
 * @param argv -> Apontador para um array
 * @return (Função do tipo VOID)
 */

void batch(char **argv);


#endif // BATCH_H