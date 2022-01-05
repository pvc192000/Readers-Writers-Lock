all:
	gcc -o rwmain main.c readerwriter.c -Wall -pthread

main.o:
	readerwriter.h main.c

readerwriter.o:
	readerwriter.h readerwriter.c

clean:
	rm -rf *o rwmain
