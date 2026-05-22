/* Symbol Table */
#ifndef SYMTABLE_NEW_H
#define SYMTABLE_NEW_H

#define MAX_SYMBOLS 256

typedef struct {
    char name[64];
    char type[32];      /* "int" or "float" */
    int scope;
    int offset;
} Symbol;

typedef struct {
    Symbol symbols[MAX_SYMBOLS];
    int count;
    int scope_level;
} SymTable;

SymTable *symtable_create(void);
void symtable_destroy(SymTable *st);
void symtable_insert(SymTable *st, const char *name, const char *type);
Symbol *symtable_lookup(SymTable *st, const char *name);
void symtable_print(SymTable *st);

#endif
