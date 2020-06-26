#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

#define MAX 	10000
#define SIZE 	200

typedef Pair Type;

typedef struct heap {
	Type vector[MAX];
	int size;
	int capacity;
	int (*compare_func)(const void*, const void*);
} *Heap;

/**
*	Inițializează cu 0 dimensiunea heap-ului și atribuie valoarea pentru
* funcția generică de comparare.
*	De asemenea, alocă și memorie pentru structura heap.
**/
Heap initHeap(int (*compare_func) (const void*, const void*));

/**
*	Funcții auxiliare care realizează "cernerea" pentru a menține proprie-
* tățile structurii de date.
**/
Heap siftDown(Heap h, int index);
Heap siftUp(Heap h, int index);
Heap swapAndSiftDown(Heap h, int parent, int child);

/**
*	Introduce un element în heap și realizează "cernerea" pentru asigura-
* rea respectării proprietăților de maxHeap.
**/
Heap insertHeap(Heap h, Type element);

/**
*	Extrage elementul maxim din heap (rădăcina heap-ului).
**/
Type* extractMax(Heap h);

/**
*	Funcție care dealoca memoria alocată pentru structura de date.
**/
Heap freeHeap(Heap h);

#endif /* HEAP_H */
