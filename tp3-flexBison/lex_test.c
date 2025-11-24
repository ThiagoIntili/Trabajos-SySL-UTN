#include <stdio.h>

extern int yylex(void);
extern char *yytext;

/* Definiciones dummy para enlazar lex.yy.c sin el parser */
int yylval;
int yywrap(void) { return 1; }

int main(void) {
    int tok;
    while ((tok = yylex()) != 0) {
        printf("TOKEN=%d TEXT=\"%s\"\n", tok, yytext ? yytext : "");
    }
    return 0;
}
