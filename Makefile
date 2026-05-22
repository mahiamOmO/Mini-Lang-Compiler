# Makefile for MyLang Compiler
# Requirements: flex, bison, gcc, nasm (for running output)

CC      = gcc
CFLAGS  = -Wall -Wno-unused-function -g -I./include
FLEX    = flex
BISON   = bison

# Source files
SRC     = src/symtable.c src/semantic.c src/icg.c src/optimizer.c src/codegen.c main.c
GEN     = src/lex.yy.c src/parser.tab.c

TARGET  = mylang

.PHONY: all clean run install-deps

all: $(TARGET)

# Step 1: Generate lexer from flex spec
src/lex.yy.c: src/lexer.l src/parser.tab.h
	$(FLEX) -o src/lex.yy.c src/lexer.l

# Step 2: Generate parser from bison spec
src/parser.tab.c src/parser.tab.h: src/parser.y
	$(BISON) -d -o src/parser.tab.c src/parser.y

# Step 3: Compile everything
$(TARGET): src/parser.tab.c src/parser.tab.h src/lex.yy.c $(SRC)
	$(CC) $(CFLAGS) $(GEN) $(SRC) -o $(TARGET) -lm
	@echo ""
	@echo "Build successful! Run: ./mylang <source.ml> <output.asm>"

# Install flex and bison on Ubuntu/WSL
install-deps:
	sudo apt-get update
	sudo apt-get install -y flex bison gcc nasm

# Run example
run: $(TARGET)
	./$(TARGET) examples/hello.ml build/hello.asm
	@echo ""
	@echo "Assembling..."
	nasm -f elf64 build/hello.asm -o build/hello.o
	gcc build/hello.o -o build/hello -no-pie
	@echo "Running..."
	./build/hello

clean:
	rm -f src/lex.yy.c src/parser.tab.c src/parser.tab.h
	rm -f $(TARGET)
	rm -f build/*.asm build/*.o build/*.tac
