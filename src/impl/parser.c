// parser.c - C99
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"

#define MAX_EXPR_LEN 100

// Forward declarations
static Expr *parse_bp(Lexer *lx, int min_bp);
static int lbp(TokenType t);
static Expr *nud(Lexer *lx, Token t);
static Expr *led(Lexer *lx, Token t, Expr *left);

Expr *parse(Lexer *lx) {
        // Public API to the parser
        lx->parser_pos = 0;
        return parse_bp(lx, 0);
}

static Expr *parse_bp(Lexer *lx, int min_bp) {
        // Main loop in the parsing algorithm
        Token t = lx->tokens[lx->parser_pos++];
        Expr *left = nud(lx, t);

        while (1) {
                Token look = lx->tokens[lx->parser_pos];
                int bp = lbp(look.t);

                if (bp <= min_bp)
                        break;

                lx->parser_pos++; // consume operator
                left = led(lx, look, left);
        }

        return left;
}

static int lbp(TokenType t) {
        // Assign binding power to each operator
        switch (t) {
                case T_PLUS:   return 10;
                case T_MINUS:  return 10;
                case T_STAR:   return 20;
                case T_SLASH:  return 20;
                default:       return 0;
        }
}

static Expr *nud(Lexer *lx, Token t) {
        // Null denotation (evaluating opperands/parentethis)
        Expr *node = malloc(sizeof(Expr));

        if (t.t == T_NUM) {
                node->type = atom;
                node->val = t.val;
                node->left = node->right = NULL;
                return node;
        }

        if (t.t == T_LPAREN) {
                Expr *inside = parse_bp(lx, 0);
                if (lx->tokens[lx->parser_pos].t != T_RPAREN) {
                        printf("error: missing ')'\n");
                } else {
                        lx->parser_pos++;
                }
                return inside;
        }

        printf("error: unexpected token in nud\n");
        free(node);
        return NULL;
}

static Expr *led(Lexer *lx, Token t, Expr *left) {
        // Left denotation (evaluating operations)
        Expr *node = malloc(sizeof(Expr));
        node->type = expr;
        node->left = left;

        int bp = lbp(t.t);

        Expr *right = parse_bp(lx, bp);
        node->right = right;

        switch (t.t) {
                case T_PLUS:  node->val = '+'; break;
                case T_MINUS: node->val = '-'; break;
                case T_STAR:  node->val = '*'; break;
                case T_SLASH: node->val = '/'; break;
                default:
                              printf("error: unexpected operator\n");
                              break;
        }

        return node;
}


