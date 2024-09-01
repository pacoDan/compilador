#include <stdio.h>
#include <string.h>
int posCaracterInicial;
char *caracterActual;
int estadoActual;
int *estadosFinales; // posible lista de ints, podria usar array
// int estadosFinales[];
int mientrasHayaCaracteres(char);
void inicializoLaPila();
char *cadena; // cadena a analizar
int estadoTopeDeLaPila(int estadoActual, char topeDePila, char *caracterActual);
void resultados();
char *contenidoDePila();
char *_contenidoDePila;
#define ESTADORECHAZO 99

typedef struct
{
    int estado;
    char *simbolo;
} EstadoSimbolo;
// EstadoSimbolo _fila={{0, "$"},{1, "R"},{2, "R"},{2, "$"},{ESTADORECHAZO, "$"}};
EstadoSimbolo TM[4][3] = {
    {{1, "R$"}, {ESTADORECHAZO, "$"}, {ESTADORECHAZO, "$"}},
    {{1, "RR"}, {2, "e"}, {ESTADORECHAZO, "$"}},
    {{ESTADORECHAZO, "$"}, {2, "e"}, {ESTADORECHAZO, "$"}},
    {{ESTADORECHAZO, "$"}, {ESTADORECHAZO, "$"}, {3, "$"}}};
int fila(int estado, char simbolo);
int columna(char c);
void pop();
void push();
char topeDePila();
int main(int argc, char const *argv[])
{
    posCaracterInicial = 0;
    cadena = "aabb",
    inicializoLaPila();
    estadosFinales=NULL;
    caracterActual = cadena[0];
    printf("Probando ejercicio 11 con %s \n!!", cadena);
    while (mientrasHayaCaracteres(caracterActual) && estadoActual!=ESTADORECHAZO)
    {
        estadoActual = estadoTopeDeLaPila(estadoActual, topeDePila(), caracterActual);
        caracterActual = cadena[posCaracterInicial++];
    }
    resultados();
    liberoPilaYRecursos();
    return 0;
}
char topeDePila(){
    puts("topeDePila()");
    return _contenidoDePila[0];
}
void liberoPilaYRecursos(){
    free(_contenidoDePila);
}
void resultados()
{
    if(estadoActual==ESTADORECHAZO) mostrarPilaYEstadoActual();
    if (criterioEstadoFinal() || criterioPilaVacia())
        printf("se Reconoce la Cadena %s \n", cadena);
    else
        mostrarPilaYEstadoActual();
}
void mostrarPilaYEstadoActual()
{
    fprintf(stderr,"NO SE RECONOCE LA CADENA %s\n",cadena);
    fprintf(stderr, "la pila tiene contenido: %s\n", contenidoDePila());
    fprintf(stderr, "el estado actual es -> %d\n", estadoActual);
    fprintf(stderr,"estado de rechazo es %d\n",ESTADORECHAZO);    
}
int mientrasHayaCaracteres(char c)
{
    return c != '\0' && c != 'EOF';
}
void inicializoLaPila()
{
    // _contenidoDePila = strdup("$");
     _contenidoDePila = (char*)malloc(2 * sizeof(char)); 
}
int estadoTopeDeLaPila(int estadoActual, char topeDePila, char *caracterActual)
{
    puts("estadoTopeDeLaPila()");
    EstadoSimbolo registro = TM[fila(estadoActual,topeDePila)][columna(caracterActual)];
    if(strcmp("e",registro.simbolo)) pop();
    if(strcmp("$",registro.simbolo));
    if(strcmp("R$",registro.simbolo)) push();
    if(strcmp("RR",registro.simbolo)) push();
    printf("movimiento:  %d,%s=>%s=>%d,%s\n",estadoActual,topeDePila,caracterActual,registro.estado,registro.simbolo);
    return registro.estado;
}
// Función para encontrar la posición en el vector _fila
int fila(int estado, char simbolo) {
    // for (int i = 0; i < sizeof(_fila) / sizeof(_fila[0]); ++i) {
    //     if (_fila[i].estado == estado && strcmp(_fila[i].simbolo, simbolo) == 0) {
    //         return i; // Retorna la posición si se encuentra la coincidencia
    //     }
    // }
     // Verificación simple basada en los valores del ejemplo
    if (estado == 0 && simbolo == '$') return 0;
    else if (estado == 1 && simbolo == 'R') return 1;
    else if (estado == 2 && simbolo == 'R') return 2;
    else if (estado == 2 && simbolo == '$') return 3;
    else if (estado == ESTADORECHAZO && simbolo == '$') return 4;
    else perror("fila()");
    return -1; // Retorna -1 si no se encuentra la coincidencia
}
int columna(char c){
    if(c='a' || strcmp(c,"a")) return 0;
    if(c='b' || strcmp(c,"b")) return 1;
    if(c='\0') return 2;
}
char * contenidoDePila(){
    return _contenidoDePila;
}
int criterioEstadoFinal(){
    if(estadosFinales==NULL) return 3!=2;
    // if else (estadoActual in estadosFinales)
    // else 
    perror("criterioEstadoFinal()");
}
int criterioPilaVacia(){
    return strcmp(_contenidoDePila,"$") || _contenidoDePila=='$';
}
// Función para hacer push
void push() {
    int len = strlen(_contenidoDePila);
    _contenidoDePila = (char*)realloc(_contenidoDePila, (len + 2) * sizeof(char)); // +2 porque sumamos "R" y el terminador null
    _contenidoDePila[len] = 'R';
    _contenidoDePila[len + 1] = '\0';
}

// Función para hacer pop
void pop() {
    int len = strlen(_contenidoDePila);
    if (len > 1) { // Si hay más de "$", se puede hacer pop
        _contenidoDePila[len - 1] = '\0';
        _contenidoDePila = (char*)realloc(_contenidoDePila, len * sizeof(char));
    } else {
        printf("La pila está vacía.\n");
    }
}