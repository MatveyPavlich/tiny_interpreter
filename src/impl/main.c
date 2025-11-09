#include <stdio.h>
#include "lexer.h"


int main(void) {
        const char *input = "12 + 3 * 3 * (4 - 2)";
        Token tok;

        printf("Input: %s\n", input);
        printf("Tokens:\n");

        while ((tok = next_token(&input)).type != TOKEN_END) {
                printf("  %-10s '%s'\n",
                                (tok.type == TOKEN_NUMBER) ? "NUMBER" :
                                (tok.type == TOKEN_PLUS)   ? "PLUS"   :
                                (tok.type == TOKEN_MINUS)  ? "MINUS"  :
                                (tok.type == TOKEN_STAR)   ? "STAR"   :
                                (tok.type == TOKEN_SLASH)  ? "SLASH"  :
                                (tok.type == TOKEN_LPAREN) ? "LPAREN" :
                                (tok.type == TOKEN_RPAREN) ? "RPAREN" :
                                "INVALID",
                                tok.text);
        }

        return 0;
}
