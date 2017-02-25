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
#include <sortingutils.h>


void threadlist_sort(struct threadlist* tl){

	/* We sort the threadlist in O(nlogn) time using merge sort */

	struct threadlistnode* head = tl->tl_head;

	/* BASE CASE FOR SORTING: If the list has length of 0 or 1, no need to sort */

		if((head == NULL) || (head->tln_next == NULL)) return;

	/* RECURSIVE CASE */ 

	/*
	 *  (1) The list is split into two lists: one with head "a" and another with head "b"
	 *  To achieve this, we  iterate through the list with a fast pointer and slow pointer
	 */

		struct threadlistnode* slow;
		struct threadlistnode* fast;
		struct threadlistnode* a;
		struct threadlistnode* b;
		 
		 /* When the fast pointer reaches null, slow will be one node behind the middle  */

		 slow = head;
		 fast = head->tln_next;
		 while(fast != NULL){ //When this loop ends b will be at the middle
		 	fast = fast->tln_next;
		 	if(fast->tln_next != NULL){
		 		slow = slow->tln_next;
		 		fast = fast->tln_next;	
		 	}
		 }

		 /* a points to the first node of the first list and b points to the first node of the second list */

		 a = head;
		 b = slow->tln_next;
		 slow->tln_next = NULL;

	/*
	 *  (2) Recursively split into sublists
	 */

		threadlist_sort(&a);
		threadlist_sort(&b);

	/*
	 *  (3) Merge the sorted sublists into one
	 */

		if (a == NULL) return(b);
		else if (b==NULL) return(a);

}

/* Helper function for merge sort. Merges two sorted lists */

struct threadlistnode* threadlist_merge_sorted(struct threadlistnode *a, struct threadlistnode *b){

	/* This function merges two sorted linked lists recurisively in O(n) time */


	/* Base case */

	if (a == NULL) return(b);
	else if (b==NULL) return(a);
 
	struct threadlistnode* result;

	/* Recursive step: We merge whatever node's has highest priority with this node's next and the other node */
	if (a->tln_self->t_priority <= b->tln_self->t_priority)
	{
		result = a;
		result->tln_next = SortedMerge(a->tln_next, b);
	}
	else
	{
		result = b;
		result->tln_next = SortedMerge(a, b->tln_next);
	}

	return(result);

}

/* Function to print lists useful for debugging */

void printthreadlist(struct threadlistnode* head){
	printf(" *** Printing threadlist by priority *** \n \n");

	unsigned int count = 1;
	struct threadlistnode* temp = head;
	while(temp != NULL){
		printf("Node %u: Priority = %u", count, temp->tln_self->t_priority);
		temp = temp->tln_next;
	}

}