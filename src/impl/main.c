// main.c  — C99
// interpreter to evaluate single digit integer expressions 

#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

#define MAX_EXPR_LEN 100

int main(void) {
        // REPL loop
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
                // interpret() should output what is interpreted
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
