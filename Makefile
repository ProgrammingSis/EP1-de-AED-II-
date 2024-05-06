CFLAGS = -Wall -std=c99

mat: ep1_matriz
lis: ep1_lista

ep1_matriz: CFLAGS+=-DMATRIZ

ep1_matriz: build/grafo_matrizadj.o build/ep_14677190.o
	gcc $(CFLAGS) -o ep build/grafo_matrizadj.o build/ep_14677190.o

build/grafo_matrizadj.o: grafo_matrizadj.c grafo_matrizadj.h
	gcc $(CFLAGS) -c grafo_matrizadj.c -o build/grafo_matrizadj.o

clean:
	rm -f *.o *.exe
	rm -f build/*.o

ep1_lista: build/grafo_listaadj.o build/ep_14677190.o
	gcc $(CFLAGS) -o ep build/grafo_listaadj.o build/ep_14677190.o


build/grafo_listaadj.o: grafo_listaadj.c grafo_listaadj.h
	gcc $(CFLAGS) -c  grafo_listaadj.c -o build/grafo_listaadj.o

build/ep_14677190.o: ep_14677190.c grafo_matrizadj.h  grafo_listaadj.h
	gcc $(CFLAGS) -c  ep_14677190.c -o build/ep_14677190.o
