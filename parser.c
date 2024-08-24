#include "parser.h"
typedef struct
{
    char identifi[TAMLEX];
    TOKEN t;
    /* t=0, 1, 2, 3 Palabra Reservada, t=ID=4 Identificador */
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

// ------------------
// Aproximacion a C
/**********Procedimientos de Analisis Sintactico (PAS) *****************/
void Objetivo(void)
{
    /* <objetivo>
    -
    > <programa> FDT #terminar */
    Programa();
    Match(FDT);
    Terminar();
}
void Programa(void)
{
    /* <programa>
    -
    > #comenzar INICIO <listaSentencias> FIN */
    Comenzar();
    Match(INICIO);
    ListaSentencias();
    Match(FIN);
}
void ListaSentencias(void)
{
    /* <listaSentencias>
    -
    > <sentencia> {<sentencia>} */
    Sentencia();
    while (1)
    {
        switch (ProximoToken())
        {
        case ID:
        case LEER:
        case ESCRIBIR:
            Sentencia();
            break;
        default:
            return;
        }
    }
}
void Sentencia(void)
{
    TOKEN tok = ProximoToken();
    REG_EXPRESION izq, der;
    switch (tok)
    {
    case ID:
        /* <sentencia>
        -
        > ID := <expresion> #asignar ; */
        Identificador(&izq);
        Match(ASIGNACION);
        Expresion(&der);
        Asignar(izq, der);
        Match(PUNTOYCOMA);
        break;
    case LEER:
        /* <sentencia>
        -
        > LEER ( <listaIdentificadores> ) */
        Match(LEER);
        Match(PARENIZQUIERDO);
        ListaIdentificadores();
        Match(PARENDERECHO);
        Match(PUNTOYCOMA);
        break;
    case ESCRIBIR:
        /* <sentencia>
        -
        > ESCRIBIR ( <listaExpresiones> ) */
        Match(ESCRIBIR);
        Match(PARENIZQUIERDO);
        ListaExpresiones();
        Match(PARENDERECHO);
        Match(PUNTOYCOMA);
        break;
    default:
        return;
    }
}
void ListaIdentificadores(void)
{
    /* <listaIdentifi
    cadores>
    -
    > <identificador> #leer_id {COMA <identificador> #leer_id} */
    TOKEN t;
    REG_EXPRESION reg;
    Identificador(&reg);
    Leer(reg);
    for (t = ProximoToken(); t == COMA; t = ProximoToken())
    {
        Match(COMA);
        Identificador(&reg);
        Leer(reg);
    }
}
void Identificador(REG_EXPRESION *presul)
{
    /* <identificador>
    -
    > ID #procesar_id */
    Match(ID);
    *presul = ProcesarId();
}
void ListaExpresiones(void)
{
    /* <listaExpresiones>
    -
    > <expresion> #escribir_exp {COMA <expresion> #escribir_exp} */
    TOKEN t;
    REG_EXPRESION reg;
    Expresion(&reg);
    Escribir(reg);
    for (t = ProximoToken(); t == COMA; t = ProximoToken())
    {
        Match(COMA);
        Expresion(&reg);
        Escribir(reg);
    }
}

void Expresion(REG_EXPRESION *presul)
{
    /* <expresion>
    -
    > <primaria> { <operadorAditivo> <primaria> #gen_infijo } */
    REG_EXPRESION operandoIzq, operandoDer;
    char op[TAMLEX];
    TOKEN t;
    Primaria(&operandoIzq);
    for (t = ProximoToken(); t == SUMA || t == RESTA; t = ProximoToken())
    {
        OperadorAditivo(op);
        Primaria(&operandoDer);
        operandoIzq = GenInfijo(operandoIzq, op, operandoDer);
    }
    *presul = operandoIzq;
}
void Primaria(REG_EXPRESION *presul)
{
    TOKEN tok = ProximoToken();
    switch (tok)
    {
    case ID:
        /* <primaria>
        -
        > <identificador> */
        Identificador(presul);
        break;
    case CONSTANTE:
        /* <primaria>
        -
        > CONSTANTE #procesar_cte */
        Match(CONSTANTE);
        *presul = ProcesarCte();
        break;
    case PARENIZQUIERDO:
        /* <primaria>
        -
        > PARENIZQUIERDO <expre
        sion>
        PARENDERECHO */
        Match(PARENIZQUIERDO);
        Expresion(presul);
        Match(PARENDERECHO);
        break;
    default:
        return;
    }
}
void OperadorAditivo(char *presul)
{
    /* <operadorAditivo>
    -
    > SUMA #procesar_op | RESTA #procesar_op */
    TOKEN t = ProximoToken();
    if (t == SUMA || t == RESTA)
    {
        Match(t);
        strcpy(presul, ProcesarOp());
    }
    else
        ErrorSintactico(t);
}

/**********************Rutinas Semanticas******************************/
REG_EXPRESION ProcesarCte(void)
{
    /* Convierte cadena que representa numero a numero entero y construye un registro
    semantico */
    REG_EXPRESION reg;
    reg.clase = CONSTANTE;
    strcpy(reg.nombre, buffer);
    sscanf(buffer, "%d", &reg.valor);
    return reg;
}
REG_EXPRESION ProcesarId(void)
{
    /*
    Declara ID y construye el correspondiente registro semantico */
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
    /* Genera la inst
    ruccion para escribir */
    Generar("Write", Extraer(&out), "Entera", "");
}
REG_EXPRESION GenInfijo(REG_EXPRESION e1, char *op, REG_EXPRESION e2)
{
    /* Genera la instruccion para una operacion infija y construye un registro semantico con el
    resultado */
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
/*********
******Funciones Auxiliares**********************************/
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
    /* Retorn
    a la cadena del registro semantico */
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