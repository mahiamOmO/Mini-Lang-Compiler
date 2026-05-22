#!/bin/bash

# MiniLang Compiler - All Phases Output
# Usage: ./compile.sh <filename.ml>

COMPILER_DIR="/mnt/c/Users/HP/Downloads/compiler"

if [ -z "$1" ]; then
    echo "Usage: $0 <filename.ml>"
    echo "Example: $0 examples/test.ml"
    exit 1
fi

FILE="$1"

if [ ! -f "$FILE" ]; then
    echo "Error: File not found: $FILE"
    exit 1
fi

cd "$COMPILER_DIR"

echo "Compiling: $FILE"
echo ""
cat "$FILE" | ./build/minilang
