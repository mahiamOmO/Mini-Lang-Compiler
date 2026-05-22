/*
 * symtable.c - Symbol Table Implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/symtable.h"

/* Simple hash function */
static unsigned int hash(const char *name) {
    unsigned int h = 0;
    while (*name) {
        h = (h * 31 + (unsigned char)*name) % SYMTABLE_SIZE;
        name++;
    }
    return h;
}

SymTable *symtable_create(void) {
    SymTable *st = (SymTable *)calloc(1, sizeof(SymTable));
    st->current_scope = 0;
    st->total_vars    = 0;
    return st;
}

void symtable_destroy(SymTable *st) {
    for (int i = 0; i < SYMTABLE_SIZE; i++) {
        SymEntry *e = st->table[i];
        while (e) {
            SymEntry *next = e->next;
            free(e->name); free(e->type); free(e->kind);
            free(e);
            e = next;
        }
    }
    free(st);
}

void symtable_enter_scope(SymTable *st) {
    st->current_scope++;
    printf("[SYMTABLE] Entering scope level %d\n", st->current_scope);
}

void symtable_exit_scope(SymTable *st) {
    /* Remove all entries at current scope */
    for (int i = 0; i < SYMTABLE_SIZE; i++) {
        SymEntry **ep = &st->table[i];
        while (*ep) {
            if ((*ep)->scope == st->current_scope) {
                SymEntry *del = *ep;
                *ep = del->next;
                free(del->name); free(del->type); free(del->kind);
                free(del);
            } else {
                ep = &(*ep)->next;
            }
        }
    }
    printf("[SYMTABLE] Exiting scope level %d\n", st->current_scope);
    st->current_scope--;
}

void symtable_insert(const char *name, const char *type,
                     const char *kind, int offset, SymTable *st) {
    unsigned int idx = hash(name);
    SymEntry *entry  = (SymEntry *)malloc(sizeof(SymEntry));
    entry->name   = strdup(name);
    entry->type   = strdup(type);
    entry->kind   = strdup(kind);
    entry->scope  = st->current_scope;
    entry->offset = offset ? offset : (st->total_vars++ * 4);
    entry->next   = st->table[idx];
    st->table[idx] = entry;
    printf("[SYMTABLE] Inserted '%s' type='%s' kind='%s' scope=%d offset=%d\n",
           name, type, kind, entry->scope, entry->offset);
}

SymEntry *symtable_lookup(const char *name, SymTable *st) {
    unsigned int idx = hash(name);
    SymEntry *e = st->table[idx];
    while (e) {
        if (strcmp(e->name, name) == 0) return e;
        e = e->next;
    }
    return NULL;
}

SymEntry *symtable_lookup_current(const char *name, SymTable *st) {
    unsigned int idx = hash(name);
    SymEntry *e = st->table[idx];
    while (e) {
        if (strcmp(e->name, name) == 0 && e->scope == st->current_scope)
            return e;
        e = e->next;
    }
    return NULL;
}

void symtable_print(SymTable *st) {
    printf("\n========== SYMBOL TABLE ==========\n");
    printf("%-15s %-8s %-10s %-6s %-6s\n",
           "Name", "Type", "Kind", "Scope", "Offset");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < SYMTABLE_SIZE; i++) {
        SymEntry *e = st->table[i];
        while (e) {
            printf("%-15s %-8s %-10s %-6d %-6d\n",
                   e->name, e->type, e->kind, e->scope, e->offset);
            e = e->next;
        }
    }
    printf("==================================\n\n");
}
