#ifndef TOKENS_H
#define TOKENS_H

/*
 * tokens.h - Token type definitions
 */

typedef enum {
    /* Keywords */
    TOK_INT, TOK_FLOAT, TOK_CHAR, TOK_STRING, TOK_VOID,
    TOK_IF, TOK_ELSE, TOK_WHILE, TOK_FOR, TOK_RETURN,
    TOK_PRINT,
    /* Literals */
    TOK_INT_LIT, TOK_FLOAT_LIT, TOK_STRING_LIT, TOK_BOOL_LIT,
    /* Identifiers */
    TOK_ID,
    /* Operators */
    TOK_PLUS, TOK_MINUS, TOK_MUL, TOK_DIV, TOK_MOD,
    TOK_ASSIGN, TOK_EQ, TOK_NEQ, TOK_LT, TOK_LE, TOK_GT, TOK_GE,
    TOK_AND, TOK_OR, TOK_NOT, TOK_INC, TOK_DEC,
    /* Delimiters */
    TOK_LPAREN, TOK_RPAREN, TOK_LBRACE, TOK_RBRACE,
    TOK_LBRACKET, TOK_RBRACKET, TOK_SEMICOLON, TOK_COMMA,
    TOK_EOF
} TokenType;

#endif /* TOKENS_H */
