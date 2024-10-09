%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "y.tab.h"
	#include <string.h>
%}
DIGITO [0-9]
LETRA [a-zA-Z]
IDENTIFICADOR {LETRA}({LETRA}|{DIGITO})*
constEntera {DIGITO}({DIGITO})*
%%
EOF {return FDT;}
"inicio" {puts("se ingreso token palabraReservada INICIO");return INICIO;}
"fin" {puts("se ingreso token palabraReservada FIN");return FIN;}
"leer" {puts("se ingreso token palabraReservada  LEER");return LEER;}
"escribir" {puts("se ingreso token palabraReservada  ESCRIBIR");return ESCRIBIR;}
":=" {puts("se ingreso token ASIGNACION");return ASIGNACION;}
{constEntera} {yylval.num=atoi(yytext);return CONSTANTE;}
";" {return PYCOMA;}
"," {return COMA;}
"(" {return PARENIZQUIERDO;}
")" {return PARENDERECHO;}
"+" {puts("se ingreso token palabraReservada SUMA");return SUMA;}
"-" {puts("se ingreso token palabraReservada RESTA");return RESTA;}
"*" {puts("se ingreso token palabraReservada MULTIPLICACION");return MULTIPLICACION;}
{IDENTIFICADOR} {yylval.cadena = strdup(yytext); return ID;}
%%
