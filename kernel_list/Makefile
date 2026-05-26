CC = clang
CFLAGS = -std=gnu17 -Wall
SRCS := $(wildcard *.c)

all: $(SRCS)
	@$(CC) $(CFLAGS) $^ -o main
	@./main
