CC = gcc
LDFLAGS = -Llibraries -lraylib -lm
SRC = src/*.c
OUTPUT = game

program:
	$(CC) $(SRC) -o $(OUTPUT) $(LDFLAGS)

clean:
	rm -f $(OUTPUT) $(WEB-OUT)
