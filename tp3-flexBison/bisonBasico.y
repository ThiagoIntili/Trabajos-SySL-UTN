%{
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
extern char *yytext;
extern int yyleng;
extern int yylex(void);
extern void yyerror(char*);
/* Prototipos de rutinas semánticas */
int detectar_redeclaracion(const char *id);
int detectar_uso_no_declarado(const char *id);
int variable=0;
int resultado=0;
int erroresSintacticos=0;
%}
%union{
   char* cadena;
   int num;
} 
%token INICIO FIN LEER ESCRIBIR COMA
%token ASIGNACION PYCOMA SUMA RESTA PARENIZQUIERDO PARENDERECHO
%token <cadena> ID
%token <num> CONSTANTE
%type <num> expresion operadorAditivo primaria
%%
programa: INICIO sentencias FIN
sentencias: sentencias sentencia 
|sentencia 
;

sentencia: ID { printf("el id es: %s\nde longitud: %d\n", $1, yyleng); if (yyleng>10) yyerror("metiste la pata"); /* declarar/insertar variable en tabla (detecta redeclaracion) */ detectar_redeclaracion($1); free($1); } ASIGNACION expresion PYCOMA 
|LEER PARENIZQUIERDO identificadores PARENDERECHO PYCOMA {printf("Leido con exito")}
|ESCRIBIR PARENIZQUIERDO expresiones PARENDERECHO PYCOMA {printf("Escrito con exito")}
;

identificadores: identificadores ID
|COMA ID
;

expresiones: expresion
;

expresion: primaria 
|expresion operadorAditivo primaria {
	if($2=='+'){
		resultado=$1+$3;
	}else{
		resultado=$1+$3;
	}
}
; 
primaria: ID { /* uso de variable en expresion: verificar declaracion previa */ 
	if(detectar_uso_no_declarado($1)==0){
		$$=atoi($1); /*lo convierte a nro para sumas*/
	};free($1); }
|CONSTANTE { printf("valores %d\n\n", $1);$$=$1 }
|PARENIZQUIERDO expresion PARENDERECHO {$$=$2}
;
operadorAditivo: SUMA { $$ = '+'; }
|RESTA { $$ = '-'; }
;

%%
void yyerror (char *s){
	erroresSintacticos++;
	printf ("mi error Es %s\n",s);
}
int yywrap()  {
  return 1;  
} 

/* Rutinas semánticas */
#include <string.h>

#define MAX_SYM_C 256
static char *symbol_table_c[MAX_SYM_C];
static int symbol_count_c = 0;

/*
 * detectar_redeclaracion: devuelve
 *  0 si la inserción fue exitosa (no estaba declarada),
 *  1 si ya estaba declarada (redeclaración detectada),
 * -1 en error (tabla llena o malloc falla)
 */
int detectar_redeclaracion(const char *id) {
    if (id == NULL) return -1;
    for (int i = 0; i < symbol_count_c; ++i) {
        if (strcmp(symbol_table_c[i], id) == 0) {
            /* redeclaración */
            yyerror("error semantico, hiciste una redeclaracion");
            return 1;
        }
    }
    if (symbol_count_c >= MAX_SYM_C) {
        yyerror("tabla de simbolos llena (C)");
        return -1;
    }
    symbol_table_c[symbol_count_c] = strdup(id);
    if (symbol_table_c[symbol_count_c] == NULL) {
        yyerror("memoria insuficiente para símbolo (C)");
        return -1;
    }
    symbol_count_c++;
    return 0;
}

/*
 * detectar_uso_no_declarado: devuelve
 *  0 si la variable fue encontrada (está declarada),
 *  1 si no está declarada (error semántico)
 */
int detectar_uso_no_declarado(const char *id) {
    if (id == NULL) return 1;
    for (int i = 0; i < symbol_count_c; ++i) {
        if (strcmp(symbol_table_c[i], id) == 0) return 0; 
    }
    printf("la variable %s no ha sido declarada ", id);
    yyerror("error semantico");
    return 1;
}
int main(){
	int ret = yyparse();
    printf("Se encontraron %d errores sintácticos\n", erroresSintacticos);
    return ret;
}
