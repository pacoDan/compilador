%{
#include <stdlib.h>
#ifndef yywrap
    static int yywrap(void) { return 1;}
#endif
%}
DECIMAL    [+-]?[0-9]+[.,][0-9]+
%%
{DECIMAL}    printf( "decimal num: %s de longitud %d\n", yytext, yyleng);
.       printf("NO SE RECONOCE DECIMAL\"%s\"!!",yytext);
%%
int main() {
    yylex();
}