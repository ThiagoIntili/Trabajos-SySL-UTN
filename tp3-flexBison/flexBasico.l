%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "y.tab.h"
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
{IDENTIFICADOR} {return ID;}
";" {return PYCOMA;}
"(" {return PARENIZQUIERDO;}
")" {return PARENDERECHO;}
"+" {return SUMA;}
"-" {return RESTA;}
"inicio" {return INICIO}
"fin" {return FIN}
"leer" {return LEER}
"escribir" {return ESCRIBIR}
[ \t\r\n]+    { /* ignorar espacios en blanco */ }
. { fprintf(stderr, "mi error es error lexico '%s'\n", yytext); exit(1); }
%%
