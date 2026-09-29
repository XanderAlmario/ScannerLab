
all: scanit.exe rdparse.exe

token.o: token.c token.h
	gcc -c token.c

scan.o: scan.c scan.h token.h
	gcc -c scan.c

scanit.o: scanit.c scan.h token.h
	gcc -c scanit.c

scanit.exe: scanit.o scan.o token.o
	gcc -o scanit.exe scanit.o scan.o token.o

rdparse.o: rdparse.c scan.h token.h
	gcc -c rdparse.c

rdparse.exe: rdparse.o scan.o token.o
	gcc -o rdparse.exe rdparse.o scan.o token.o

clean:
	rm *.exe *.o

test1: test1.txt
	./scanit.exe test1.txt

test2: test2.txt
	./scanit.exe test2.txt

test3: test3.txt
	./scanit.exe test3.txt

