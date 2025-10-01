#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "infijaToPostfija.c"

#define MAX_BUFFER 100
#define MAX_TOKENS 100
#define MAX_LEN 50


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
int tokenizar(const char* expresion, char tokens[MAX_TOKENS][MAX_LEN]) {
    int i = 0;
    int num_tokens = 0;

    while (expresion[i] != '\0') {

        if (isdigit(expresion[i]) || (expresion[i] == '-' && i == 0)) {
            int j = 0;

            if(expresion[i] == '-') {
                tokens[num_tokens][j] = expresion[i];
                j++;
                i++;
            }

            while (isdigit(expresion[i])) {
                tokens[num_tokens][j] = expresion[i];
                j++;
                i++;
            }
            tokens[num_tokens][j] = '\0';
            num_tokens++;
        }

        else if (es_operador(expresion[i])){
            tokens[num_tokens][0] = expresion[i];
            tokens[num_tokens][1] = '\0';
            num_tokens++;
            i++;
        }
            else {
                i++;
            }
    }

    return num_tokens; // cantidad de tokens
}

int main() {
    char expresion[MAX_BUFFER];
    printf("Ingrese una expresión aritmetica: ");
    scanf("%s",expresion);

    char tokens[MAX_TOKENS][MAX_LEN],postfija[MAX_TOKENS][MAX_LEN];
    int cantidad = tokenizar(expresion, tokens);

    printf("Tokenizado: ");
    for (int i = 0; i < cantidad; i++) {
        printf("%s ", tokens[i]);
    }
    printf("\n");


	int Lpostfija=infijaToPostfija(tokens,cantidad,postfija);
	printf("Notacion polaca inversa: ");
	for (int k = 0; k < Lpostfija; k++) {
        printf("%s ", postfija[k]);
    }


    return 0;
}
