CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Targets
all: app

app: main.c game.c game.h
	$(CC) $(CFLAGS) -o app main.c game.c

test:
	$(CC) $(CFLAGS) -DTESTING -o main_test main_test.c game.c
	./main_test

main_test: main_test.c game.c game.h
	$(CC) $(CFLAGS) -DTESTING -o main_test main_test.c game.c

coverage: main_test.c game.c game.h
	$(CC) $(CFLAGS) -DTESTING --coverage -o main_test main_test.c game.c
	./main_test
	gcov game.c

check-warnings:
	$(CC) $(CFLAGS) -Werror -DTESTING -fsyntax-only main_test.c game.c

clean:
	rm -f main_test app *.gcda *.gcno *.gcov

.PHONY: all test clean coverage check-warnings
