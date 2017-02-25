#ifndef _SORTINGUTILS_H_
#define _SORTINGUTILS_H_

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

void threadlist_sort(struct threadlistnode* head);

struct threadlistnode* threadlist_merge_sorted(struct threadlistnode *a, struct threadlistnode *b);

void printthreadlist(struct threadlistnode* head);

#endif /* _SORTINGUTILS_H_ */
