#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX_BUFFER 100
#define MAX_TOKENS 100
#define MAX_LEN 50
// Funcion inciso 1 

#define MAX_LINE 1024

int esDecimal(const char* token);
int esOctal(const char* token);
int esHexadecimal(const char* token);
void analizarCadena(const char* input);

void analizarCadena(const char* input) {
    char copia[MAX_LINE];
    strcpy(copia, input);
    char *token = strtok(copia, "#");

    int countDecimal = 0, countOctal = 0, countHex = 0, countError = 0;

    while (token != NULL) {
        if (esHexadecimal(token)) {
            printf("HEX: %s\n", token);
            countHex++;
        } else if (esOctal(token)) {
            printf("OCT: %s\n", token);
            countOctal++;
        } else if (esDecimal(token)) {
            printf("DEC: %s\n", token);
            countDecimal++;
        } else {
            printf("ERROR: %s\n", token);
            countError++;
        }

        token = strtok(NULL, "#");
    }

    printf("\nResumen:\n");
    printf("Decimales: %d\n", countDecimal);
    printf("Octales: %d\n", countOctal);
    printf("Hexadecimales: %d\n", countHex);
    printf("Errores: %d\n", countError);
}

int esDecimal(const char* token) {
    int i = 0;
    if (token[i] == '+' || token[i] == '-') i++;
    if (!isdigit(token[i])) return 0;
    while (isdigit(token[i])) i++;
    return token[i] == '\0';
}

int esOctal(const char* token) {
    if (token[0] != '0') return 0;
    for (int i = 1; token[i] != '\0'; i++) {
        if (token[i] < '0' || token[i] > '7') return 0;
    }
    return 1;
}

int esHexadecimal(const char* token) {
    if (!(token[0] == '0' && (token[1] == 'x' || token[1] == 'X')))
        return 0;
    if (token[2] == '\0') return 0; // debe tener al menos un dígito después de 0x

    for (int i = 2; token[i] != '\0'; i++) {
        if (!isxdigit(token[i])) return 0;
    }
    return 1;
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

int main(int argc, char *argv[]) {
    char expresion[] = "-12+34*5-2";
    char tokens[MAX_TOKENS][MAX_LEN];

    int cantidad = tokenizar(expresion, tokens);

    printf("Tokens:\n");
    for (int i = 0; i < cantidad; i++) {
        printf("%s\n", tokens[i]);
    } 


    // inciso 1 
    // necesito hacer q main pueda recibir parametros 

    char linea[MAX_LINE];

    if (argc == 2) {
        // Leer desde archivo
        FILE *archivo = fopen(argv[1], "r");
        if (!archivo) {
            perror("Error al abrir archivo");
            return 1;
        }
        while (fgets(linea, sizeof(linea), archivo)) {
            analizarCadena(linea);
        }
        fclose(archivo);
    } else {
        // Leer desde línea de comandos
        printf("Ingrese la cadena: ");
        if (fgets(linea, sizeof(linea), stdin) != NULL) {
        linea[strcspn(linea, "\n")] = '\0';  // elimina el salto de línea
        analizarCadena(linea);
        }
    }

    return 0;
}