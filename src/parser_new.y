%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex(void);
extern int line_num;

void yyerror(const char *s);

/* Parse tree node */
typedef struct ASTNode {
    char *type;
    char *value;
    struct ASTNode **children;
    int num_children;
} ASTNode;

ASTNode *ast_create(const char *type, const char *value);
void ast_add_child(ASTNode *parent, ASTNode *child);
void ast_print(ASTNode *node, int indent);

%}

%union {
    int num;
    char *str;
    struct ASTNode *node;
}

%token INT WHILE IF ELSE
%token <num> NUM
%token <str> ID
%token PLUS MINUS MUL DIV MOD
%token ASSIGN EQ NEQ LT LE GT GE
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON COMMA

%left PLUS MINUS
%left MUL DIV MOD

%type <node> program statement_list statement expr

%%

program: statement_list
        {
            printf("\n=== PARSE TREE ===\n");
            ast_print($1, 0);
            printf("=================\n\n");
        }
        ;

statement_list: statement
              {
                  $$ = ast_create("StatementList", NULL);
                  ast_add_child($$, $1);
              }
              | statement_list statement
              {
                  ast_add_child($1, $2);
                  $$ = $1;
              }
              ;

statement: INT ID SEMICOLON 
         {
             ASTNode *node = ast_create("Declaration", NULL);
             ast_add_child(node, ast_create("Type", "int"));
             ast_add_child(node, ast_create("ID", $2));
             $$ = node;
         }
         | ID ASSIGN expr SEMICOLON
         {
             ASTNode *node = ast_create("Assignment", NULL);
             ast_add_child(node, ast_create("ID", $1));
             ast_add_child(node, $3);
             $$ = node;
         }
         | WHILE LPAREN expr RPAREN LBRACE statement_list RBRACE
         {
             ASTNode *node = ast_create("While", NULL);
             ast_add_child(node, $3);
             ast_add_child(node, $6);
             $$ = node;
         }
         | IF LPAREN expr RPAREN LBRACE statement_list RBRACE
         {
             ASTNode *node = ast_create("If", NULL);
             ast_add_child(node, $3);
             ast_add_child(node, $6);
             $$ = node;
         }
         | IF LPAREN expr RPAREN LBRACE statement_list RBRACE ELSE LBRACE statement_list RBRACE
         {
             ASTNode *node = ast_create("IfElse", NULL);
             ast_add_child(node, $3);
             ast_add_child(node, $6);
             ast_add_child(node, $10);
             $$ = node;
         }
         ;

expr: NUM
    {
        char buf[32];
        sprintf(buf, "%d", $1);
        $$ = ast_create("Number", buf);
    }
    | ID
    {
        $$ = ast_create("Variable", $1);
    }
    | expr PLUS expr
    {
        ASTNode *node = ast_create("BinOp", "+");
        ast_add_child(node, $1);
        ast_add_child(node, $3);
        $$ = node;
    }
    | expr MINUS expr
    {
        ASTNode *node = ast_create("BinOp", "-");
        ast_add_child(node, $1);
        ast_add_child(node, $3);
        $$ = node;
    }
    | expr MUL expr
    {
        ASTNode *node = ast_create("BinOp", "*");
        ast_add_child(node, $1);
        ast_add_child(node, $3);
        $$ = node;
    }
    | expr DIV expr
    {
        ASTNode *node = ast_create("BinOp", "/");
        ast_add_child(node, $1);
        ast_add_child(node, $3);
        $$ = node;
    }
    | expr MOD expr
    {
        ASTNode *node = ast_create("BinOp", "%");
        ast_add_child(node, $1);
        ast_add_child(node, $3);
        $$ = node;
    }
    | expr EQ expr
    {
        ASTNode *node = ast_create("Compare", "==");
        ast_add_child(node, $1);
        ast_add_child(node, $3);
        $$ = node;
    }
    | expr NEQ expr
    {
        ASTNode *node = ast_create("Compare", "!=");
        ast_add_child(node, $1);
        ast_add_child(node, $3);
        $$ = node;
    }
    | expr LT expr
    {
        ASTNode *node = ast_create("Compare", "<");
        ast_add_child(node, $1);
        ast_add_child(node, $3);
        $$ = node;
    }
    | expr LE expr
    {
        ASTNode *node = ast_create("Compare", "<=");
        ast_add_child(node, $1);
        ast_add_child(node, $3);
        $$ = node;
    }
    | expr GT expr
    {
        ASTNode *node = ast_create("Compare", ">");
        ast_add_child(node, $1);
        ast_add_child(node, $3);
        $$ = node;
    }
    | expr GE expr
    {
        ASTNode *node = ast_create("Compare", ">=");
        ast_add_child(node, $1);
        ast_add_child(node, $3);
        $$ = node;
    }
    | LPAREN expr RPAREN
    {
        $$ = $2;
    }
    ;

%%

/* AST implementation */
ASTNode *ast_create(const char *type, const char *value) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = strdup(type);
    node->value = value ? strdup(value) : NULL;
    node->children = (ASTNode **)malloc(sizeof(ASTNode *) * 10);
    node->num_children = 0;
    return node;
}

void ast_add_child(ASTNode *parent, ASTNode *child) {
    parent->children[parent->num_children++] = child;
}

void ast_print(ASTNode *node, int indent) {
    if (!node) return;
    
    for (int i = 0; i < indent; i++) printf("  ");
    
    printf("├─ %s", node->type);
    if (node->value) printf(" : %s", node->value);
    printf("\n");
    
    for (int i = 0; i < node->num_children; i++) {
        ast_print(node->children[i], indent + 1);
    }
}

void yyerror(const char *s) {
    fprintf(stderr, "Error at line %d: %s\n", line_num, s);
}
