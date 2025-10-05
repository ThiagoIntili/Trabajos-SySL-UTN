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

typedef struct nodoPila{
    char* token;
    struct nodoPila* sig;
}NodoPila;

void destruirNodo(NodoPila* nodo){
    nodo->sig=NULL;
    free(nodo);
}

void pushToken(NodoPila** pila, char* token){
    NodoPila* nodoNuevo = (NodoPila*)malloc(sizeof(NodoPila));
    nodoNuevo->token=token;
    nodoNuevo->sig=*pila;
    *pila = nodoNuevo;
}

char* popToken(NodoPila** pila_){
    if (*pila_ == NULL) return NULL;
    char* token;
    token=(*pila_)->token;
    NodoPila* aux=*pila_;

    *pila_=aux->sig;
    free(aux);//libera memoria
    return token;
}

void operarSegunOperador(char* operador,char* operando1, char* operando2, char resultadoAlfa[MAX_LEN]){
    printf("operador: %s\n",operador);
    printf("operando1: %s\n",operando1);
    printf("operando2: %s\n",operando2);
    
    int operador1 = string_a_int(operando1);
    int operador2 = string_a_int(operando2);
    int resultado=0;

    switch(operador[0]) {
        case '+': 
            resultado = operador1 + operador2; 
            break;
        case '-': 
            resultado = operador1 - operador2; 
            break;
        case '*': 
            resultado = operador1 * operador2; 
            break;
        case '/': 
            resultado = (operador2 != 0) ? operador1 / operador2 : 0; 
            break;
    }

    sprintf(resultadoAlfa, "%d", resultado); //convertir en char
}

void leer_expresion(char* expresion) {
    printf("Ingrese una expresión aritmética: ");
    scanf("%s", expresion);
}

void mostrar_tokens(char tokens[MAX_TOKENS][MAX_LEN], int cantidad) {
    printf("\nTokens:\n");
    for (int i = 0; i < cantidad; i++) {
        printf("%s ", tokens[i]);
    }
    printf("\n");
}

void mostrar_postfija(char postfija[MAX_TOKENS][MAX_LEN], int cantidad) {
    printf("\nNotación postfija:\n");
    for (int i = 0; i < cantidad; i++) {
        printf("%s ", postfija[i]);
    }
    printf("\n");
}

int leer_expresion_archivo(char* expresion, char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "r");
    
    if (!archivo) {
        printf("Error: No se pudo abrir el archivo '%s'\n", nombreArchivo);
        return 0;  
    }
    
    if (!fgets(expresion, MAX_BUFFER, archivo)) {
        printf("Error: No se pudo leer del archivo\n");
        fclose(archivo);
        return 0;
    }
    
    fclose(archivo);
    return 1;
}


int main() {
    NodoPila*pila=NULL;
    NodoPila*pilaInvertida=NULL;
    NodoPila*pilaAux=NULL;
    char* token;
    char resultado[MAX_LEN];

    char expresion[MAX_BUFFER];
    char tokens[MAX_TOKENS][MAX_LEN],postfija[MAX_TOKENS][MAX_LEN];
    int cantTokens=0;

    leer_expresion(expresion);    

    cantTokens = tokenizar(expresion, tokens);
    mostrar_tokens(tokens, cantTokens);


	int Lpostfija=infijaToPostfija(tokens,cantTokens,postfija); //Lpostfija es lo mismo que cantTokens
	printf("Notacion polaca inversa (push pila): ");
	for (int k = 0; k < Lpostfija; k++) {
        printf("%s ", postfija[k]);
        pushToken(&pila,postfija[k]);
    }

    printf("\n\nPilaInvertida: ");
	for (int k = 0; k < Lpostfija; k++) {
        token=popToken(&pila);
        printf("%s ", token);
        pushToken(&pilaInvertida,token);
    }

    printf("\nEvaluando cada componente:\n");
    for (int k = 0; k < Lpostfija; k++) {

        token=popToken(&pilaInvertida);
        printf("Elemento de la pilaInvertida: %s\n",token);
        if(!esOperador(token)){
            printf("A poner pilaAux: ");
            pushToken(&pilaAux,token);
            printf("%s", token);
        }else{
            operarSegunOperador(token,popToken(&pilaAux),popToken(&pilaAux),resultado);
            printf("resultado: %s\n",resultado);
            pushToken(&pilaAux,resultado);
        }
        printf("\n-fin de analisis-\n");

    }

    return 0;
}
