// #include "parser.h"
// #include "scanner.h"
#include "analizadorSintactico.h"
/**********************Rutinas Semanticas******************************/

REG_EXPRESION ProcesarCte(void)
{
    /* Convierte cadena que representa numero a numero entero y construye un registro semantico */

    REG_EXPRESION reg;

    reg.clase = CONSTANTE;
    strcpy(reg.nombre, buffer);
    sscanf(buffer, "%d", &reg.valor);

    return reg;
}

REG_EXPRESION ProcesarId(void)
{
    /* Declara ID y construye el correspondiente registro semantico */

    REG_EXPRESION reg;

    Chequear(buffer);
    reg.clase = ID;
    strcpy(reg.nombre, buffer);

    return reg;
}

char *ProcesarOp(void)
{
    /* Declara OP y construye el correspondiente registro semantico */

    return buffer;
}

void Leer(REG_EXPRESION in)
{
    /* Genera la instruccion para leer */

    Generar("Read", in.nombre, "Entera", "");
}

void Escribir(REG_EXPRESION out)
{
    /* Genera la instruccion para escribir */

    Generar("Write", Extraer(&out), "Entera", "");
}

REG_EXPRESION GenInfijo(REG_EXPRESION e1, char *op, REG_EXPRESION e2)
{
    /* Genera la instruccion para una operacion infija y construye un registro semantico con el resultado */

    REG_EXPRESION reg;
    static unsigned int numTemp = 1;
    char cadTemp[TAMLEX] = "Temp&";
    char cadNum[TAMLEX];
    char cadOp[TAMLEX];

    if (op[0] == '-')
        strcpy(cadOp, "Restar");
    if (op[0] == '+')
        strcpy(cadOp, "Sumar");

    sprintf(cadNum, "%d", numTemp);
    numTemp++;
    strcat(cadTemp, cadNum);

    if (e1.clase == ID)
        Chequear(Extraer(&e1));
    if (e2.clase == ID)
        Chequear(Extraer(&e2));
    Chequear(cadTemp);
    Generar(cadOp, Extraer(&e1), Extraer(&e2), cadTemp);

    strcpy(reg.nombre, cadTemp);

    return reg;
}
/***************Funciones Auxiliares**********************************/

void Match(TOKEN t)
{
    if (!(t == ProximoToken()))
        ErrorSintactico();
    flagToken = 0;
}

TOKEN ProximoToken()
{
    if (!flagToken)
    {
        tokenActual = scanner();
        if (tokenActual == ERRORLEXICO)
            ErrorLexico();
        flagToken = 1;
        if (tokenActual == ID)
        {
            Buscar(buffer, TS, &tokenActual);
        }
    }

    return tokenActual;
}

void ErrorLexico()
{
    printf("Error Lexico\n");
}

void ErrorSintactico()
{
    printf("Error Sintactico\n");
}

void Generar(char *co, char *a, char *b, char *c)
{
    /* Produce la salida de la instruccion para la MV por stdout */

    printf("%s %s%c%s%c%s\n", co, a, ',', b, ',', c);
}

char *Extraer(REG_EXPRESION *preg)
{
    /* Retorna la cadena del registro semantico */

    return preg->nombre;
}

int Buscar(char *id, RegTS *TS, TOKEN *t)
{
    /* Determina si un identificador esta en la TS */

    int i = 0;

    while (strcmp("$", TS[i].identifi))
    {
        if (!strcmp(id, TS[i].identifi))
        {
            *t = TS[i].t;
            return 1;
        }
        i++;
    }
    return 0;
}

void Colocar(char *id, RegTS *TS)
{
    /* Agrega un identificador a la TS */

    int i = 4;

    while (strcmp("$", TS[i].identifi))
        i++;

    if (i < 999)
    {
        strcpy(TS[i].identifi, id);
        TS[i].t = ID;
        strcpy(TS[++i].identifi, "$");
    }
}

void Chequear(char *s)
{
    /* Si la cadena No esta en la Tabla de Simbolos la agrega,
       y si es el nombre de una variable genera la instruccion */

    TOKEN t;

    if (!Buscar(s, TS, &t))
    {
        Colocar(s, TS);
        Generar("Declara", s, "Entera", "");
    }
}

void Comenzar(void)
{
    /* Inicializaciones Semanticas */
}

void Terminar(void)
{
    /* Genera la instruccion para terminar la ejecucion del programa */

    Generar("Detiene", "", "", "");
}

void Asignar(REG_EXPRESION izq, REG_EXPRESION der)
{
    /* Genera la instruccion para la asignacion */

    Generar("Almacena", Extraer(&der), izq.nombre, "");
}
