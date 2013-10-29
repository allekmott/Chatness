# Chatness makefile
# Created: 28.10.2013
# Author: Allek Mott

CC=gcc
CFLAGS=

DEPS=chat.h server.h


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: server

server: chat.o server.o
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: all

all: client server