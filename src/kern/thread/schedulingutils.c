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


void threadlist_bubblesort(struct threadlist* tl){
	//putch('B');putch('e');putch('f');putch('o');putch('r');putch('e');putch(':');putch('\n'); printfromnode(tl->tl_head.tln_next);
	if(tl->tl_count  < 2){
		// kprintf("\nThreadlist contains less than two nodes. No need to sort \n");
		return;
	}

	struct threadlistnode* firstNode = tl->tl_head.tln_next;
	struct threadlistnode* current;
	unsigned int size = tl->tl_count;
	unsigned int i,j;

	for(i=0; i<size; i++){
		current = firstNode;
		for(j=1; j<size-i; j++){
			if(current->tln_self->t_priority >= current->tln_next->tln_self->t_priority){
				threadlist_swap(current, current->tln_next);
				if(current == firstNode) firstNode = current->tln_prev;
			}
			else current = current->tln_next;
		}
	}

	//putch('A');putch('f');putch('t');putch('e');putch('r');putch(':');putch('\n'); printfromnode(tl->tl_head.tln_next);
}

void threadlist_swap(struct threadlistnode* a, struct threadlistnode* b){
	a->tln_next = b->tln_next;
	b->tln_prev = a->tln_prev;
	a->tln_prev->tln_next = b;
	b->tln_next->tln_prev = a;
	b->tln_next = a;
	a->tln_prev = b;
}


void threadlist_updateage(struct threadlistnode *curthread, struct threadlist *tl){
	// increment the thread in the cpu
	if(curthread->tln_self->t_priority < 0xFFFF)
	{
		++(curthread->tln_self->t_priority);
	}

	printthreadlist(tl);

	if(tl->tl_count <= 1){return;} // List has less than 1 element

	struct threadlistnode *temp = tl->tl_head.tln_next;
	while(temp->tln_self != NULL){
				if(temp->tln_self->t_priority > 0x0000)
				{
					--(temp->tln_self->t_priority);
				}
		temp = temp->tln_next;
	}

	printthreadlist(tl);

}


void threadlist_updateage_multilevel(struct threadlistnode *curthread, struct threadlist* A, struct threadlist* B, struct threadlist* C){

	// increment the thread in the cpu
	if(curthread->tln_self->t_priority < 0xFFFF)
	{
		++(curthread->tln_self->t_priority);
	}

	// decrease the priority for threadlistA, and check if each node belongs there
	struct threadlistnode* temp = A->tl_head.tln_next;
	while(temp->tln_self != NULL)
	{
		if(temp->tln_self->t_priority > 0x0000) {--(temp->tln_self->t_priority);}

		if(temp->tln_self->t_priority > 20){
			threadlist_move(A, B, temp);
		}
		else if(temp->tln_self->t_priority > 10){
			threadlist_move(A, C, temp);
		}
		temp = temp->tln_next;
	}

	// decrease the priorities for threadlistB
	temp = B->tl_head.tln_next;
	while(temp->tln_self != NULL)
	{
		if(temp->tln_self->t_priority > 0x0000) {--(temp->tln_self->t_priority);}

		if(temp->tln_self->t_priority <= 10){
			threadlist_move(B, A, temp);
		}
		else if(temp->tln_self->t_priority > 20){
			threadlist_move(B, C, temp);
		}
		temp = temp->tln_next;
	}

	// decrease the priorities for threadlistC
	temp = C->tl_head.tln_next;
	while(temp->tln_self != NULL)
	{
		if(temp->tln_self->t_priority > 0x0000) {--(temp->tln_self->t_priority);}

		if(temp->tln_self->t_priority <= 10){
			threadlist_move(C, A, temp);
		}
		else if(temp->tln_self->t_priority <= 20){
			threadlist_move(C, B, temp);
		}
		temp = temp->tln_next;
	}
}


void threadlist_move(struct threadlist* source, struct threadlist* destination, struct threadlistnode *sourceNode){
	threadlist_remove(source, sourceNode->tln_self);
	threadlist_addtail(destination, sourceNode->tln_self);
}


/* Function to print lists useful for debugging */
void printthreadlist(struct threadlist* tl){

	kprintf("\n\n*************************** Printing threadlist *************************** \n");
	kprintf("Number of nodes in this list = %u \n" , tl->tl_count);

	if(threadlist_isempty(tl)){
		kprintf("\n Threadlist is empty. No nodes to show \n");
	}
	else{
		unsigned int count = 1;
		struct threadlistnode *temp = tl->tl_head.tln_next;

		kprintf("Printing threads in threadlist...\n");
		while(temp->tln_self != NULL){
			kprintf("Node#%u: Priority = %u \n", count++, temp->tln_self->t_priority);
			temp = temp->tln_next;
		}
	}

	kprintf("\n****************************************************************** \n\n");
}

void printfromnode(struct threadlistnode* tln){

	struct threadlistnode* temp = tln;
	while(temp->tln_self != NULL){
		char priority = temp->tln_self->t_priority + '0';
		putch(priority);
		putch(' '); putch('-'); putch('>'); putch(' ');
		temp = temp->tln_next;
	}
	putch('\n');
}
