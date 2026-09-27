
all: scanit.exe compute.exe

token.o: token.c token.h
	gcc -c token.c

scan.o: scan.c scan.h token.h
	gcc -c scan.c

scanit.o: scanit.c scan.h token.h
	gcc -c scanit.c

scanit.exe: scanit.o scan.o token.o
	gcc -o scanit.exe scanit.o scan.o token.o

compute.o: compute.c scan.h token.h
	gcc -c compute.c

compute.exe: compute.o scan.o token.o
	gcc -o compute.exe compute.o scan.o token.o

clean:
	rm *.exe *.o

test1: test1.txt
	./scanit.exe test1.txt
	./compute.exe test1.txt

test2: test2.txt
	./scanit.exe test2.txt
	./compute.exe test2.txt

test3: test3.txt
	./scanit.exe test3.txt
	./compute.exe test3.txt
