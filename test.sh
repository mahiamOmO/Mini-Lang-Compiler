#!/bin/bash

# MiniLang Compiler Test Script (WSL)
# Usage: ./test.sh [example_name]

COMPILER_DIR="/mnt/c/Users/HP/Downloads/compiler"
cd "$COMPILER_DIR"

# Default to test.ml if no argument provided
EXAMPLE="${1:-test.ml}"
EXAMPLE_FILE="examples/$EXAMPLE"

echo "========================================"
echo "MiniLang Compiler Test (WSL)"
echo "========================================"
echo ""
echo "Testing with: $EXAMPLE"
echo "File path: $EXAMPLE_FILE"
echo ""

if [ ! -f "$EXAMPLE_FILE" ]; then
    echo "ERROR: File not found: $EXAMPLE_FILE"
    echo ""
    echo "Available examples:"
    ls -1 examples/
    exit 1
fi

echo "Source code:"
echo "---"
cat "$EXAMPLE_FILE"
echo "---"
echo ""

echo "Parse tree output:"
echo ""
cat "$EXAMPLE_FILE" | ./build/minilang

echo ""
echo "========================================"
