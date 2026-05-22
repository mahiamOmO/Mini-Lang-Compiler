/*
 * semantic.c - Simple Semantic Analysis
 * Type checking and validation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/semantic.h"

void semantic_error(const char *msg, const char *name, int line) {
    fprintf(stderr, "Semantic error at line %d: %s (%s)\n", line, msg, name);
    exit(1);
}

int semantic_compatible(const char *t1, const char *t2) {
    if (!t1 || !t2) return 0;
    return strcmp(t1, t2) == 0;
}

void semantic_check_assign(const char *ltype, const char *rtype,
                           const char *name, int line) {
    if (!rtype) return;
    if (!semantic_compatible(ltype, rtype)) {
        fprintf(stderr, "Type mismatch at line %d: %s\n", line, name);
        exit(1);
    }
}

void semantic_check_arith(const char *t1, const char *t2,
                          const char *op, int line) {
    if (!t1 || !t2) return;
}

int semantic_check(void *ast) {
    return 0;
}

char *semantic_result_type(const char *t1, const char *t2) {
    if (!t1) return (char *)t2;
    if (!t2) return (char *)t1;
    return "int";
}
