/* Token definitions */
#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    /* Keywords */
    TOKEN_INT, TOKEN_WHILE, TOKEN_IF, TOKEN_ELSE,
    
    /* Identifiers and literals */
    TOKEN_ID, TOKEN_NUM,
    
    /* Operators */
    TOKEN_PLUS, TOKEN_MINUS, TOKEN_MUL, TOKEN_DIV, TOKEN_MOD,
    TOKEN_ASSIGN, TOKEN_EQ, TOKEN_NEQ, TOKEN_LT, TOKEN_LE, TOKEN_GT, TOKEN_GE,
    
    /* Delimiters */
    TOKEN_LPAREN, TOKEN_RPAREN, TOKEN_LBRACE, TOKEN_RBRACE, TOKEN_SEMICOLON, TOKEN_COMMA,
    
    /* Special */
    TOKEN_EOF, TOKEN_ERROR
} TokenType;

typedef struct {
    TokenType type;
    char *value;
    int line;
} Token;

#endif
