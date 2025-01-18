CC = gcc
LDFLAGS = -Llibraries -lraylib -lm
PROFFLAGS = -g -pg
SRC = src/*.c
OUTPUT = game

program:
	$(CC) $(SRC) -o $(OUTPUT) $(LDFLAGS)

profile:
	$(CC) $(SRC) -o $(OUTPUT) $(LDFLAGS) $(PROFFLAGS)

clean:
	rm -f $(OUTPUT) $(WEB-OUT)
