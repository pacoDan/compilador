# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Archivos fuente y ejecutable
SRCS = principal.c scanner.c parser.c
OBJS = $(SRCS:.c=.o)
EXEC = principal

# Regla por defecto para compilar el programa
all: $(EXEC)

# Regla para compilar el ejecutable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Regla para compilar archivos .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para ejecutar el programa con un archivo de entrada
run: $(EXEC)
	@echo "Debe especificar un archivo de entrada como argumento."
	@echo "Ejemplo: make ejemplo1"

ejemplo1: $(EXEC)
	./$(EXEC) ejemplo1.micro

ejemplo2: $(EXEC)
	./$(EXEC) ejemplo2.micro

# Regla para limpiar los archivos compilados
clean:
	rm -f $(OBJS) $(EXEC)

# Evitar errores cuando se pasa un argumento que no es un objetivo
%:
	@:
