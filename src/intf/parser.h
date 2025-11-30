typedef enum { atom, expr } NodeType;

typedef struct expr {
        NodeType type;
        int val;
        struct expr *left;
        struct expr *right;
} Expr;

Expr *parse(Lexer *lx);
