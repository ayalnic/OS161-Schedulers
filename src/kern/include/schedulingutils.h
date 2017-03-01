#ifndef _SCHEDULINGUTILS_H_
#define _SCHEDULINGUTILS_H_

/*
 * SORTING UTILTIIES
 *
 * Used for sorting threadlist
 *
 */


#include <types.h>
#include <lib.h>
#include <thread.h>
#include <threadlist.h>

// struct thread;	/* from <thread.h> */
// struct threadlistnode; /* from <threadlist.h> */
// struct threadlist; /* from <threadlist.h> */

void threadlist_sort(struct threadlist* tl);
void threadlist_bubblesort(struct threadlistnode** firstRef, unsigned int size);
void threadlist_swap(struct threadlistnode *a, struct threadlistnode *b);
void threadlist_updateage(struct threadlistnode *curthread, struct threadlist *tl);


void threadlist_mergesort(struct threadlistnode** firstRef);
struct threadlistnode* threadlist_merger(struct threadlistnode* a, struct threadlistnode* b);
void printthreadlist(struct threadlist* tl);
void printfromnode(struct threadlistnode* tln);
#endif /* _SCHEDULINGUTILS_H_ */
