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

void threadlist_sort(struct threadlistnode* head);
struct threadlistnode* threadlist_merge_sorted(struct threadlistnode* a, struct threadlistnode* b);
void printthreadlist(struct threadlist* tl);

#endif /* _SCHEDULINGUTILS_H_ */
