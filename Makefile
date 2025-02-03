CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = src/main.c src/analisador_lexico.c src/analisador_sintatico.c src/analisador_semantico.c src/tabela_simbolos.c
OBJ = $(SRC:.c=.o)
TARGET = compilador

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

test: $(TARGET)
	./$(TARGET) testes/teste2.cminus
