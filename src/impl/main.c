// main.c  — C99
// interpreter to evaluate single digit integer expressions 

#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPR_LEN 100

typedef enum {
        T_NUM,
        T_PLUS,
        T_MINUS,
        T_STAR,
        T_SLASH,
        T_LPAREN,
        T_RPAREN,
        T_END,
        T_ERR
} TokenType;

typedef struct { const char *s; } Lexer;

typedef struct {
        TokenType t;
        int val;
} Token;
        
static void sp_skip(Lexer *lx) {
        while (isspace((unsigned int)*lx->s)) lx->s++;
}
// static void sk_space(Lexer *lx)
//         return if (is_space((unsigned char)lx->s) == 0) lx->s++;


static Token generate_token(Lexer *lx) {
        sp_skip(lx);

        char c = *lx->s;
        if (c == '\0')
                return (Token){ T_END, 0 };

        if (isdigit((unsigned char)c)) {
                int v = c - '0';  
                lx->s++; 
                return (Token){ T_NUM, v };
        }

        lx->s++;

        switch (c) {
                case '+': return (Token){ T_PLUS,   0 };
                case '-': return (Token){ T_MINUS,  0 };
                case '*': return (Token){ T_STAR,   0 };
                case '/': return (Token){ T_SLASH,  0 };
                case '(': return (Token){ T_LPAREN, 0 };
                case ')': return (Token){ T_RPAREN, 0 };
                default:  return (Token){ T_ERR,    0 };
        }
}

static int tokenise(Lexer *lx, Token out[], int max) {
        int count = 0;

        while (count < max) {
                Token t = generate_token(lx);
                out[count++] = t;

                if (t.t == T_ERR) {
                        printf("error: invalid token\n");
                        return count;
                }
                if (t.t == T_END) {
                        printf("end reached\n");
                        return count;
                }
        }

        printf("error: too many tokens\n");
        return count;
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

                Token tokens[MAX_EXPR_LEN];
                int n = tokenise(&l, tokens, MAX_EXPR_LEN);

                printf("tokens: ");
                for (int i = 0; i < n; i++) {
                        printf("[%d:%d] ", tokens[i].t, tokens[i].val);
                }
                printf("\n");

                printf("saved: \"%s\"\n", l.s);
        }

        return 0;
}

/*
// Trial rewrite from memory
int main(void) {
        fputs("calc >", stdout);
        fflush(stdout) // not must since will be flushed anyway
        
        char buffer[1024];
        if (fgets(buffer, sizeof(buffer), stdin) break;
}
*/
