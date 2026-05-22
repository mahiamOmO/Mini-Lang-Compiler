#ifndef OPTIMIZER_H
#define OPTIMIZER_H

/*
 * optimizer.h - Code Optimization
 * Passes: constant folding, dead code elimination, copy propagation
 */

#include "icg.h"

void optimize(ICGContext *ctx);

/* Individual passes */
void opt_constant_folding(ICGContext *ctx);
void opt_copy_propagation(ICGContext *ctx);
void opt_dead_code_elimination(ICGContext *ctx);
void opt_print_stats(ICGContext *ctx, int before, int after);

#endif /* OPTIMIZER_H */
