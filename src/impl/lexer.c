#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "lexer.h"

Token next_token(const char **input) {
        Token token = {TOKEN_INVALID, {0}};

        // Skip whitespace
        while (isspace(**input)) (*input)++;

        char c = **input;
        if (c == '\0') {
                token.type = TOKEN_END;
                return token;
        }

        if (isdigit(c)) {
                // Parse number (single or multiple digits)
                int i = 0;
                while (isdigit(**input) && i < (int)sizeof(token.text) - 1) {
                        token.text[i++] = **input;
                        (*input)++;
                }
                token.text[i] = '\0';
                token.type = TOKEN_NUMBER;
                return token;
        }

        // Single-character operators
        (*input)++;
        switch (c) {
                case '+': token.type = TOKEN_PLUS; break;
                case '-': token.type = TOKEN_MINUS; break;
                case '*': token.type = TOKEN_STAR; break;
                case '/': token.type = TOKEN_SLASH; break;
                case '(': token.type = TOKEN_LPAREN; break;
                case ')': token.type = TOKEN_RPAREN; break;
                default: token.type = TOKEN_INVALID; break;
        }

        return token;
}
