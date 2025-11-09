typedef enum {
        TOKEN_NUMBER,
        TOKEN_PLUS,
        TOKEN_MINUS,
        TOKEN_STAR,
        TOKEN_SLASH,
        TOKEN_LPAREN,
        TOKEN_RPAREN,
        TOKEN_END,
        TOKEN_INVALID
} TokenType;

typedef struct {
        TokenType type;
        char text[32];   // token text (for numbers or debugging)
} Token;

Token next_token(const char **input);
