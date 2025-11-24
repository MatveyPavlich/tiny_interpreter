// parser.c - C99
// Cargo dump stuff from labs and go through it
// TODO: actually go through the code
// parser.c — C99
#include <stdio.h>
#include "lexer.h"

#define MAX_EXPR_LEN 100

// ──────────────────────────────────────────────
// Parser state
// ──────────────────────────────────────────────

typedef struct {
        Token *toks;
        int n;
        int pos;
} Parser;

// ──────────────────────────────────────────────
// Utility: peek, consume, match
// ──────────────────────────────────────────────

static Token peek(Parser *p) {
        if (p->pos < p->n)
                return p->toks[p->pos];
        return (Token){ T_END, 0 };
}

static Token consume(Parser *p) {
        return p->toks[p->pos++];
}

static int match(Parser *p, TokenType tt) {
        if (peek(p).t == tt) {
                consume(p);
                return 1;
        }
        return 0;
}

// ──────────────────────────────────────────────
// Forward declarations
// ──────────────────────────────────────────────

static int parse_expr(Parser *p);
static int parse_term(Parser *p);
static int parse_factor(Parser *p);

// ──────────────────────────────────────────────
// factor → NUMBER | '(' expr ')'
// ──────────────────────────────────────────────

static int parse_factor(Parser *p) {
        Token t = peek(p);

        if (t.t == T_NUM) {
                consume(p);
                return t.val;
        }

        if (match(p, T_LPAREN)) {
                int val = parse_expr(p);
                if (!match(p, T_RPAREN)) {
                        printf("error: missing ')'\n");
                        return 0;
                }
                return val;
        }

        printf("error: unexpected token in factor\n");
        consume(p);
        return 0;
}

// ──────────────────────────────────────────────
// term → factor (('*' | '/') factor)*
// ──────────────────────────────────────────────

static int parse_term(Parser *p) {
        int left = parse_factor(p);

        while (1) {
                if (match(p, T_STAR)) {
                        int right = parse_factor(p);
                        left *= right;
                }
                else if (match(p, T_SLASH)) {
                        int right = parse_factor(p);
                        if (right == 0) {
                                printf("error: division by zero\n");
                                return 0;
                        }
                        left /= right;
                }
                else break;
        }

        return left;
}

// ──────────────────────────────────────────────
// expr → term (('+' | '-') term)*
// ──────────────────────────────────────────────

static int parse_expr(Parser *p) {
        int left = parse_term(p);

        while (1) {
                if (match(p, T_PLUS)) {
                        int right = parse_term(p);
                        left += right;
                }
                else if (match(p, T_MINUS)) {
                        int right = parse_term(p);
                        left -= right;
                }
                else break;
        }

        return left;
}

// ──────────────────────────────────────────────
// Public API
// ──────────────────────────────────────────────

int parse(Token *toks, int n) {
        Parser p = { .toks = toks, .n = n, .pos = 0 };
        return parse_expr(&p);
}
