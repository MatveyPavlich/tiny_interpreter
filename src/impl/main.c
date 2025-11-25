// main.c  — C99
// interpreter to evaluate single digit integer expressions 

#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"

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

                Buffer b = {.s = buf};
                interpret(b);
        }

        return 0;
}
