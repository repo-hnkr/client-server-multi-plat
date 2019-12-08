
COMPILER=gcc
INCLUDE="./include/"
CC = g++
BIN = ./bin
SRCDIR = ./src
SRCS = $(shell find $(SRCDIR) -name '*.c')
#OBJS = $(shell find $(OBJDIR) -name '*.o')
OBJS = $(SRCS:.c=.o)
INCL = -I./include -L./lib

DEBUG = -g
server_file = server
CFLAGS = -m64 -Wall

.PHONY: default

default: server

SRV_FILES = $(SRCDIR)/server_main.c

server:
	$(COMPILER) $(SRV_FILES) $(DEBUG) $(CFLAGS) $(INCL) -o $(BIN)/$(server_file)


clean:
	rm ./$(BIN)/*

run:
	./$(BIN)/$(server_file)


