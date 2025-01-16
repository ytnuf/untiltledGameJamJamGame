CC = gcc
CFLAGS = -lm -lraylib
SRC = src/*.c
OUTPUT = game
program:
	$(CC) $(CFLAGS) $(SRC) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)
