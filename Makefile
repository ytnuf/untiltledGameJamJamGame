CC = gcc
LDFLAGS = -Llibraries -lraylib -lm -ldl -lpthread -lGL -lrt -lX11
SRC = src/*.c
OUTPUT = game
program:
	$(CC) $(SRC) -o $(OUTPUT) $(LDFLAGS)

clean:
	rm -f $(OUTPUT)
