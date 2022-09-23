C=gcc	
CFLAGS=-W -Wall
LDFLAGS=
EXEC=app
SRC= ../generator/generator.c app.c
OBJ= $(SRC:.c=.o)

all: $(EXEC)

app: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(LDFLAGS) -I ../generator

.PHONY: clean mrproper

clean:
	rm -rf ../**/*.o

mrproper: clean
	rm -rf $(EXEC)