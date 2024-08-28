#include "parser.h"
// #include "scanner.h"
/**********************Rutinas Semanticas******************************/

REG_EXPRESION ProcesarCte(void);
REG_EXPRESION ProcesarId(void);
char *ProcesarOp(void);
void Leer(REG_EXPRESION in);
void Escribir(REG_EXPRESION out);
REG_EXPRESION GenInfijo(REG_EXPRESION e1, char *op, REG_EXPRESION e2);
/***************Funciones Auxiliares**********************************/

void Match(TOKEN t);
TOKEN ProximoToken();
void ErrorLexico();
void ErrorSintactico();
void Generar(char *co, char *a, char *b, char *c);
char *Extraer(REG_EXPRESION *preg);
int Buscar(char *id, RegTS *TS, TOKEN *t);
void Colocar(char *id, RegTS *TS);
void Chequear(char *s);
void Comenzar(void);
void Terminar(void);
void Asignar(REG_EXPRESION izq, REG_EXPRESION der);