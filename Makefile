CC = clang
IDIR = -I/opt/homebrew/include -I/Users/samuelreid/Desktop/programming/include
LDIR = -L/opt/homebrew/lib
CFLAGS = -Wall -Wpedantic -Wextra -Werror -std=gnu99 -Wno-unused-but-set-variable

all: glad window
	$(CC) $(IDIR) $(LDIR) $(CFLAGS) -lglfw .glad.o .window.o main.c program.c shaders.c -o game

glad:
	$(CC) $(IDIR) -Wall -Wextra -Werror -std=gnu99 -c glad.c -o .glad.o

window:
	$(CC) $(IDIR) $(CFLAGS) -Wno-unused-parameter -c window.c -o .window.o
  
clean:
	rm game .window.o .glad.o
