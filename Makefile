CC = gcc
LDFLAGS = -Llibraries/raylib -lraylib -lm -ldl -lpthread -lGL -lrt -lX11
SRC = src/*.c
OUTPUT = buildOut/game

WEB-CC = emcc
WEB-FLAGS = -Llibraries/raylib -lm -Iinclude -s USE_GLFW=3 -s USE_WEBGL2=1 -s FULL_ES3=1 -s ASYNCIFY -s ALLOW_MEMORY_GROWTH=1
WEB-OUT = buildOut/index.html

program:
	$(CC) $(SRC) -o $(OUTPUT) $(LDFLAGS)

web:
	$(WEB-CC) $(SRC) -o $(WEB-OUT) $(WEB-FLAGS)

clean:
	rm -f $(OUTPUT) $(WEB-OUT)
