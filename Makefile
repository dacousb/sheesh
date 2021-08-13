CC ?= gcc
CFLAGS = -O2
BINDIR = ./bin
TARGET = $(BINDIR)/sheesh
SRCS := $(shell find src -type f -name *.c)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRCS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $@

run: $(TARGET)
	$<

clean:
	rm -rf $(BINDIR)