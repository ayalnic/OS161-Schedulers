/*
 * SORTING UTILTIIES
 *
 * Used for sorting threadlists, aging, and working with multi-level queues
 *
 */


#include <types.h>
#include <lib.h>
#include <thread.h>
#include <threadlist.h>
#include <schedulingutils.h>


void threadlist_sort(struct threadlistnode* head){

	/* We sort the threadlist in O(nlogn) time using merge sort */

	/* BASE CASE FOR SORTING: If the list has length of 0 or 1, no need to sort */

		if((head->tln_self == NULL) || (head->tln_next->tln_self == NULL)) return;


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
		while(fast->tln_self != NULL){ //When this loop ends b will be at the middle
			fast = fast->tln_next;
			if(fast->tln_next->tln_self != NULL){
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

		threadlist_sort(a);
		threadlist_sort(b);

	// /*
	//  *  (3) Merge the sorted sublists into one
	//  */

	threadlist_merge_sorted(a,b);

}

/* Helper function for merge sort. Merges two sorted lists */

struct threadlistnode* threadlist_merge_sorted(struct threadlistnode* a, struct threadlistnode* b){

	/* This function merges two sorted linked lists recurisively in O(n) time */

	/* Base case */

	if (a->tln_self == NULL) return(b);
	else if (b->tln_self == NULL) return(a);

	struct threadlistnode* result;

	/* Recursive step: We merge whatever node's has highest priority with this node's next and the other node */
	if (a->tln_self->t_priority <= b->tln_self->t_priority)
	{
		result = a;
		result->tln_next = threadlist_merge_sorted(a->tln_next, b);
	}
	else
	{
		result = b;
		result->tln_next = threadlist_merge_sorted(a, b->tln_next);
	}

	return(result);

}

/* Function to print lists useful for debugging */

void printthreadlist(struct threadlist* tl){
	kprintf(" *** Printing threadlist by priority *** \n \n");

	struct threadlistnode* temp = &tl->tl_head;;

	unsigned int count = 1;

	while(temp != NULL){
		kprintf("Node %u: Priority = %u", count++, temp->tln_self->t_priority);
		temp = temp->tln_next;
	}
}


/* Function to decrease a thread's priority by one */

void decreasePriority(struct threadlistnode* node){
	if(node->tln_self->t_priority > 0)
        node->tln_self->t_priority--;
}

void increasePriority(struct threadlistnode* node){
	if(node->tln_self->t_priority < 0xFFFF) 
        node->tln_self->t_priority++;
}
