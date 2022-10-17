C=gcc
CFLAGS=-W -Wall -std=c99
LDFLAGS=
EXEC=app
SRC= arithmetika/mathematika/mathematika.c arithmetika/crypto/crypto.c arithmetika/app.c
OBJ= $(SRC:.c=.o)

all: $(EXEC)

app: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)


%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) -Iarithmetika/mathematika -Iarithmetika/crypto

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)