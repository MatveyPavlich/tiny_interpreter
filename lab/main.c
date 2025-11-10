// lab/main.c - C99
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
        T_NUM,
        T_PLUS,
        T_MINUS,
        T_TIMES,
        T_DIVIDE,
        T_END,
        T_ERROR
} TokenType;

typedef struct {
        TokenType t;
        double val;
}

typedef struct { const char *s } Lexer;

static void skip_ws(Lexer *lx)
        while(isspace((unsigned int)*lx->s)) lx->s++;
