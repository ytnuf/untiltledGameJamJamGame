CC = gcc
LDFLAGS = -Llibraries -lraylib -lm
PROFFLAGS = -g -pg
WINCC = x86_64-w64-mingw32-gcc
WINFLAGS = -Llibraries/windows -lgdi32 -luser32 -lwinmm -lkernel32 -lopengl32
LINFLAGS = -Llibraries/linux
LDFLAGS = -lraylib -lm
SRC = src/*.c
OUTPUT = build/game

program:
	$(CC) $(SRC) -o $(OUTPUT) $(LDFLAGS) $(LINFLAGS)

windows:
	$(WINCC) $(SRC) -o $(OUTPUT) $(LDFLAGS) $(WINFLAGS)

profile:
	$(CC) $(SRC) -o $(OUTPUT) $(LDFLAGS) $(PROFFLAGS)

clean:
	rm -f $(OUTPUT)* $(WEB-OUT)
