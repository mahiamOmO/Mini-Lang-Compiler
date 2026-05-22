/* Code Generator */
#ifndef CODEGEN_NEW_H
#define CODEGEN_NEW_H

#include "ast.h"
#include "symtable_new.h"

void codegen(const char *outfile, ASTNode *ast, SymTable *st);

#endif
