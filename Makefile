CC = gcc

CFLAGS = -Wall -g -Iinclude `pkg-config --cflags glib-2.0`
LDFLAGS = -lm `pkg-config --cflags --libs glib-2.0`

RESULT_DIR = resultados

all: $(RESULT_DIR) main test interactive

main: src/main.o src/artists.o src/users.o src/batch.o src/parser.o src/files.o src/artistsmanager.o src/musicsmanager.o src/musics.o src/usersmanager.o src/query1.o src/query2.o src/interpreter.o src/validation.o src/database_manager.o src/query3.o src/query6.o src/history.o src/historymanager.o src/albums.o src/albumsmanager.o src/query4.o src/utils.o
	$(CC) $^ $(LDFLAGS) -o programa-principal

test: src/test.o src/artists.o src/users.o src/batch.o src/parser.o src/files.o src/artistsmanager.o src/musicsmanager.o src/musics.o src/usersmanager.o src/query1.o src/query2.o src/interpreter.o src/validation.o src/database_manager.o src/query3.o src/query6.o src/history.o src/historymanager.o src/albums.o src/albumsmanager.o src/query4.o src/utils.o
	$(CC) $^ $(LDFLAGS) -o programa-testes

interactive: src/interactive.o src/artists.o src/users.o src/batch.o src/parser.o src/files.o src/artistsmanager.o src/musicsmanager.o src/musics.o src/usersmanager.o src/query1.o src/query2.o src/interpreter.o src/validation.o src/database_manager.o src/query3.o src/query6.o src/history.o src/historymanager.o src/albums.o src/albumsmanager.o src/query4.o  src/utils.o
	$(CC) $^ $(LDFLAGS) -o programa-interativo

src/main.o : src/main.c include/main.h
	$(CC) $(CFLAGS) -c $< -o $@

src/test.o : src/test.c include/test.h
	$(CC) $(CFLAGS) -c $< -o $@	

src/artists.o : src/artists.c include/artists.h
	$(CC) $(CFLAGS) -c $< -o $@

src/users.o : src/users.c include/users.h
	$(CC) $(CFLAGS) -c $< -o $@

src/files.o : src/files.c include/files.h
	$(CC) $(CFLAGS) -c $< -o $@

src/batch.o : src/batch.c include/batch.h
	$(CC) $(CFLAGS) -c $< -o $@

src/parser.o : src/parser.c include/parser.h
	$(CC) $(CFLAGS) -c $< -o $@

src/artistsmanager.o : src/artistsmanager.c include/artistsmanager.h
	$(CC) $(CFLAGS) -c $< -o $@

src/musics.o : src/musics.c include/musics.h
	$(CC) $(CFLAGS) -c $< -o $@

src/musicsmanager.o : src/musicsmanager.c include/musicsmanager.h
	$(CC) $(CFLAGS) -c $< -o $@

src/usersmanager.o : src/usersmanager.c include/usersmanager.h
	$(CC) $(CFLAGS) -c $< -o $@

src/query1.o : src/query1.c include/query1.h
	$(CC) $(CFLAGS) -c $< -o $@

src/query2.o : src/query2.c include/query2.h
	$(CC) $(CFLAGS) -c $< -o $@

src/interpreter.o : src/interpreter.c include/interpreter.h
	$(CC) $(CFLAGS) -c $< -o $@

src/validation.o : src/validation.c include/validation.h
	$(CC) $(CFLAGS) -c $< -o $@	

src/database_manager.o : src/database_manager.c include/database_manager.h
	$(CC) $(CFLAGS) -c $< -o $@	

src/query3.o : src/query3.c include/query3.h
	$(CC) $(CFLAGS) -c $< -o $@

src/query6.o : src/query6.c include/query6.h
	$(CC) $(CFLAGS) -c $< -o $@

src/history.o : src/history.c include/history.h
	$(CC) $(CFLAGS) -c $< -o $@

src/historymanager.o : src/historymanager.c include/historymanager.h
	$(CC) $(CFLAGS) -c $< -o $@

src/albums.o : src/albums.c include/albums.h
	$(CC) $(CFLAGS) -c $< -o $@

src/albumsmanager.o : src/albumsmanager.c include/albumsmanager.h
	$(CC) $(CFLAGS) -c $< -o $@

src/query4.o : src/query4.c include/query4.h
	$(CC) $(CFLAGS) -c $< -o $@

src/interactive.o : src/interactive.c include/interactive.h
	$(CC) $(CFLAGS) -c $< -o $@

src/utils.o : src/utils.c include/utils.h
	$(CC) $(CFLAGS) -c $< -o $@

$(RESULT_DIR):
	mkdir -p $(RESULT_DIR)

clean:
	rm -f programa-principal programa-testes programa-interativo src/*.o
	rm -rf $(RESULT_DIR)