# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
# GRAMATICAS PARA DEFINIR EL LENGUAJE
gramatica_sintactica = bison.y
gramatica_lexica=flex.l

# Archivos fuente
SRCS = parser.c
EXEC = ejecutable

# Limpiar archivos compilados
clean:
	rm -f $(EXEC) y.tab.c lex.yy.c y.tab.h
generar_ejecutable:
	bison -yd $(gramatica_sintactica)
	flex $(gramatica_lexica)
	$(CC) y.tab.c lex.yy.c -o $(EXEC)

# Regla por defecto para compilar el programa
all: $(EXEC)

$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS)

# Reglas para ejecutar el programa con diferentes archivos de entrada
ejemplo1: $(EXEC)
	./$(EXEC) ejemplo1.micro

ejemplo2: $(EXEC)
	./$(EXEC) ejemplo2.micro