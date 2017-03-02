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

void threadlist_bubblesort(struct threadlist* tl);
void threadlist_swap(struct threadlistnode *a, struct threadlistnode *b);

void threadlist_updateage(struct threadlistnode *curthread, struct threadlist *tl);
void threadlist_updateage_multilevel(struct threadlistnode *curthread, struct threadlist *CPU_RQ, struct threadlist *A, struct threadlist *B, struct threadlist *C);
void threadlist_move(struct threadlist* source, struct threadlist* destination, struct thread *t);
void threadlist_migrate(struct threadlist* source, struct threadlist* destination);


void printthreadlist(struct threadlist* tl);
void printfromnode(struct threadlistnode* tln);
#endif /* _SCHEDULINGUTILS_H_ */
