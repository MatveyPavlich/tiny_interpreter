# Tiny Interpreter (Pratt Parser)

A tiny expression interpreter built in C99 using a **Pratt parser**. It reads single-digit arithmetic expressions (only `+ - * /` are supported), tokenises them, builds an AST, and evaluates the result. Parenthesis are also handled. Example:
```
clc> (3 + 4) * 2
= 14
clc> 6/2+1
= 4
```

---

## Building & Running
From the project root:
```
make        # compiles into build/main
make run    # runs the interpreter
```
Or simply after compiling:
```
./build/main
```

## Project Structure
```
src/
  intf/      # Public headers
    lexer.h
    parser.h
  impl/      # Implementations
    lexer.c  # Tokenises input strings
    parser.c # Pratt parser + AST construction
    main.c   # REPL loop
```

- **Lexer**: Converts input text into a stream of tokens (`T_NUM`, `T_PLUS`, `T_LPAREN`, etc.)
- **Parser**: Implements Pratt’s top-down operator-precedence algorithm. Builds an `Expr` tree representing the expression.
- **Evaluator**: Walks the AST and computes the final numeric result.
