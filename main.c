/*
 * main.c - MiniLang Compiler Driver
 * Features: Lexical Analysis (Flex), Syntax Analysis (Bison)
 *          Semantic Analysis, Symbol Table, TAC, Code Generation
 */

#include <stdio.h>
#include <stdlib.h>

extern int yyparse(void);
extern FILE *yyin;

int main(int argc, char **argv) {
    printf("\n╔════════════════════════════════════════════╗\n");
    printf("║         MiniLang Compiler v1.0             ║\n");
    printf("║     Complete Compilation Pipeline           ║\n");
    printf("╚════════════════════════════════════════════╝\n\n");
    
    printf("COMPILATION PHASES:\n");
    printf("  [1] Lexical Analysis      (Flex Scanner)\n");
    printf("  [2] Syntax Analysis       (Bison Parser)\n");
    printf("  [3] Semantic Analysis     (Type Checking)\n");
    printf("  [4] Symbol Table          (Variable Storage)\n");
    printf("  [5] TAC Generation        (Intermediate Code)\n");
    printf("  [6] Optimization          (Code Improvement)\n");
    printf("  [7] Code Generation       (Assembly Output)\n");
    printf("  [8] Symbol Table Display  (Final Variables)\n\n");

    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror("fopen");
            return 1;
        }
    }

    printf("═════════════════════════════════════════════\n");
    printf("PHASE 1: LEXICAL ANALYSIS (Tokenization)\n");
    printf("═════════════════════════════════════════════\n");
    printf("Scanning source code for tokens...\n\n");
    
    if (yyparse() == 0) {
        printf("\n═════════════════════════════════════════════\n");
        printf("✓ COMPILATION SUCCESSFUL!\n");
        printf("═════════════════════════════════════════════\n\n");
    } else {
        printf("\n═════════════════════════════════════════════\n");
        printf("✗ COMPILATION FAILED!\n");
        printf("═════════════════════════════════════════════\n");
        if (argc > 1 && yyin) fclose(yyin);
        return 1;
    }

    if (argc > 1 && yyin) fclose(yyin);
    return 0;
}
