#ifndef CODEGEN_H
#define CODEGEN_H

/*
 * codegen.h - Target Code Generation
 * Generates x86-64 Linux Assembly (NASM syntax)
 */

#include "icg.h"
#include "symtable.h"

typedef struct {
    FILE     *out;
    SymTable *sym;
    int       stack_offset;   /* current RSP offset for locals */
    char      strings[64][256]; /* string literals for .data section */
    int       str_count;
} CodegenCtx;

CodegenCtx *codegen_create(const char *outfile, SymTable *sym);
void        codegen_destroy(CodegenCtx *ctx);
void        codegen_generate(CodegenCtx *ctx, ICGContext *icg);

#endif /* CODEGEN_H */
