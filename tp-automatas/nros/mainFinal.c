#include <stdio.h>      // Para funciones de entrada/salida como printf, fgets, fopen, fclose, perror
#include <stdlib.h>     // Para funciones de utilidad general (no se usa explícitamente, pero es común para exit, malloc, etc.)
#include <ctype.h>      // Para funciones de manejo de caracteres como isdigit, isxdigit
#include <string.h>     // Para funciones de manejo de cadenas como strcpy, strtok, strlen, strcspn
#include <stdbool.h>    // Para usar el tipo de dato bool y los valores true/false

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
    if(c == '-') 
        return 0; 
    if(c == '0') 
        return 1;
    if(isdigit(c))
        return 2;
    if(c == '#') 
        return 3;
    return 4; 
}

int columna(char c) {
    char nums[12] = {'A','B','C','D','E','F','a','b','c','d','e','f'}; 
    if(c == '0') 
        return 0; 
    if(isdigit(c) || es_miembro(c, nums , 12))
        return 2;
    if(c == '#') 
        return 3;
    if(c == 'x' || c == 'X') {
        return 1; 
    }
    return 5; 
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

int esDecimal(const char* token) {
    int countDecimal = 0;
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
    int c = token[i]; // carácter actual
    while(c!='\0') {
        e = ttdec[e][columnaDec(c)]; 
        if(c != '#') 
            agregar_a_palabra(palabra, c);        
        if(e == 0) {
            printf("DECIMAL: %s\n", palabra);
            memset(palabra, 0, sizeof(palabra)); // Reiniciar palabra
            countDecimal++;
        }
        i++; 
        c = token[i]; 
    }
    printf("DECIMALES: %d\n", countDecimal);
    if(e == 0) {
        return 1; // es decimal
    } else if(e == 4) {
        return 2; // es error lexico
    }
    return 0; // no es decimal
}

int esOctal(const char* token) {
    int countOctal = 0;
    char palabra[MAX_LEN] = "";
    static int ttoct[4][4] = {
                        {1,3,3,3},
                        {2,2,3,3},
                        {2,2,0,3},
                        {3,3,3,3},
                        };
    int e = 0; // estado inicial
    int i = 0; // índice del carácter actual
    int c = token[i]; // carácter actual
    while(c!='\0') {
        e = ttoct[e][columnaOctal(c)]; 
        if(c != '#') 
            agregar_a_palabra(palabra, c);        
        if(e == 0) {
            printf("OCTAL: %s\n", palabra);
            memset(palabra, 0, sizeof(palabra)); // Reiniciar palabra
            countOctal++;
        }
        i++; 
        c = token[i]; 
    }
    printf("Octales: %d\n", countOctal);
    if(e == 0) {
        return 1; // es octal
    } else if(e == 3) {
        return 2; // es error lexico
    }
    return 0; // no es octal
}

int esHexadecimal(const char* token) {
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
    char c = token[i]; // carácter actual
    while(c!='\0') {
        e = tthex[e][columna(c)]; 
        if(c != '#') 
            agregar_a_palabra(palabra, c);        
        if(e == 0) {
            printf("HEXADECIMAL: %s\n", palabra);
            memset(palabra, 0, sizeof(palabra)); // Reiniciar palabra
            countHex++;
        }
        i++; 
        c = token[i]; 
    }
    printf("Hexadecimales: %d\n", countHex);
    if(e == 0) {
        return 1; // es hexadecimal
    } else if(e == 5) {
        return 2; // es error lexico
    }
    return 0; // no es hexadecimal
}

void analizarCadena(const char* token) {

    int countDecimal = 0,  countError = 0;
    
    while (token != NULL) {
        if (esDecimal(token) == 2 && esOctal(token) != 1 && esHexadecimal(token) != 1) {
                printf("ERROR LEXICO DECIMAL: %s\n", token);
                countError++;
        } else if (esOctal(token) == 2 && esDecimal(token) != 1 && esHexadecimal(token) != 1) {
                printf("ERROR LEXICO OCTAL: %s\n", token);
                countError++;
        } else if(esHexadecimal(token) == 2 && esDecimal(token) != 1 && esOctal(token) != 1) {
                printf("ERROR LEXICO HEXADECIMAL: %s\n", token);
                countError++;
        } 
        token = strtok(NULL, "#");
    }

    printf("\nResumen:\n");
    printf("Decimales: %d\n", countDecimal);
    printf("Errores: %d\n", countError);
}

typedef struct pila{
      int indice;
      int total;
      char datos[MAX_ELEMENTOS][MAX_LEN];
}Pila;

Pila *crear(){
	Pila *p;
	p=(Pila *)malloc(sizeof(Pila));
	p->indice=0;
	p->total=0;
	return p;
}

int estaVacia(Pila pila){
	if(pila.total==0){
		return 1;
	}else{
		return 0;
	}
}

int estaLlena(Pila pila){
	if(pila.total==MAX_ELEMENTOS){
		return 1;
	}else{
		return 0;
	}
}

int push(Pila *pila, char* dato){ //chau Pila *pila, char dato
	if(pila->total<MAX_ELEMENTOS){
		strcpy(pila->datos[pila->indice], dato);//pila->datos[pila->indice]=dato;
		pila->indice++;
		pila->total++;
		return 1;
	}else{
		return 0;
	}
}

int pop(Pila *pila, char* buffer){
    if (pila->total > 0) {
        strcpy(buffer, pila->datos[pila->indice - 1]);
        pila->indice--;
        pila->total--;
        return 1;
    } else {
        return 0;
    }
}
int nivelDePrecedencia(char* operador){
	if(strcmp(operador, "(") == 0){
	    return 0;
	}
	if(strcmp(operador, "+") == 0 || strcmp(operador, "-") == 0){
	    return 1;
	}

	if(strcmp(operador, "*") == 0 || strcmp(operador, "/") == 0){
	    return 2;
	}
	if(strcmp(operador, "$") == 0){
	    return 3;
	}

    return -1;
}

int tieneMayorOIgualPrioridad(char* operador1, char* operador2){
	int precedenciaPrimerOperador=nivelDePrecedencia(operador1);
	int precedenciaSegundoOperador=nivelDePrecedencia(operador2);
	if(precedenciaPrimerOperador>=precedenciaSegundoOperador){
		return 1;
	}else{
		return 0;
	}
}

int esOperador(char* elemento){
	if(strcmp(elemento, "+") == 0 ||
	   strcmp(elemento, "-") == 0 ||
	   strcmp(elemento, "*") == 0 ||
	   strcmp(elemento, "/") == 0 ||
	   strcmp(elemento, "$") == 0
	   ){
		return 1;
	}else{
		return 0;
	}
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

int esOperando(char* elemento){ //char elemento chau

    if(string_a_int(elemento)!=-1){
        return 1;
    }else{
        return 0;
    }
}

int infijaToPostfija(char infija[][MAX_LEN], int longitud,char postfija[][MAX_LEN]){ //chau: char* infija[]

	char elemento[MAX_LEN],operador[MAX_LEN];
	int j=0;
	int i=0;
	Pila *pila=crear();

	//int longitud= strlen(infija);

	while (i<longitud){
		//elemento = infija[i];
		strcpy(elemento, infija[i]);
		i++;

		if(esOperando(elemento)){
			strcpy(postfija[j], elemento);
			j++;
		}else if (esOperador(elemento)){
			if(!estaVacia(*pila)){
				int seDebeContinuar;
				do{
					int value=pop(pila,operador);//operador=pop(pila);
				    if(tieneMayorOIgualPrioridad(operador, elemento)){
						//postfija[j]=operador;
						strcpy(postfija[j], operador);
						j++;
						seDebeContinuar=1;
					}else{
						seDebeContinuar=0;
						push(pila,operador);
					}
				}while(!estaVacia(*pila) && seDebeContinuar);
			}
			push(pila,elemento);
		}else if (strcmp(elemento,"(") == 0){
			push(pila,elemento);
		}else if (strcmp(elemento,")") == 0){
			int value=pop(pila,operador);
			while(!estaVacia(*pila) && strcmp(operador,"(") != 0) {
				strcpy(postfija[j], operador);
				j++;
				int value=pop(pila,operador);//operador=pop(pila);
			}
		}
	}
	while(!estaVacia(*pila)) {
		int value=pop(pila,operador);//operador=pop(pila);
		strcpy(postfija[j], operador);//postfija[j]=operador;
		//printf("--nroEntre: %s\n",postfija[j]);
		j++;
	}
	//postfija[j]='\0';
    //return postfija;
    free(pila);
    return j;
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

void leer_cadena_numerica(char* cadena) {
    printf("Ingrese una cadena numerica a analizar con numeros separados por #: ");
    scanf("%s", cadena);
}

void leer_nombre_archivo(char* nombreArchivo) {
    printf("Ingrese el nombre del archivo: ");
    scanf("%s", nombreArchivo);
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

void evaluar_expresion(char* expresion){
    NodoPila*pila=NULL;
    NodoPila*pilaInvertida=NULL;
    NodoPila*pilaAux=NULL;

    char* token;
    char resultado[MAX_LEN];
    char tokens[MAX_TOKENS][MAX_LEN],postfija[MAX_TOKENS][MAX_LEN];


    int cantTokens = tokenizar(expresion, tokens);
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
            char* operador2 = popToken(&pilaAux);
            char* operador1 = popToken(&pilaAux);
            operarSegunOperador(token,operador1,operador2,resultado);
            printf("resultado: %s\n",resultado);
            pushToken(&pilaAux,resultado);
            free(operador1);
            free(operador2);
        }
        printf("\n-fin de analisis-\n");
        free(token);
    }
}

int main() {

    char expresion[MAX_BUFFER];
    int opcion;
    
    printf("TP AUTOMATAS - SINTAXIS Y SEMANTICA DE LOS LENGUAJES\n\n");
    printf("Seleccione una opcion:\n");
    printf("1. Analizar cadena con numeros\n");
    printf("2. Evaluar expresion aritmetica dada por terminal\n");
    printf("3. Evaluar expresion aritmetica dada por archivo\n");
    printf("4. Salir\n");
    printf("\nOpcion: ");
    scanf("%d", &opcion);
    
    switch(opcion) {
        case 1: {
            char cadena[MAX_LINE];
            leer_cadena_numerica(cadena);
            analizarCadena(cadena);
            break;
        }
        case 2:
            leer_expresion(expresion);
            evaluar_expresion(expresion);
            break;
        case 3:
            /* char nombreArchivo[MAX_BUFFER];
            leer_nombre_archivo(nombreArchivo);
            leer_expresion_archivo(expresion, nombreArchivo);
            evaluar_expresion(expresion);
            break;
            */ 
        case 4:
            printf("\nSaliendo...\n");
            break;
        default:
            printf("\nOpción inválida\n");
    }

    return 0;
}
