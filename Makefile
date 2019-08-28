CC = gcc
CFLAGS = -W -Wall -pedantic -g

SRCDIR = ./src
BUILDIR = ./build
OBJDIR = ./obj

SRC = main.c

$(shell mkdir -p $(BUILDIR))
$(shell mkdir -p $(OBJDIR))

# TODO: More generic makefile

build: $(OBJDIR)/main.o $(OBJDIR)/io.o $(OBJDIR)/insert.o $(OBJDIR)/remove.o
	@echo "\nBuilding main program\n"
	$(CC) -o ./build/insurance-reg $(OBJDIR)/main.o $(OBJDIR)/io.o $(OBJDIR)/insert.o $(OBJDIR)/remove.o -g
	@echo "\nBuild completed!\n"

$(OBJDIR)/main.o:	$(SRCDIR)/${SRC}
	$(CC) -o $(OBJDIR)/main.o -c $(SRCDIR)/$(SRC) $(CFLAGS)

$(OBJDIR)/io.o: $(SRCDIR)/io.c $(SRCDIR)/headers/io.h
	$(CC) -o $(OBJDIR)/io.o -c $(SRCDIR)/io.c $(CFLAGS)

$(OBJDIR)/insert.o: $(SRCDIR)/insert.c $(SRCDIR)/headers/insert.h
	$(CC) -o $(OBJDIR)/insert.o -c $(SRCDIR)/insert.c $(CFLAGS)

$(OBJDIR)/remove.o: $(SRCDIR)/remove.c $(SRCDIR)/headers/remove.h
	$(CC) -o $(OBJDIR)/remove.o -c $(SRCDIR)/remove.c $(CFLAGS)

# TODO: make a decent clean

clean-obj:
	rm -rf ./obj

clean-build:
	rm -rf ./build

clean: clean-obj clean-build
