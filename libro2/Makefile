# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Reglas generales
all: clean

# Regla por defecto (para evitar errores si se ejecuta sin especificar un objetivo)
default: all

ejercicio11:
	$(CC) $(CFLAGS) -o ejecutable ejercicio11.c
	./ejecutable
# Regla para limpiar archivos ejecutables
clean:
	find . -type f -executable -exec rm -f {} +

# Regla dinámica para compilar y ejecutar un ejercicio específico
%: %.c
	$(CC) $(CFLAGS) -o $@ $<
	./$@