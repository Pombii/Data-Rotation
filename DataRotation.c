#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct DNode {
	int data;																							//Creates my struct for my nodes and queue pointers
	struct DNode* next;
	struct DNode* prev;
};

struct Queue {
	DNode* head;
	DNode* last;
};

void queueinit(Queue* lq);
void reorderlist(Queue* rq, FILE* outfile);
void Insertendlist(Queue* iq, int d);

int main()
{
	FILE* fin, *fout;
	Queue myqueue;
	int filedata;
	fin = fopen("C:\\Users\\corti\\Documents\\INFILE.txt", "r");
	fout = fopen("C:\\Users\\corti\\Documents\\OUTFILE.txt", "w");
	
	queueinit(&myqueue);

	if (fin == NULL) {
		printf("ehhh");
		return -1;
	}

	while (!feof(fin))
	{
		fscanf(fin, "%d", &filedata);																					//Reads data from my in file
		Insertendlist(&myqueue, filedata);
	}
	reorderlist(&myqueue, fout);
	return 0;
}


void queueinit(Queue* lq) {
	lq->head = NULL;
	lq->last = NULL;																						//Initialize queue
}

void Insertendlist(Queue* iq, int d) {
	DNode* myn = (DNode*)malloc(sizeof(DNode));
	if (myn == NULL) {
		printf("No memory!");
		exit(1);
	}

	myn->data = d;

	if (iq->head == NULL) {																						//Reads the data from file then place in list
		myn->next = myn->prev = NULL;
		iq->head = iq->last = myn;
	}
	else {
		myn->prev = iq->last;
		myn->next = NULL;
		iq->last->next = myn;
		iq->last = myn;
	}
}

void reorderlist(Queue* rq, FILE* outfile) {
	DNode* n; 
	DNode* ln; 

	do {
		n = rq->head;
		ln = rq->last;
		fprintf(outfile, "%d ", n->data);
		fprintf(outfile, "%d ", ln->data);
		rq->head = n->next;																							//Prints first then last element in list
		rq->last = ln->prev;
		
		if (rq->head == rq->last) {
			fprintf(outfile, "%d ", rq->head->data);
		}
	} while (rq->head != rq->last);
}
