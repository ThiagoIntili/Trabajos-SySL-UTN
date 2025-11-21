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
%}
%union{
   char* cadena;
   int num;
} 
%token ASIGNACION PYCOMA SUMA RESTA PARENIZQUIERDO PARENDERECHO
%token <cadena> ID
%token <num> CONSTANTE
%%
sentencias: sentencias sentencia 
|sentencia 
;
sentencia: ID { printf("el id es: %s de longitud: %d ", $1, yyleng); if (yyleng>10) yyerror("metiste la pata"); /* declarar/insertar variable en tabla (detecta redeclaracion) */ detectar_redeclaracion($1); free($1); } ASIGNACION expresion PYCOMA
;
expresion: primaria 
|expresion operadorAditivo primaria 
; 
primaria: ID { /* uso de variable en expresion: verificar declaracion previa */ detectar_uso_no_declarado($1); free($1); }
| CONSTANTE { printf("valores %d ", $1); }
| PARENIZQUIERDO expresion PARENDERECHO
;
operadorAditivo: SUMA 
| RESTA
;
%%
void yyerror (char *s){
printf ("mi error es %s\n",s);
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