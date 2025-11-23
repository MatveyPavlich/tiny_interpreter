#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "lexer.h"

static void sp_skip(Lexer *lx) {
        while (isspace((unsigned int)*lx->s)) lx->s++;
}

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

// static int tokenise(Lexer *lx, Token out[], int max) {
int tokenise(Lexer *lx, Token out[], int max) {
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

// static int interpret() {
//         return 0;
// }
