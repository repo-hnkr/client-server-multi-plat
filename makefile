
COMPILER=gcc
CC = g++
BIN = ./bin
SRCDIR = ./src
OBJDIR = ./obj
LIBS = -lWS2_32
SRCS = $(shell find $(SRCDIR) -name '*.c')
#OBJS = $(shell find $(OBJDIR) -name '*.o')
OBJS = $(SRCS:.c=.o)
INCL = -I./include

DEBUG = -g
client_file = client
CFLAGS = -m64 -Wall

.PHONY: default

default: client

CLI_FILES = $(SRCDIR)/client_main.c

client:
	$(COMPILER) $(CLI_FILES) $(LIBS) $(DEBUG) $(CFLAGS) $(INCL) -o $(BIN)/$(client_file)

run:
	./$(BIN)/$(client_file)

clean:
	rm ./$(BIN)/*

