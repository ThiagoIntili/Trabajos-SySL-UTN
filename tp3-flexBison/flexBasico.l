%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "bisonBasico.tab.h"
	#include <string.h>

	char *strdup(const char *s);
%}
DIGITO [0-9]
LETRA [a-zA-Z]
SUMA \+
RESTA \-
COMA ,
PYCOMA ;
PARENIZQUIERDO \(
PARENDERECHO \)

ASIGNACION :=
IDENTIFICADOR {LETRA}({LETRA}|{DIGITO})*
CONSTANTE {DIGITO}({DIGITO})*
%%
":=" {return ASIGNACION;}
{CONSTANTE} {yylval.num=atoi(yytext);return CONSTANTE;}
"inicio" {return INICIO;}
"fin" {return FIN;}
"leer" {return LEER;}
"escribir" {return ESCRIBIR;}
";" {return PYCOMA;}
"(" {return PARENIZQUIERDO;}
")" {return PARENDERECHO;}
"+" {return SUMA;}
"-" {return RESTA;}
"," {return COMA;}
{IDENTIFICADOR} {yylval.cadena = strdup(yytext);return ID;}
[\n\t\r]+    {; /* ignorar espacios en blanco */ }
. { fprintf(stderr, "mi error es error lexico '%s'\n", yytext); exit(1); }
%%
