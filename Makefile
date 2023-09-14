CC=gcc
CCFLAGS=-g -Wall -Wextra -lm -o

ifeq ($(OS), Windows_NT)
	OUT=bv.exe
else
	OUT=./bv
endif

build:
	@ $(CC) main.c $(CCFLAGS) $(OUT)

debug: build
	@ gdb -q -tui -ex 'b main' -ex 'run' $(OUT)
