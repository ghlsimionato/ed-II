# For multiple files:
# myprogam: main.o foo.o
#     gcc -o myprogram main.o foo.o

# main.o: main.c foo.h
#     gcc -c main.c

# foo.o: foo.c foo.h
#     gcc -c foo.c

CFLAGS = -W -Wall -pedantic
SRCDIR = src
BUILDIR = build
DEPS = structs.h
SRC = main.c

buildprogram: main.o io.o
	@echo "Building main program"
	gcc -o ./build/main-prog main.o io.o

main.o:	${SRC}
	gcc -o main.o -c $(SRC) $(CFLAGS)

io.o: io.c io.h
	gcc -o io.o -c io.c $(CFLAGS)

clean:
	rm -f *o	