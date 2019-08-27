CC = gcc
CFLAGS = -W -Wall -pedantic

SRCDIR = ./src
BUILDIR = ./build
OBJDIR = ./obj

SRC = main.c

buildprogram: $(OBJDIR)/main.o $(OBJDIR)/io.o
	@echo "\nBuilding main program\n"
	gcc -o ./build/main-prog $(OBJDIR)/main.o $(OBJDIR)/io.o
	@echo "\nBuild completed!\n"

$(OBJDIR)/main.o:	$(SRCDIR)/${SRC}
	gcc -o $(OBJDIR)/main.o -c $(SRCDIR)/$(SRC) $(CFLAGS)

$(OBJDIR)/io.o: $(SRCDIR)/io.c $(SRCDIR)/headers/io.h
	gcc -o $(OBJDIR)/io.o -c $(SRCDIR)/io.c $(CFLAGS)

clean:
	rm -f *o	