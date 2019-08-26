# For multiple files:
# myprogam: main.o foo.o
#     gcc -o myprogram main.o foo.o

# main.o: main.c foo.h
#     gcc -c main.c

# foo.o: foo.c foo.h
#     gcc -c foo.c

CFLAGS= -W -Wall -ansi -pedantic
SRC=main.c


buildprogram: main.o
	gcc -o ./build/main-prog main.o

main.o:	${SRC}
	gcc -o main.o -c $(SRC) $(CFLAGS)

clean:
	rm -f *o	