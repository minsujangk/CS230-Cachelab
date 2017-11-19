/**********************************
20160559 장민수
**********************************/

#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int simulateCache (int* hit, int* miss, int* evict, int s, int E, int b, int mem, int size, Cache** cache);


int main (int argc, char* argv[])
{
	//printSummary(0, 0, 0);
	int s, E, b;
	FILE* f;
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-s") == 0) {
			s = atoi(argv[++i]);
		} else if (strcmp(argv[i], "-E") == 0) {
			E = atoi(argv[++i]);
		} else if (strcmp(argv[i], "-b") == 0) {
			b = atoi(argv[++i]);
		} else if (strcmp(argv[i], "-t") == 0) {
			f = fopen(argv[++i], "r");
		}
	}

	Cache** cache = (Cache**) calloc((1 << s), sizeof(Cache*));
	for (int i = 0; i < (1 << s); i++) {
		Cache* cacheT = (Cache*) calloc(E, sizeof(Cache));
		cache[i] = cacheT;
	}
	char inst;
	int mem = 0, size = 0;
	int hit = 0, miss = 0, evict = 0;
	printf("%d %d %d", hit, miss, evict);
	while (fscanf(f, " %c %x,%d", &inst, &mem, &size) != -1) {
		//	printf("%d %d", mem, size);
		if (inst == 'L' || inst == 'S') {
			simulateCache(&hit, &miss, &evict, s, E, b, mem, size, cache);
		}
		else if (inst == 'M') {
			simulateCache(&hit, &miss, &evict, s, E, b, mem, size, cache);
			simulateCache(&hit, &miss, &evict, s, E, b, mem, size, cache);
		}

	}
	printf("%d %d %d", hit, miss, evict);
	printSummary(hit, miss, evict);

	return 0;
}

int simulateCache (int* hit, int* miss, int* evict, int s, int E, int b, int mem, int size, Cache** cache){
	int set = (mem & (((1 << s) - 1) << b)) >> b;
	int tag = (mem & (-1 << (s + b))) >> (s + b);

	printf ("%d %d %d %x %d %d", s, E, b, mem, set, tag);

	for (int i = 0; i < E; i++) {
		if (cache[set][i].tag == tag && cache[set][i].valid == 1) {
			(*hit)++;
			Cache temp = cache[set][i];
			for (; i > 0; i--) {
				cache[set][i] = cache[set][i - 1];
			}
			cache[set][0] = temp;
			printf("hit");
			return 1;
		}

	}

	(*miss)++;
	printf("miss");
	if (cache[set][E - 1].valid == 1) {
		(*evict)++;
		printf("evict");
	}
	for (int i = E - 1; i > 0; i--) {
		cache[set][i] = cache[set][i - 1];
	}
	cache[set][0].tag = tag;
	cache[set][0].valid = 1;

	printf("\n");

	return 1;
}
