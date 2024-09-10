CC=gcc
CFLAGS=-Wall -Wextra -pedantic -O2
PROGRAMS=$(patsubst %.c,%,$(wildcard *.c))

all: $(PROGRAMS)

%: %.c
	$(CC) $(CFLAGS) $< -o ./bin/$@
