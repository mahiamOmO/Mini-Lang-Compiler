#ifndef ICG_H
#define ICG_H

/*
 * icg.h - Intermediate Code Generation (Three-Address Code)
 */

#define MAX_ICG_INSTRS  4096
#define MAX_LABEL_STACK 64

/* Three-address instruction */
typedef struct {
    char *op;    /* operation: ADD, SUB, ASSIGN, LABEL, GOTO, etc. */
    char *result;
    char *arg1;
    char *arg2;
} TAC;  /* Three-Address Code */

/* ICG Context */
typedef struct {
    TAC   instrs[MAX_ICG_INSTRS];
    int   count;

    int   temp_count;   /* for generating t0, t1, ... */
    int   label_count;  /* for generating L0, L1, ...  */

    /* label stack for if/while/for */
    char *label_stack[MAX_LABEL_STACK];
    int   label_top;
} ICGContext;

/* Function prototypes */
ICGContext *icg_create(void);
void        icg_destroy(ICGContext *ctx);
void        icg_emit(ICGContext *ctx, const char *op,
                     const char *result, const char *arg1, const char *arg2);
char       *icg_new_temp(ICGContext *ctx);
char       *icg_new_label(ICGContext *ctx);
void        icg_push_label(ICGContext *ctx, char *label);
char       *icg_pop_label(ICGContext *ctx);
void        icg_print(ICGContext *ctx);
void        icg_write_file(ICGContext *ctx, const char *filename);

#endif /* ICG_H */
