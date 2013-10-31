# Chatness makefile
# Created: 28.10.2013
# Author: Allek Mott

CC=gcc
CFLAGS=

DEPS=chat.h server.h db.h

SERVER_DEPS = chat.o server.o db.o


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: server

server: $(SERVER_DEPS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: all

all: client server