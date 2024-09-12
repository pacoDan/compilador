# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Archivos fuente
EXEC = ejecutable

# Limpiar archivos compilados
clean:
	rm -f $(EXEC) lex.yy.c detecta_decimales detecta_enteros

# Genera el ejecutable con flex
detecta_decimales:
	flex detecta_decimales.l
	$(CC) lex.yy.c -o $(EXEC)
detecta_entero:
	flex detecta_enteros.l
	$(CC) lex.yy.c -o $(EXEC)
ejecutar:
	./$(EXEC)