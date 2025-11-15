// main.c  — C99
#define _GNU_SOURCE
#include <unistd.h>
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
        char buf[1024];
        while (1) {
                fputs("clc> ", stdout);
                fgets(buf, sizeof buf, stdin);

        }
        return 0;
}
