// Compilador del Lenguaje Micro (Fischer)

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define NUMESTADOS 15
#define NUMCOLS 13
#define TAMLEX 32 + 1
#define TAMNOM 20 + 1

/******************Declaraciones Globales*************************/
FILE *in;
typedef enum
{
    INICIO,
    FIN,
    LEER,
    ESCRIBIR,
    ID,
    CONSTANTE,
    PARENIZQUIERDO,
    PARENDERECHO,
    PUNTOYCOMA,
    COMA,
    ASIGNACION,
    SUMA,
    RESTA,
    FDT,
    ERRORLEXICO
} TOKEN;

// ---------

typedef struct

{

    char identifi[TAMLEX];

    TOKEN t; /* t=0, 1, 2, 3 Palabra Reservada, t=ID=4 Identificador */

} RegTS;

RegTS TS[1000] = {{"inicio", INICIO}, {"fin", FIN}, {"leer", LEER}, {"escribir", ESCRIBIR}, {"$", 99}};

typedef struct

{

    TOKEN clase;

    char nombre[TAMLEX];

    int valor;

} REG_EXPRESION;

char buffer[TAMLEX];

TOKEN tokenActual;

int flagToken = 0;

TOKEN scanner();
int estadoFinal(int);
int columna(int);