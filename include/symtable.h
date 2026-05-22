#ifndef SYMTABLE_H
#define SYMTABLE_H

/*
 * symtable.h - Symbol Table
 * Uses chained hash table with scope support
 */

#define SYMTABLE_SIZE 256
#define MAX_SCOPES    64

/* Symbol Table Entry */
typedef struct SymEntry {
    char         *name;
    char         *type;       /* "int", "float", "char", "string", "void" */
    char         *kind;       /* "variable", "function", "param" */
    int           scope;      /* scope level */
    int           offset;     /* memory offset for code gen */
    struct SymEntry *next;    /* chaining for collision */
} SymEntry;

/* Symbol Table (scoped hash table) */
typedef struct {
    SymEntry   *table[SYMTABLE_SIZE];
    int         current_scope;
    int         total_vars;
} SymTable;

/* Function prototypes */
SymTable  *symtable_create(void);
void       symtable_destroy(SymTable *st);
void       symtable_enter_scope(SymTable *st);
void       symtable_exit_scope(SymTable *st);
void       symtable_insert(const char *name, const char *type,
                           const char *kind, int offset, SymTable *st);
SymEntry  *symtable_lookup(const char *name, SymTable *st);
SymEntry  *symtable_lookup_current(const char *name, SymTable *st);
void       symtable_print(SymTable *st);

#endif /* SYMTABLE_H */
