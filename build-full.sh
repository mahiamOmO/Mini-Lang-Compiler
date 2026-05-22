#!/bin/bash

# MiniLang Complete Build & Run Script for WSL
# This builds the compiler AND shows all 7 phases

COMPILER_DIR="/mnt/c/Users/HP/Downloads/compiler"
cd "$COMPILER_DIR"

echo "╔══════════════════════════════════════════════════════════╗"
echo "║      MiniLang Compiler - Complete Build Pipeline        ║"
echo "║    One Command = Build + All 7 Compilation Phases        ║"
echo "╚══════════════════════════════════════════════════════════╝"
echo ""

# Step 1: Build
echo "══════════════════════════════════════════════════════════"
echo "BUILDING COMPILER..."
echo "══════════════════════════════════════════════════════════"
bash build.sh

exit_code=$?

if [ $exit_code -ne 0 ]; then
    echo "Build failed!"
    exit 1
fi

echo ""
echo "Build and compilation complete! All 7 phases displayed above."
echo ""
