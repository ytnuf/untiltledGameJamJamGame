program:
	gcc src/*.c -lraylib -lm -o game -g -pg
profile:
	gprof game > prof
