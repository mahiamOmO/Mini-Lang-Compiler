#ifndef SEMANTIC_H
#define SEMANTIC_H

/*
 * semantic.h - Semantic Analysis
 */

void  semantic_error(const char *msg, const char *name, int line);
void  semantic_check_assign(const char *ltype, const char *rtype,
                            const char *name, int line);
void  semantic_check_arith(const char *t1, const char *t2,
                           const char *op, int line);
char *semantic_result_type(const char *t1, const char *t2);
int   semantic_compatible(const char *t1, const char *t2);

#endif /* SEMANTIC_H */
