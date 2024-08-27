#include "scanner.h"
#include "parser.h"
/***************************Programa Principal************************/
int main(int argc, char *argv[])
{
    TOKEN tok;
    char nomArchi[TAMNOM];
    int l;

    /***************************Se abre el Archivo Fuente******************/
    if (argc == 1)
    {
        printf("Debe ingresar el nombre del archivo fuente (en lenguaje Micro) en la linea de comandos\n");
        return -1;
    }
    if (argc != 2)
    {
        printf("Numero incorrecto de argumentos\n");
        return -1;
    }
    strcpy(nomArchi, argv[1]);
    l = strlen(nomArchi);
    if (l > TAMNOM)
    {
        printf("Nombre incorrecto del Archivo Fuente\n");
        return -1;
    }
    if (nomArchi[l - 1] != 'm' || nomArchi[l - 2] != '.')
    {
        printf("Nombre incorrecto del Archivo Fuente\n");
        return -1;
    }

    if ((in = fopen(nomArchi, "r")) == NULL)
    {
        printf("No se pudo abrir archivo fuente\n");
        return -1;
    }

    /*************************Inicio Compilacion***************************/

    Objetivo();

    /**************************Se cierra el Archivo Fuente******************/

    fclose(in);

    return 0;
}
