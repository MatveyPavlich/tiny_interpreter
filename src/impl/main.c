// expr_repl.c  — C99
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
        T_NUM, T_PLUS, T_MINUS, T_STAR, T_SLASH, T_LPAREN, T_RPAREN, T_END, T_ERR
} TokType;

typedef struct { TokType type; double num; } Token;

typedef struct { const char *p; } Lexer;

/* ---------- Lexer ---------- */
static void skip_ws(Lexer *lx){ while (isspace((unsigned char)*lx->p)) lx->p++; }

static Token next_token(Lexer *lx){
        skip_ws(lx);
        char c = *lx->p;
        if (c == '\0') return (Token){T_END, 0};
        if (isdigit((unsigned char)c) || (c=='.' && isdigit((unsigned char)lx->p[1]))){
                char *end; double v = strtod(lx->p, &end);
                lx->p = end;
                return (Token){T_NUM, v};
        }
        lx->p++;
        switch (c){
                case '+': return (Token){T_PLUS, 0};
                case '-': return (Token){T_MINUS, 0};
                case '*': return (Token){T_STAR, 0};
                case '/': return (Token){T_SLASH,0};
                case '(': return (Token){T_LPAREN,0};
                case ')': return (Token){T_RPAREN,0};
                default:  return (Token){T_ERR,  0};
        }
}

/* ---------- Recursive-descent parser + evaluator ----------
Grammar:
expr  := term (('+'|'-') term)*
term  := factor (('*'|'/') factor)*
factor:= NUMBER | '(' expr ')'
*/
typedef struct {
        Lexer lx;
        Token cur;
        int   ok;   // 1 if no parse error so far
        char  msg[64];
} Parser;

static void advance(Parser *ps){ ps->cur = next_token(&ps->lx); }

static double parse_expr(Parser *ps); // fwd

static double parse_factor(Parser *ps){
        if (ps->cur.type == T_NUM){
                double v = ps->cur.num; advance(ps); return v;
        }
        if (ps->cur.type == T_LPAREN){
                advance(ps);
                double v = parse_expr(ps);
                if (ps->cur.type != T_RPAREN){ ps->ok=0; strcpy(ps->msg,"missing ')'"); return 0; }
                advance(ps);
                return v;
        }
        ps->ok = 0; strcpy(ps->msg, "expected number or '('");
        return 0;
}

static double parse_term(Parser *ps){
        double v = parse_factor(ps);
        while (ps->ok && (ps->cur.type==T_STAR || ps->cur.type==T_SLASH)){
                TokType op = ps->cur.type; advance(ps);
                double rhs = parse_factor(ps);
                if (!ps->ok) return 0;
                if (op==T_STAR) v *= rhs;
                else {
                        if (rhs==0){ ps->ok=0; strcpy(ps->msg,"division by zero"); return 0; }
                        v /= rhs;
                }
        }
        return v;
}

static double parse_expr(Parser *ps){
        double v = parse_term(ps);
        while (ps->ok && (ps->cur.type==T_PLUS || ps->cur.type==T_MINUS)){
                TokType op = ps->cur.type; advance(ps);
                double rhs = parse_term(ps);
                if (!ps->ok) return 0;
                v = (op==T_PLUS) ? v + rhs : v - rhs;
        }
        return v;
}

static int eval_line(const char *line, double *out, char errbuf[64]){
        Parser ps = { .lx = { .p = line }, .ok = 1, .msg = "" };
        advance(&ps);
        if (ps.cur.type == T_END){ strcpy(errbuf, "empty input"); return 0; }
        double v = parse_expr(&ps);
        if (ps.ok && ps.cur.type != T_END){ ps.ok=0; strcpy(ps.msg,"trailing input"); }
        if (!ps.ok){ strcpy(errbuf, ps.msg); return 0; }
        *out = v; return 1;
}

/* ---------- REPL ---------- */
int main(void){
        char buf[1024];
        while (1){
                fputs("calc> ", stdout);
                if (!fgets(buf, sizeof buf, stdin)) break;          // Ctrl-D
                                                                    // trim newline
                buf[strcspn(buf, "\r\n")] = '\0';
                if (buf[0]=='\0') continue;
                if (strcmp(buf,"quit")==0 || strcmp(buf,"exit")==0) break;

                double result; char err[64];
                if (eval_line(buf, &result, err))
                        printf("= %.15g\n", result);
                else
                        printf("error: %s\n", err);
        }
        return 0;
}
