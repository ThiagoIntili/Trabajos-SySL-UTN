#include <stdio.h>
#include <stdlib.h>

/* Declaración del parser generado por Bison */
int yyparse(void);

int main(void)
{
    int ret = yyparse();
}