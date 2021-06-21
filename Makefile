#
#	Makefile for ptimer
#
#	Created by dimpk
#


CFLAGS = -g -Wall

ptimer: main.c
	$(CC) $(CFLAGS) $^ -o $@

