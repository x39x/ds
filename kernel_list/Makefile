CC = clang
CFLAGS = -std=gnu17 -Wall
TARGET = main
SRCS := $(wildcard *.c)

all: $(TARGET)

$(TARGET): $(SRCS)
	@$(CC) $(CFLAGS) $^ -o $@
	@./$@
	@rm -f $(TARGET)
