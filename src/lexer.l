%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"

int line_num = 1;
int token_count = 0;

#define PRINT_TOKEN(type, value) \
    token_count++; \
    printf("  [%-3d] [LEXICAL] %-15s: %s\n", token_count, type, value)

%}

%%

"int"       { PRINT_TOKEN("KEYWORD", "int"); return INT; }
"while"     { PRINT_TOKEN("KEYWORD", "while"); return WHILE; }
"if"        { PRINT_TOKEN("KEYWORD", "if"); return IF; }
"else"      { PRINT_TOKEN("KEYWORD", "else"); return ELSE; }
"print"     { PRINT_TOKEN("KEYWORD", "print"); return PRINT; }
"return"    { PRINT_TOKEN("KEYWORD", "return"); return RETURN; }

[a-zA-Z_][a-zA-Z0-9_]* { 
    yylval.str = strdup(yytext); 
    PRINT_TOKEN("IDENTIFIER", yytext);
    return ID; 
}

[0-9]+      { 
    yylval.num = atoi(yytext); 
    PRINT_TOKEN("NUMBER", yytext);
    return NUM; 
}

"+"         { PRINT_TOKEN("OPERATOR", "+"); return PLUS; }
"-"         { PRINT_TOKEN("OPERATOR", "-"); return MINUS; }
"++"        { PRINT_TOKEN("OPERATOR", "++"); return INC; }
"--"        { PRINT_TOKEN("OPERATOR", "--"); return DEC; }
"*"         { PRINT_TOKEN("OPERATOR", "*"); return MUL; }
"/"         { PRINT_TOKEN("OPERATOR", "/"); return DIV; }
"%"         { PRINT_TOKEN("OPERATOR", "%"); return MOD; }
"="         { PRINT_TOKEN("OPERATOR", "="); return ASSIGN; }
"=="        { PRINT_TOKEN("OPERATOR", "=="); return EQ; }
"!="        { PRINT_TOKEN("OPERATOR", "!="); return NEQ; }
"<"         { PRINT_TOKEN("OPERATOR", "<"); return LT; }
"<="        { PRINT_TOKEN("OPERATOR", "<="); return LE; }
">"         { PRINT_TOKEN("OPERATOR", ">"); return GT; }
">="        { PRINT_TOKEN("OPERATOR", ">="); return GE; }

"("         { PRINT_TOKEN("SYMBOL", "("); return LPAREN; }
")"         { PRINT_TOKEN("SYMBOL", ")"); return RPAREN; }
"{"         { PRINT_TOKEN("SYMBOL", "{"); return LBRACE; }
"}"         { PRINT_TOKEN("SYMBOL", "}"); return RBRACE; }
";"         { PRINT_TOKEN("SYMBOL", ";"); return SEMICOLON; }
","         { PRINT_TOKEN("SYMBOL", ","); return COMMA; }

[ \t]      { }
\n          { line_num++; }
"//".*     { }

.           { }

%%

int yywrap(void) { return 1; }