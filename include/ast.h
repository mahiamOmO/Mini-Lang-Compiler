/* Abstract Syntax Tree */
#ifndef AST_H
#define AST_H

typedef enum {
    AST_NUM, AST_ID, AST_BINOP, AST_ASSIGN, AST_IF, AST_WHILE, AST_BLOCK, AST_DECL
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    
    /* For leaf nodes */
    int intval;
    char *strval;
    
    /* For operators */
    char op;
    
    /* Child nodes */
    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *condition;
    struct ASTNode *body;
    
    /* For sequences */
    struct ASTNode *statements;
    struct ASTNode *next;
} ASTNode;

ASTNode *ast_create_num(int val);
ASTNode *ast_create_id(const char *name);
ASTNode *ast_create_binop(ASTNode *left, char op, ASTNode *right);
ASTNode *ast_create_assign(ASTNode *id, ASTNode *expr);
ASTNode *ast_create_if(ASTNode *cond, ASTNode *body, ASTNode *else_body);
ASTNode *ast_create_while(ASTNode *cond, ASTNode *body);
ASTNode *ast_create_block(ASTNode *statements);
void ast_free(ASTNode *node);
void ast_print(ASTNode *node, int indent);

#endif
