#!/bin/bash

echo "╔════════════════════════════════════════════════════╗"
echo "║     MiniLang Compiler - Complete Build System     ║"
echo "║   Building + Showing All 7 Compilation Phases      ║"
echo "╚════════════════════════════════════════════════════╝"
echo ""

mkdir -p build

cd src

echo "════════════════════════════════════════════════════"
echo "STEP 1: Running Flex (Lexical Analysis Generator)..."
echo "════════════════════════════════════════════════════"
flex -o lex.yy.c lexer.l
echo "✓ Lexer generated: lex.yy.c"
echo ""

echo "════════════════════════════════════════════════════"
echo "STEP 2: Running Bison (Parser Generator)..."
echo "════════════════════════════════════════════════════"
bison -d parser.y
echo "✓ Parser generated: parser.tab.c, parser.tab.h"
echo ""

echo "════════════════════════════════════════════════════"
echo "STEP 3: Compiling with GCC..."
echo "════════════════════════════════════════════════════"
gcc -Wall -g lex.yy.c parser.tab.c ../main.c -o ../build/minilang -lm

if [ $? -eq 0 ]; then
    echo "✓ Compilation successful: ./build/minilang"
else
    echo "✗ Build failed!"
    exit 1
fi

cd ..

echo ""
echo "════════════════════════════════════════════════════"
echo "STEP 4: Running Compiler with Test Example"
echo "════════════════════════════════════════════════════"
echo ""
echo "Test file: examples/test.ml"
echo ""

cat examples/test.ml | ./build/minilang

echo ""
echo "════════════════════════════════════════════════════"
echo "BUILD & COMPILATION COMPLETE!"
echo "════════════════════════════════════════════════════"
echo ""
echo "To test other examples, use:"
echo "  cat examples/complex.ml | ./build/minilang"
echo "  cat examples/ifelse.ml | ./build/minilang"
echo "  cat examples/counter.ml | ./build/minilang"
echo "  cat examples/nested.ml | ./build/minilang"
echo ""
echo ""
echo "  Usage: ./mylang <source.ml> <output.asm>"
echo ""
echo "  Quick test:"
echo "    ./mylang examples/hello.ml build/hello.asm"
echo "    nasm -f elf64 build/hello.asm -o build/hello.o"
echo "    gcc build/hello.o -o build/hello -no-pie"
echo "    ./build/hello"
echo "========================================"
