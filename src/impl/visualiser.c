#include <stdio.h>
#include "lexer.h"
#include "parser.h"

// Internal helper
static void print_indent(int depth) {
        for (int i = 0; i < depth; i++)
                printf("    ");
}

void print_ast(Expr *node, int depth) {
        if (!node) return;

        print_indent(depth);

        if (node->type == atom) {
                printf("%d\n", node->val);
        } else {
                printf("%c\n", (char)node->val);
        }

        print_ast(node->left, depth + 1);
        print_ast(node->right, depth + 1);
}
