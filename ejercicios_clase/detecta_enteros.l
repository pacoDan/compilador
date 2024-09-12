%{
#include <stdlib.h>
#ifndef yywrap
    static int yywrap(void) { return 1;}
#endif
%}
ENTERO    [+-]?[0-9]+
%%
{ENTERO}    printf( "entero num: %s de longitud %d\n", yytext, yyleng);
.       printf("NO SE RECONOCE ENTERO \"%s\"!!",yytext);
%%
int main() {
    yylex();
}