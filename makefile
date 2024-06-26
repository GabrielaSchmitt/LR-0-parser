CC = gcc
CFLAGS = -Iinclude
SRC = src/transducer.c src/stack.c src/parser.c main.c
OBJ = $(SRC:.c=.o)
EXEC = meu_programa

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJ) $(EXEC)
