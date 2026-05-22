/*
 * icg.c - Intermediate Code Generation
 * Generates Three-Address Code (TAC)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/icg.h"

ICGContext *icg_create(void) {
    ICGContext *ctx = (ICGContext *)calloc(1, sizeof(ICGContext));
    ctx->count       = 0;
    ctx->temp_count  = 0;
    ctx->label_count = 0;
    ctx->label_top   = 0;
    return ctx;
}

void icg_destroy(ICGContext *ctx) {
    for (int i = 0; i < ctx->count; i++) {
        free(ctx->instrs[i].op);
        free(ctx->instrs[i].result);
        free(ctx->instrs[i].arg1);
        free(ctx->instrs[i].arg2);
    }
    free(ctx);
}

void icg_emit(ICGContext *ctx, const char *op,
              const char *result, const char *arg1, const char *arg2) {
    if (ctx->count >= MAX_ICG_INSTRS) {
        fprintf(stderr, "[ICG] Instruction limit reached!\n");
        return;
    }
    TAC *t    = &ctx->instrs[ctx->count++];
    t->op     = strdup(op);
    t->result = strdup(result ? result : "");
    t->arg1   = strdup(arg1   ? arg1   : "");
    t->arg2   = strdup(arg2   ? arg2   : "");
}

char *icg_new_temp(ICGContext *ctx) {
    char *buf = (char *)malloc(16);
    sprintf(buf, "t%d", ctx->temp_count++);
    return buf;
}

char *icg_new_label(ICGContext *ctx) {
    char *buf = (char *)malloc(16);
    sprintf(buf, "L%d", ctx->label_count++);
    return buf;
}

void icg_push_label(ICGContext *ctx, char *label) {
    ctx->label_stack[ctx->label_top++] = label;
}

char *icg_pop_label(ICGContext *ctx) {
    if (ctx->label_top == 0) return "";
    return ctx->label_stack[--ctx->label_top];
}

void icg_print(ICGContext *ctx) {
    printf("\n========== INTERMEDIATE CODE (3-Address) ==========\n");
    for (int i = 0; i < ctx->count; i++) {
        TAC *t = &ctx->instrs[i];
        if (strcmp(t->op, "LABEL") == 0) {
            printf("%s:\n", t->result);
        } else if (strcmp(t->op, "ASSIGN") == 0) {
            printf("  %s = %s\n", t->result, t->arg1);
        } else if (strcmp(t->op, "ADD") == 0) {
            printf("  %s = %s + %s\n", t->result, t->arg1, t->arg2);
        } else if (strcmp(t->op, "SUB") == 0) {
            printf("  %s = %s - %s\n", t->result, t->arg1, t->arg2);
        } else if (strcmp(t->op, "MUL") == 0) {
            printf("  %s = %s * %s\n", t->result, t->arg1, t->arg2);
        } else if (strcmp(t->op, "DIV") == 0) {
            printf("  %s = %s / %s\n", t->result, t->arg1, t->arg2);
        } else if (strcmp(t->op, "MOD") == 0) {
            printf("  %s = %s %% %s\n", t->result, t->arg1, t->arg2);
        } else if (strcmp(t->op, "NEG") == 0) {
            printf("  %s = -%s\n", t->result, t->arg1);
        } else if (strcmp(t->op, "NOT") == 0) {
            printf("  %s = !%s\n", t->result, t->arg1);
        } else if (strcmp(t->op, "EQ") == 0) {
            printf("  %s = %s == %s\n", t->result, t->arg1, t->arg2);
        } else if (strcmp(t->op, "NEQ") == 0) {
            printf("  %s = %s != %s\n", t->result, t->arg1, t->arg2);
        } else if (strcmp(t->op, "LT") == 0) {
            printf("  %s = %s < %s\n", t->result, t->arg1, t->arg2);
        } else if (strcmp(t->op, "LE") == 0) {
            printf("  %s = %s <= %s\n", t->result, t->arg1, t->arg2);
        } else if (strcmp(t->op, "GT") == 0) {
            printf("  %s = %s > %s\n", t->result, t->arg1, t->arg2);
        } else if (strcmp(t->op, "GE") == 0) {
            printf("  %s = %s >= %s\n", t->result, t->arg1, t->arg2);
        } else if (strcmp(t->op, "AND") == 0) {
            printf("  %s = %s && %s\n", t->result, t->arg1, t->arg2);
        } else if (strcmp(t->op, "OR") == 0) {
            printf("  %s = %s || %s\n", t->result, t->arg1, t->arg2);
        } else if (strcmp(t->op, "GOTO") == 0) {
            printf("  goto %s\n", t->result);
        } else if (strcmp(t->op, "IF_FALSE") == 0) {
            printf("  if_false %s goto %s\n", t->result, t->arg1);
        } else if (strcmp(t->op, "RETURN") == 0) {
            printf("  return %s\n", t->result);
        } else if (strcmp(t->op, "PRINT") == 0) {
            printf("  print %s\n", t->result);
        } else if (strcmp(t->op, "PARAM") == 0) {
            printf("  param %s\n", t->result);
        } else if (strcmp(t->op, "CALL") == 0) {
            printf("  %s = call %s\n", t->result, t->arg1);
        } else if (strcmp(t->op, "FUNC_BEGIN") == 0) {
            printf("\n--- function %s ---\n", t->result);
        } else if (strcmp(t->op, "FUNC_END") == 0) {
            printf("--- end %s ---\n\n", t->result);
        } else if (strcmp(t->op, "DECL") == 0) {
            printf("  decl %s %s\n", t->result, t->arg1);
        } else {
            printf("  %s %s %s %s\n", t->op, t->result, t->arg1, t->arg2);
        }
    }
    printf("====================================================\n\n");
}

void icg_write_file(ICGContext *ctx, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) { perror("icg_write_file"); return; }
    fprintf(f, "# Three-Address Intermediate Code\n\n");
    for (int i = 0; i < ctx->count; i++) {
        TAC *t = &ctx->instrs[i];
        fprintf(f, "%s\t%s\t%s\t%s\n", t->op, t->result, t->arg1, t->arg2);
    }
    fclose(f);
    printf("[ICG] Written to %s\n", filename);
}
