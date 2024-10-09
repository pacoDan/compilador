%{
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
extern char *yytext;
extern int yyleng;
extern int yylex(void);
extern FILE* yyin;
extern void yyerror(char*);
void asignarIds(char* nombre, int valor);
int obtenerValorId(char* nombre);

struct Identificador{
   char* nombre;
   int valor;
}; 
struct Identificador identificadores[100];
int cantidadIdentificadores = 0;

%}
%union{
   char* cadena;
   int num;
} 

%token ASIGNACION PYCOMA RESTA SUMA MULTIPLICACION PARENIZQUIERDO PARENDERECHO INICIO FIN LEER ESCRIBIR COMA FDT
%token <cadena> ID
%token <num> CONSTANTE

%%

objetivo: programa FDT

programa: INICIO listaSentencias FIN

listaSentencias: listaSentencias sentencia 
|sentencia

sentencia: ID ASIGNACION expresion PYCOMA 
{
    char* nombre = $<cadena>1;
    int valor = $<num>3;
    asignarIds(nombre, valor);
}
|LEER PARENIZQUIERDO listaIds PARENDERECHO PYCOMA 
{
    int numero;
    char* cadena = $<cadena>3;
    char* token = strtok(cadena, ", ");
    while(token != NULL){
        printf("Ingresarle un valor a el id %s: ", token);
        scanf("%d", &numero);
        asignarIds(token, numero);
        token = strtok(NULL, " ,");
    }
}
|ESCRIBIR PARENIZQUIERDO listaExpresiones PARENDERECHO PYCOMA
;

listaIds: listaIds COMA ID 
{
    strcat($<cadena>1, ",");
    strcat($<cadena>1, $<cadena>3);
}
| ID
;

listaExpresiones: listaExpresiones COMA expresion
{
    printf("%d\n", $<num>3);
}
|expresion
{
    printf("%d\n", $<num>$);
}

expresion: termino 
| expresion SUMA termino {$<num>$ = $<num>1 + $<num>3;}
| expresion RESTA termino {$<num>$ = $<num>1 - $<num>3;}

termino: primaria 
| termino MULTIPLICACION primaria {$<num>$ = $<num>1 * $<num>3;}

primaria: ID 
{
    char* nombre = $<cadena>1;
    int valor = obtenerValorId(nombre);
    $<num>$ = valor;
}
| CONSTANTE 
| PARENIZQUIERDO expresion PARENDERECHO
{ $<num>$ = $<num>2; }
;

%%

/*int main() {
    yyparse();
}*/

void main(int argc,char **argv)
{
if (argc>1)
 yyin=fopen(argv[1],"rt");
else
 yyin=stdin;
yyparse();

}

void yyerror (char *s){
    printf ("ERROR: %s\n",s);
    exit(1);
}

int yywrap(){
    return 1;
}

void asignarIds(char* nombre, int valor) {
    int i;
    for (i = 0; i < cantidadIdentificadores; i++) {
        if (strcmp(identificadores[i].nombre, nombre) == 0) {
            identificadores[i].valor = valor;
            return;
        }
    }
    
    identificadores[cantidadIdentificadores].nombre = nombre; 
    identificadores[cantidadIdentificadores].valor = valor;
    cantidadIdentificadores++;
}

int obtenerValorId(char* nombre) {
    for (int i = 0; i < cantidadIdentificadores; i++) {
        if (strcmp(identificadores[i].nombre, nombre) == 0) {
            return identificadores[i].valor;
        }
    }
    char mensaje[100];
    sprintf(mensaje, "La variable %s no ha sido definida.\n", nombre);
    yyerror(mensaje);
    return 0; // Nunca se alcanza, pero evita una advertencia del compilador.
}
