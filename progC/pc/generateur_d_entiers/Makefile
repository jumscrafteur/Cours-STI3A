C=gcc
CFLAGS=-W -Wall -std=c99
LDFLAGS=
EXEC=app
SRC= v5/generator/generator.c v5/principal/app.c
OBJ= $(SRC:.c=.o)

all: $(EXEC)

app: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)


%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) -I v5/generator

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)