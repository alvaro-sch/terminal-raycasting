CC ?= gcc

SRC = src

CFLAGS = -Wall -Wextra -pedantic -std=c17 -Iinclude
LDFLAGS = -lm `pkg-config --libs ncurses`

T ?= debug

SOURCE = $(wildcard $(SRC)/*.c)
OBJECT = $(SOURCE:$(SRC)/%.c=$T_%.o)

ifeq ($T,release)
CFLAGS += -O3
else
T = debug
CFLAGS += -g -O0 -DDEBUG
endif

.PHONY: clean

all: $T

$T_%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$T: $(OBJECT)
	$(CC) $(OBJECT) -o $T $(CFLAGS) $(LDFLAGS)

run: $T
	./$T

clean:
	-rm *.o debug release
