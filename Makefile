CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Targets
all: app

app: main.c main.h
	$(CC) $(CFLAGS) -o app main.c

test:
	$(CC) $(CFLAGS) -DTESTING -o main_test main_test.c main.c
	./main_test

main_test: main_test.c main.c main.h
	$(CC) $(CFLAGS) -DTESTING -o main_test main_test.c main.c

coverage: main_test.c main.c main.h
	$(CC) $(CFLAGS) -DTESTING --coverage -o main_test main_test.c main.c
	./main_test
	gcov main.c

clean:
	rm -f main_test app *.gcda *.gcno *.gcov

.PHONY: all test clean coverage
