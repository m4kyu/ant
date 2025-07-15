main: src/main.c chunk.o
	gcc src/main.c bin/chunk.o -o main -lraylib -lGL -lm -lpthread -ldl -lrt -lX11


chunk.o: src/chunk.c
	gcc -c src/chunk.c -o bin/chunk.o
