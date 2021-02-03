proj4: main.o doFuncts.o linkedList.o
	gcc -o proj4 main.o doFuncts.o linkedList.o

main.o: main.c proj4.h
	gcc -c main.c

doFuncts.o: doFuncts.c proj4.h
	gcc -c doFuncts.c

linkedlist.o: linkedlist.c proj4.h
	gcc -c linkedlist.c

clean:
	rm main.o doFuncts.o linkedlist.o proj4
