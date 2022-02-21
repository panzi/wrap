CC=gcc
CFLAGS=-Wall -std=c11 -Werror
BUILDDIR=build
BIN=$(BUILDDIR)/bin/wrap
OBJ=$(patsubst src/%.c,$(BUILDDIR)/obj/%.o,$(wildcard src/*.c))
RELEASE=OFF
PREFIX=/usr/local/bin

ifeq ($(RELEASE),ON)
    CFLAGS += -O2
else
    CFLAGS += -g
endif

.PHONY: all clean install uninstall

all: $(BIN)

install: $(BIN)
	@mkdir -p $(PREFIX)
	cp $(BIN) $(PREFIX)

uninstall:
	rm $(PREFIX)/wrap

$(BIN): $(OBJ)
	@mkdir -p $(BUILDDIR)/bin
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(BUILDDIR)/obj/%.o: src/%.c src/wrap.h
	@mkdir -p $(BUILDDIR)/obj
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -r $(BIN) $(OBJ)
