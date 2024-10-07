```sh
    make #compila, genera el ejecutable y corre el ejecutable 
```
```sh
    make clean #elimina ejecutables y archivos "intermedios" 
```
Gramática Léxica
```
<token> -> uno de <identificador> <constante> <palabraReservada>
                    <operadorAditivo> <operadorMultiplicativo> <asignacion> <carácterPuntuación>
<identificador> -> <letra> {<letra o dígito>}
<constante> -> <dígito> {dígito>}
<letra o dígito> -> uno de <letra> <dígito>
<letra> -> una de a-z A-Z
<dígito> -> uno de 0-9
<palabraReservada> -> una de inicio fin leer escribir
<operadorAditivo> -> uno de + -
<operadorMultiplicativo> -> *
<asignación> -> :=
<carácterPuntuación> -> uno de ( ) , ;
```
observaciones:
- el conjunto de NO terminales son los tokens (excepto el primer no terminal)
- el conjunto de terminales son los caracteres que se pueden leer en el lenguaje
- metasimbolos: ->, <, > , {, }, uno de, una de
- si un programa fuente de Micro tiene un caracter que no es terminal, entonces no sera reconocido por el lenguaje generado por esta gramatica

Gramática Sintáctica
```
<programa> -> inicio <listaSentencias> fin
<listaSentencias> -> <sentencia> {<sentencia>}
<sentencia> -> <identificador> := <expresión> ; |
                leer ( <listaIdentificadores> ) ; |
                escribir ( <listaExpresiones> ) ;
<listaIdentificadores> -> <identficador> {, <identficador>}
<listaExpresiones> -> <expresión> {, <expresión>}
<expresión> -> <primaria> {<operadorAditivo> <primaria>}
<primaria> -> <identificador> | <constante> |
                ( <expresión> )
```

observaciones: 
- conjunto NO terminales, son los programas que se usarian en el main y como rutina principales para  reconocer el lenguaje Micro en un archivo fuente de Micro
- conjunto de terminales, son los tokens que se pueden leer en el lenguaje, y los parentesis
conjunto de metasimbolos : ->, <, >, {, }, uno de, una de

### Ejemplo de un programa Micro minimo
```c
inicio
x := 5 + 3;
y := 2+(x-1);
fin
```
```c
inicio
x12 := 5 + 3;
y := 2+(x12-1);
z  := y+x12;
fin
```
:= en realidad es el operador asignacion




PREGUNTAS:
- por que se usan las bibliotecas, que traen cada una de ellas
- en la tabla de simbolos, por que esos elementos , que significa el $ y 99
-  ver las funciones de PAS, separar con las funciones complementarias/auxiliares
- el proposito del programa es ejecutar la funcion objetivo