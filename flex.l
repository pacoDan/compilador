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
"inicio" {return INICIO;}
"fin" {return FIN;}
"leer" {return LEER;}
"escribir" {return ESCRIBIR;}
":=" {return ASIGNACION;}
{constEntera} {yylval.num=atoi(yytext);return CONSTANTE;}
";" {return PYCOMA;}
"," {return COMA;}
"(" {return PARENIZQUIERDO;}
")" {return PARENDERECHO;}
"+" {return SUMA;}
"-" {return RESTA;}
{IDENTIFICADOR} {yylval.cadena = strdup(yytext); return ID;}
%%