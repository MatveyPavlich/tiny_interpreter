#define MAX_EXPR_LEN 100

typedef enum {
        T_NUM,
        T_PLUS,
        T_MINUS,
        T_STAR,
        T_SLASH,
        T_LPAREN,
        T_RPAREN,
        T_END,
        T_ERR,
        T_EXPRS,
} TokenType;

typedef struct { const char *s; } Buffer;
typedef struct {
        Token tokens[MAX_EXPR_LEN];
        int parser_pos;
        int token_count;
        const char *s buf;
} Lexer;

typedef struct {
        TokenType t;
        int val;
} Token;

Lexer interpret(Lexer l);
