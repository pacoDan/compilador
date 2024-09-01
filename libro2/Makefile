# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Reglas generales
all: clean

# Regla por defecto (para evitar errores si se ejecuta sin especificar un objetivo)
default: all

# Regla dinámica para compilar y ejecutar un ejercicio específico
%: %.c
	$(CC) $(CFLAGS) -o $@ $<
	./$@

# Regla para limpiar archivos ejecutables
clean:
	find . -type f -executable -exec rm -f {} +
