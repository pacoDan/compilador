#include "parser.h"
#include "scanner.h"
/**********Procedimientos de Analisis Sintactico (PAS) *****************/
void Objetivo(void)
{
    /* <objetivo> -><programa> FDT #terminar */
    Programa();
    Match(FDT);
    Terminar();
}

void Programa(void)
{
    /* <programa> -> #comenzar INICIO <listaSentencias> FIN */
    Comenzar();
    Match(INICIO);
    ListaSentencias();
    Match(FIN);
}

void ListaSentencias(void)
{
    /* <listaSentencias> -><sentencia> {<sentencia>} */

    Sentencia();
    while(1)
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
    case ID: /* <sentencia> -> ID := <expresion> #asignar ; */
        Identificador(&izq);
        Match(ASIGNACION);
        Expresion(&der);
        Asignar(izq, der);
        Match(PUNTOYCOMA);
        break;
    case LEER: /* <sentencia> -> LEER ( <listaIdentificadores> ) */
        Match(LEER);
        Match(PARENIZQUIERDO);
        ListaIdentificadores();
        Match(PARENDERECHO);
        Match(PUNTOYCOMA);
        break;
    case ESCRIBIR: /* <sentencia> -> ESCRIBIR ( <listaExpresiones> ) */
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
    /* <listaIdentificadores> -><identificador> #leer_id {COMA <identificador> #leer_id} */

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
    /* <identificador> -> ID #procesar_id */

    Match(ID);
    *presul = ProcesarId();
}

void ListaExpresiones(void)
{
    /* <listaExpresiones> -><expresion> #escribir_exp {COMA <expresion> #escribir_exp} */

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
    /* <expresion> -><primaria>{ <operadorAditivo><primaria> #gen_infijo } */

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
    case ID: /* <primaria> -><identificador> */
        Identificador(presul);
        break;
    case CONSTANTE: /* <primaria> -> CONSTANTE #procesar_cte */
        Match(CONSTANTE);
        *presul = ProcesarCte();
        break;
    case PARENIZQUIERDO: /* <primaria> -> PARENIZQUIERDO <expresion> PARENDERECHO */
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
    /* <operadorAditivo> -> SUMA #procesar_op | RESTA #procesar_op */

    TOKEN t = ProximoToken();

    if (t == SUMA || t == RESTA)
    {
        Match(t);
        strcpy(presul, ProcesarOp());
    }
    else
        ErrorSintactico(t);
}