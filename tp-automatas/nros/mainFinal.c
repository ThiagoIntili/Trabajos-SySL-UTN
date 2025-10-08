#include <stdio.h>      // Para funciones de entrada/salida como printf, fgets, fopen, fclose, perror
#include <stdlib.h>     // Para funciones de utilidad general (no se usa explícitamente, pero es común para exit, malloc, etc.)
#include <ctype.h>      // Para funciones de manejo de caracteres como isdigit, isxdigit
#include <string.h>     // Para funciones de manejo de cadenas como strcpy, strtok, strlen, strcspn
#include "infijaToPostfija.c"

#define MAX_BUFFER 100
#define MAX_TOKENS 100
#define MAX_LEN 50
#define MAX_ELEMENTOS 10
#define MAX_LINE 1024

// codigo punto 1

int es_miembro(char elemento, char lista[], int tamano) {
    for (int i = 0; i < tamano; i++) {
        if (lista[i] == elemento) {
            return 1; // Elemento encontrado
        }
    }
    return 0; // Elemento no encontrado
}

void agregar_a_palabra(char* palabra, char c) {
    int len = strlen(palabra);
    palabra[len] = c;
}

int columnaDec(char c) {
    if(c=='#')
        return 3;

    if(c == '-')
        return 0;

    if(c == '0')
        return 1;

    if(isdigit(c))
        return 2;
    return 4;
}


int columna(char c) {
    char nums[12] = {'A','B','C','D','E','F'};
    if(c == '0')
        return 0;
    if(isdigit(c) || es_miembro(c, nums , 12))
        return 2;
    if(c == '#')
    return 3;
    if(c == 'x') {
        return 1;
    } else
        return 4;
}

int columnaOctal(char c) {
    char nums[7] = {'1','2','3','4','5','6','7'};
    if(c == '0')
    return 0;
    if(es_miembro(c, nums , 7))
    return 1;
    if(c == '#')
    return 2;
    return 3;
}

int esDecimal(char* cadena) {
    char palabra[MAX_LEN] = "";
    static int ttdec[5][5] = {
                        {3,2,1,4,4},
                        {4,1,1,0,4},
                        {4,4,4,0,4},
                        {4,4,1,4,4},
                        {4,4,4,4,4}
                        };
    int e = 0; // estado inicial
    int i = 0; // índice del carácter actual
    int c = cadena[i]; // carácter actual

    while(c!='\0') {

        e = ttdec[e][columnaDec(c)];
        if(c != '#')
            agregar_a_palabra(palabra, c);
        if(e == 0) {
            printf("Decimal: %s\n", palabra);
            return 1; // es decimal
        } else if (e == 4) {
            return 2; // es error lexico
        }
        i++;
        c = cadena[i];
    }
}

int esOctal(char* cadena) {
    char palabra[MAX_LEN] = "";
    static int ttoct[4][4] = {
                        {1,3,3,3},
                        {2,2,3,3},
                        {2,2,0,3},
                        {3,3,3,3},
                        };
    int e = 0; // estado inicial
    int i = 0; // índice del carácter actual
    int c = cadena[i]; // carácter actual
    while(c!='\0') {
        e = ttoct[e][columnaOctal(c)];
        if(c != '#')
            agregar_a_palabra(palabra, c);
        if(e == 0) {
            printf("Octal: %s\n", palabra);
            return 1; // es octal
        } else if (e == 3) {
            return 2; // es error lexico
        }
        i++;
        c = cadena[i];
    }
}

int esHexadecimal(char* cadena) {
    char palabra[MAX_LEN] = "";
    int countHex = 0;
    static int tthex[6][6] = {
                        {1,5,5,5,5},
                        {5,2,5,5,5},
                        {3,5,3,5,5},
                        {3,5,3,0,5},
                        {5,5,3,5,5},
                        {5,5,5,5,5}
                        };
    int e = 0; // estado inicial
    int i = 0; // índice del carácter actual
    char c = cadena[i]; // carácter actual
    while(c!='\0') {
        e = tthex[e][columna(c)];
        if(c != '#')
            agregar_a_palabra(palabra, c);
        if(e == 0) {
            printf("Hexadecimal: %s\n", palabra);
            return 1; // es hexadecimal
        } else if (e == 5) {
            return 2; // es error lexico
        }
        i++;
        c = cadena[i];
    }
}

void analizarCadena(char* cadena) {
    int countDecimal = 0, countOctal = 0, countHex = 0, countError = 0;
    char copia[MAX_LINE];
    strcpy(copia, cadena);

    char* token = strtok(copia, "#");
    token[strlen(token)] = '#';
    while (token != NULL) {
        if (esDecimal(token) == 1) {
            countDecimal++;
        } else if (esOctal(token) == 1) {
            countOctal++;
        } else if (esHexadecimal(token) == 1) {
            countHex++;
        } else if (esDecimal(token) == 2 || esOctal(token) == 2 || esHexadecimal(token) == 2) {
            countError++;
        }
        token = strtok(NULL, "#");
        if(token != NULL)
            token[strlen(token)] = '#';
    }

    printf("\nResumen:\n");
    printf("Octales: %d\n", countOctal);
    printf("Decimales: %d\n", countDecimal);
    printf("Hexadecimales: %d\n", countHex);
    printf("Errores: %d\n", countError);
}

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

int es_operador(char caracter) {
    if((caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/')){
        return 1;
    }
    return 0;
}

//funcion para tokenizar la expresión
int esHexadigito(char c){
    return ((c>='A' && c<='F') || isdigit(c));
}
int tokenizar(const char* expresion, char tokens[MAX_TOKENS][MAX_LEN]) {
    int i = 0;
    int num_tokens = 0;

    while (expresion[i] != '\0') {
        int j = 0;
        if(expresion[i]=='0' && expresion[i+1]=='x'){
            tokens[num_tokens][j++]=expresion[i++]; //para 0
            tokens[num_tokens][j++]=expresion[i++]; //para x
            while(esHexadigito(expresion[i])){
                tokens[num_tokens][j++] = expresion[i++];
            }
            tokens[num_tokens][j] = '\0';
            num_tokens++;
        }else if (isdigit(expresion[i]) || (expresion[i] == '-' && i == 0)) {


            if(expresion[i] == '-') {
                tokens[num_tokens][j++] = expresion[i++];
            }

            while (isdigit(expresion[i])) {
                tokens[num_tokens][j++] = expresion[i++];
            }
            tokens[num_tokens][j] = '\0';
            num_tokens++;
        }

        else if (es_operador(expresion[i])==1){
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
    nodoNuevo->token=strdup(token);
    nodoNuevo->sig=*pila;
    *pila = nodoNuevo;
}

char* popToken(NodoPila** pila_){
    if (*pila_ == NULL) return NULL;

    NodoPila* aux=*pila_;
    char* token=aux->token;

    *pila_=aux->sig;
    free(aux);//libera memoria
    return token;
}

void leer_expresion(char* expresion) {
    printf("Ingrese una expresión aritmética: ");
    scanf("%s", expresion);
}

void leer_cadena_numerica(char* cadena) {
    printf("Ingrese una cadena numerica a analizar con numeros separados por #: ");
    scanf("%s", cadena);
}

void leer_nombre_archivo(char* nombreArchivo) {
    printf("Ingrese nuevo nombre del archivo: ");
    scanf("%s", nombreArchivo);
}

int crear_archivo(char* nombreArchivo,char* expresion){
    FILE* archivo;
    archivo=fopen(nombreArchivo,"w");
    fprintf(archivo,"%s",expresion);
    printf("(Archivo %s creado)\n",nombreArchivo);
    fclose(archivo);
    return 1;
}
int leer_expresion_archivo(char* expresion, char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "r");

    if (!archivo) {
        printf("Error: No se pudo abrir el archivo '%s'\n", nombreArchivo);
        return 0;
    }

    if (!fgets(expresion, MAX_BUFFER-1, archivo)) {
        printf("Error: No se pudo leer del archivo\n");
        fclose(archivo);
        return 0;
    }else{
        printf("(Leyendo expresion del archivo %s...)\n\n",nombreArchivo);
    }
    fclose(archivo);
    return 1;
}

void operarSegunOperador(char* operador,char* operando1, char* operando2, char resultadoAlfa[MAX_LEN]){
    printf("operador: %s\n",operador);
    printf("operando1: %s\n",operando1);
    printf("operando2: %s\n",operando2);
    int resultado=0;
    if(operador[0]=='+'){
        resultado=string_a_int(operando1)+string_a_int(operando2);
    }
    if(operador[0]=='*'){
        resultado=string_a_int(operando1)*string_a_int(operando2);
    }
    if(operador[0]=='/'){
        resultado=string_a_int(operando1)/string_a_int(operando2);
    }
    if(operador[0]=='-'){
        resultado=string_a_int(operando1)-string_a_int(operando2);
    }
    sprintf(resultadoAlfa, "%d", resultado); //convertir en char

}

char* operarPolacaInversa(int cantTokens,char tokens[MAX_TOKENS][MAX_LEN]){
    char postfija[MAX_TOKENS][MAX_LEN];
    NodoPila*pila=NULL;
    NodoPila*pilaInvertida=NULL;
    NodoPila*pilaAux=NULL;
    char* token;
    static char resultado[MAX_LEN];

    infijaToPostfija(tokens,cantTokens,postfija); //Lpostfija es lo mismo que cantTokens

	//printf("Notacion polaca inversa (push pila): ");
	//ponemos del ultimo elemento al inicial en la pila
	for (int k = cantTokens; k >=0; k--) {
        pushToken(&pila,postfija[k]);
    }
    //printf("\nEvaluando cada componente:\n");
    //evaluamos cada componente y segun el operadora, operamos aritmeticamente
    for (int k = 0; k < cantTokens; k++) {
        token=popToken(&pila);
        if(esOperador(token)==0){
            pushToken(&pilaAux,token);
        }else{
            operarSegunOperador(token,popToken(&pilaAux),popToken(&pilaAux),resultado);
            pushToken(&pilaAux,resultado);
        }
    }

    return resultado;
}
void operar_expresion(char* expresion){
    //falta funcion evaluar expresion: que sea solo deciamles
    char tokens[MAX_TOKENS][MAX_LEN];
    int cantTokens=0;
    cantTokens = tokenizar(expresion, tokens);

    printf("Resultado: %s",operarPolacaInversa(cantTokens,tokens));

}

int evaluar_expresion(char* expresion){
    char tokens[MAX_TOKENS][MAX_LEN];
    int cantTokens=0,i=0;
    cantTokens = tokenizar(expresion, tokens);
    for(i;i<cantTokens;i++){
        if(esOperador(tokens[i])==0){
            strcat(tokens[i],"#");
            if(esDecimal(tokens[i])!=1){
                return 0;
            }
        }
    }
    return 1;
}

int main() {

    char expresion[MAX_BUFFER];
    char expresion_evaluada[MAX_BUFFER];
    char nombreArchivo[MAX_BUFFER];
    int opcion;

    printf("TP AUTOMATAS - SINTAXIS Y SEMANTICA DE LOS LENGUAJES\n\n");
    printf("Seleccione una opcion:\n");
    printf("1. Analizar cadena con numeros\n");
    printf("2. Analizar cadena con numeros a traves de archivo\n");
    printf("3. Evaluar expresion aritmetica dada por terminal\n");
    printf("4. Evaluar expresion aritmetica ingresada por archivo\n");
    printf("5. Salir\n");
    printf("\nOpcion: ");
    scanf("%d", &opcion);

    switch(opcion) {
        case 1: {
            char cadena[MAX_LINE];
            leer_cadena_numerica(cadena);
            analizarCadena(cadena);
            break;
        }
        case 2: {
            char cadena[MAX_LINE];
            leer_nombre_archivo(nombreArchivo);
            leer_cadena_numerica(cadena);
            crear_archivo(nombreArchivo,cadena);
            leer_expresion_archivo(expresion, nombreArchivo);
            analizarCadena(cadena);
            break;
        }
        case 3:
            leer_expresion(expresion);
            strcpy(expresion_evaluada,expresion); //evaluamos, como la función modifica la expresion la evaluamos en un auxiliar
            if(evaluar_expresion(expresion_evaluada)==1){
                operar_expresion(expresion);
            }else{
                printf("La expresión ingresada no posee decimales");
            }

            break;
        case 4:
            leer_nombre_archivo(nombreArchivo);
            leer_expresion(expresion);
            crear_archivo(nombreArchivo,expresion);
            leer_expresion_archivo(expresion, nombreArchivo);

            strcpy(expresion_evaluada,expresion); //evaluamos, como la función modifica la expresion la evaluamos en un auxiliar
            if(evaluar_expresion(expresion_evaluada)==1){
                operar_expresion(expresion);
            }else{
                printf("La expresión ingresada no posee decimales");
            }
            break;
        case 5:
            printf("\nSaliendo...\n");
            break;
        default:
            printf("\nOpción inválida\n");
    }

    return 0;
}
