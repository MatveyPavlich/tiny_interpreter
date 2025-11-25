// parser.c - C99
#include <stdio.h>
#include "lexer.h"

#define MAX_EXPR_LEN 100

//TODO: Iterate through tokens and create a treee structure
//TODO: incorportate bind_power to each token
//TODO: Make sure Lexer type stores an array of tokens rather than a string

typedef enum {atom, expr } NodeType;

typedef struct {
        NodeType type;
        int val;
        struct Expr *left;
        struct Expr *rigth;
} Expr;

int parse(void) {
        // Public API to the parser
        Expr test_expr;
        (void) test_expr;
        printf("yoo!\n");
        return 0;
}
