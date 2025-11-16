// main.c  — C99
// interpreter to evaluate single digit integer expressions 

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

typedef struct { const char *s; } Lexer;

typedef struct {
        TokenType t;
        int val;
} Token;
        
static void sp_skip(Lexer *lx) {
        while (isspace((unsigned int)*lx->s)) lx->s++;
}

static Token generate_token(Lexer *lx) {
        sp_skip(lx);
        
        char c = *lx->s;
        if (c == '\0')
                return (Token){.t = END_TOKEN, .val = 0};
        if (isdigit((unsigned char)c)) {
                int v = atoi(c);
                return (Token){.t = OPRND_TOKEN, .val = v};
        }

}

int main(void) {
        char buf[1024];

        while (1) {
                fputs("clc> ", stdout);
                // fflush(stdout);
                // redundant since read-before-write synchronisation

                if (!fgets(buf, sizeof buf, stdin))
                        break;

                buf[strcspn(buf, "\n")] = '\0';
                if (buf[0] == '\0')
                        continue;
                Lexer l = {.s = buf};
                sp_skip(&l);

                printf("saved: \"%s\"\n", l.s);
                // printf("saved: \"%s\"\n", buf);
        }

        return 0;
}
