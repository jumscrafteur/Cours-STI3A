OBJS = main.o mini_memory.o mini_string.o mini_io.o
SOURCE	= main.c mini_memory.c mini_string.c mini_io.c
HEADER	= mini_lib.h
OUT	= main
CC	= gcc
FLAGS	= -g -c -Wall
LFLAGS	= 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c 

clean:
	rm -f $(OBJS) $(OUT) 