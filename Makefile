CC=gcc
CFLAGS=-std=gnu99 -Wall
PROG = shredder

shredder: main.c
	$(CC) -o $(PROG) main.c $(CFLAGS)

install:
	-unlink /usr/local/bin/shredder
	-unlink /usr/bin/shredder
	install -m 0755 shredder /usr/local/bin
	ln -s /usr/local/bin/shredder /usr/bin/shredder

.PHONY: install
