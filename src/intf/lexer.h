typedef enum {
        T_NUM,
        T_PLUS,
        T_MINUS,
        T_STAR,
        T_SLASH,
        T_LPAREN,
        T_RPAREN,
        T_END,
        T_ERR
} TokenType;

typedef struct { const char *s; } Lexer;

typedef struct {
        TokenType t;
        int val;
} Token;

int interpret(Lexer l);
