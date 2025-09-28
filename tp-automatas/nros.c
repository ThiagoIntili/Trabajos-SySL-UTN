#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX_BUFFER 100

// Función inciso 2
int char_a_int(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }

    return -1; 
}

// Inciso 3
int string_a_int(char* expresion) {
    if(!expresion || strlen(expresion) == 0){
        return -1;
    }

    int i = 0;
    int resultado = 0;

    while(expresion[i] != '\0'){
        int digito = char_a_int(expresion[i]);

        if(digito == -1){
            return -1;
        }

        resultado = (resultado * 10) + digito;

        i++;
    }

    return resultado;
}

bool es_operador(char caracter) {
    return (caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/');
}

//funcion para tokenizar la expresión
int tokenizar(char* expresion, int* numeros, char* operadores) {
    int pos_numero = 0;
    int pos_operador = 0;
    int i = 0;
    char numero_actual[MAX_BUFFER]; //buffer que va acumulando cada numero en medio de los operadores
    int pos_buffer = 0;

    while (expresion[i] != '\0') {

        if (isdigit(expresion[i])) {
            numero_actual[pos_buffer] = expresion[i];
            pos_buffer++;
        
        } else if (es_operador(expresion[i])) {

            numero_actual[pos_buffer] = '\0';
            numeros[pos_numero] = string_a_int(numero_actual);

            pos_numero++;
            pos_buffer = 0;
            
            operadores[pos_operador] = expresion[i];
            pos_operador++;
        }
        i++;
    }
    
    numero_actual[pos_buffer] = '\0';
    numeros[pos_numero] = string_a_int(numero_actual);
    pos_numero++;
    
    return pos_numero; 
}

int main()
{
    printf("Hello World");

    return 0;
}