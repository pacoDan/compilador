# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Archivos fuente
SRCS = principal.c scanner.c parser.c
EXEC = principal

# Regla por defecto para compilar el programa
all: $(EXEC)

$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS)

# Reglas para ejecutar el programa con diferentes archivos de entrada
ejemplo1: $(EXEC)
	./$(EXEC) ejemplo1.micro

ejemplo2: $(EXEC)
	./$(EXEC) ejemplo2.micro

# Limpiar archivos compilados
clean:
	rm -f $(EXEC)
