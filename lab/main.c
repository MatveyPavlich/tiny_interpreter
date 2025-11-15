// lab/main.c - C99
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
        ADD_TOKEN,
        SUB_TOKEN,
        DIV_TOKEN,
        MUL_TOKEN,
        END_TOKEN,
        ERR_TOKEN,
        OPRND_TOKEN,
        EXPRESSION_TOKEN
} TokenType;

typedef struct { char s; } Lexer;

typedef struct {
        TokenType t;
        double val;
} Token;
        
// static void sp_skip(Lexer *lx) {
//         while (isspace((unsigned int)*lx->s)) lx->p++;
// }

int main(void) {
        printf("Yo!!\n");
        return 0;
}
