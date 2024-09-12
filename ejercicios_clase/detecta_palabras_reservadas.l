%{
#include <stdlib.h>
#ifndef yywrap
    static int yywrap(void) { return 1;}
#endif
%}
RESERVADA    ^(inicio|fin|leer|escribir)$
%%
{RESERVADA}    printf( "una palabra reservada es: %s de longitud %d\n", yytext, yyleng);
.       printf("NO SE RECONOCE PAL RESERV.=\"%s\"!!",yytext);
%%
int main() {
    yylex();
}