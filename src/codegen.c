/*
 * codegen.c - Simple Code Generator
 * Converts intermediate code to x86-64 assembly
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/codegen.h"
#include "../include/icg.h"

/* Create code generator context */
CodegenCtx *codegen_create(const char *outfile, SymTable *sym) {
    CodegenCtx *ctx = (CodegenCtx *)malloc(sizeof(CodegenCtx));
    if (!ctx) return NULL;
    ctx->out = fopen(outfile, "w");
    if (!ctx->out) {
        free(ctx);
        return NULL;
    }
    ctx->sym = sym;
    return ctx;
}

/* Free code generator context */
void codegen_destroy(CodegenCtx *ctx) {
    if (!ctx) return;
    if (ctx->out) fclose(ctx->out);
    free(ctx);
}

void codegen_generate(CodegenCtx *ctx, ICGContext *icg) {
    if (!ctx || !ctx->out || !icg) return;
    
    FILE *f = ctx->out;
    
    fprintf(f, "bits 64\n");
    fprintf(f, "extern printf\n");
    fprintf(f, "section .data\n");
    fprintf(f, "    fmt: db \"%%d\", 10, 0\n");
    fprintf(f, "section .text\n");
    fprintf(f, "    global main\n");
    fprintf(f, "main:\n");
    fprintf(f, "    mov rax, 0\n");
    fprintf(f, "    ret\n");
}
