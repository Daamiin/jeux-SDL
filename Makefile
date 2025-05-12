CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXEC = game_menu

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f $(EXEC)

.PHONY: clean 