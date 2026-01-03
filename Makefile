CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: app

app: main.c game.c game.h
	$(CC) $(CFLAGS) -o app main.c game.c

test:
	$(CC) $(CFLAGS) -DTESTING -o game_test game_test.c game.c
	./game_test

game_test: game_test.c game.c game.h
	$(CC) $(CFLAGS) -DTESTING -o game_test game_test.c game.c

coverage: game_test.c game.c game.h
	$(CC) $(CFLAGS) -DTESTING --coverage -o game_test game_test.c game.c
	./game_test
	gcov game.c

check-warnings:
	$(CC) $(CFLAGS) -Werror -DTESTING -fsyntax-only game_test.c game.c

clean:
	rm -f game_test app *.gcda *.gcno *.gcov

.PHONY: all test clean coverage check-warnings
