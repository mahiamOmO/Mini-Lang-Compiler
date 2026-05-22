#!/bin/bash

# Quick WSL Compiler Runner
# Usage: ./run-wsl.sh [example] or just ./run-wsl.sh

COMPILER="/mnt/c/Users/HP/Downloads/compiler"
cd "$COMPILER"

if [ -z "$1" ]; then
    echo "Usage: $0 <example>"
    echo ""
    echo "Available examples:"
    ls -1 examples/ | sed 's/^/  /'
    echo ""
    exit 0
fi

EXAMPLE="$1"
FILE="examples/$EXAMPLE"

if [ ! -f "$FILE" ]; then
    echo "❌ File not found: $FILE"
    exit 1
fi

echo "📝 Compiling: $EXAMPLE"
echo ""
cat "$FILE" | ./build/minilang
