#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"

#define MAX_EXPR_LEN 100

static void sp_skip(Buffer *bf) {
        while (isspace((unsigned int)*bf->s)) bf->s++;
}

static Token generate_token(Buffer *bf) {
        sp_skip(bf);

        char c = *bf->s;
        if (c == '\0')
                return (Token){ T_END, 0 };

        if (isdigit((unsigned char)c)) {
                int v = c - '0';  
                bf->s++; 
                return (Token){ T_NUM, v };
        }

        bf->s++;

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

static Lexer* tokenise(Buffer *bf) {
        Lexer *lx = malloc(sizeof(Lexer));
        if (lx == 0) {
                printf("malloc failed on the Lexer allocation\n");
                return 0;
        }

        lx->token_count = 0;
        lx->buf = bf->s;

        while (lx->token_count < MAX_EXPR_LEN) {
                Token t = generate_token(bf);
                lx->tokens[lx->token_count++] = t; // increments count as well

                if (t.t == T_ERR) {
                        printf("error: invalid token\n");
                        return lx;
                }
                if (t.t == T_END) {
                        printf("end reached\n");
                        return lx;
                }
        }

        printf("error: too many tokens\n");
        return lx;
}

int interpret(Buffer l) {

        Lexer *lx = tokenise(&l);

        printf("tokens: ");
        for (int i = 0; i < lx->token_count; i++) {
                printf("[%d:%d] ", (lx->tokens[i]).t, (lx->tokens[i]).val);
        }
        printf("\n");

        int result = parse(lx->tokens, lx->token_count);
        printf("= %d\n", result);

        return 0;
}
