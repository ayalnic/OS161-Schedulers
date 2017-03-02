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
	if(curthread->tln_self!=NULL && curthread->tln_self->t_priority < 0xFFFF)
	{
		++(curthread->tln_self->t_priority);
	}

	//printthreadlist(tl);

	if(tl->tl_count <= 1){return;} // List has less than 1 element

	struct threadlistnode *temp = tl->tl_head.tln_next;
	while(temp->tln_self != NULL){
				if(temp->tln_self->t_priority == S_READY && temp->tln_self->t_priority > 0x0000)
				{
					--(temp->tln_self->t_priority);
				}

				if(temp->tln_self->t_priority == S_RUN && temp->tln_self->t_priority < 0xFFFF)
				{
					++(temp->tln_self->t_priority);
				}

		temp = temp->tln_next;
	}

	//printthreadlist(tl);

}


void threadlist_updateage_multilevel(struct threadlistnode *curthread, struct threadlist* CPU_RQ, struct threadlist* A, struct threadlist* B, struct threadlist* C){

	// increment the thread in the cpu
	if(curthread != NULL && curthread->tln_self->t_priority < 0xFFFF)	{		++(curthread->tln_self->t_priority); }


	struct threadlistnode* nextTemp;
	struct threadlistnode* temp;
	unsigned int i;

	//STEP 1: decrease the priority for all of the threadlists

	if(CPU_RQ->tl_count>0) temp = CPU_RQ->tl_head.tln_next;
	for(i=0; i<CPU_RQ->tl_count; i++)
	{
		nextTemp = temp->tln_next;
		if(temp->tln_self->t_priority > 0) {--(temp->tln_self->t_priority);}
		temp = nextTemp;
	}


	if(A->tl_count>0) temp = A->tl_head.tln_next;
	for(i=0; i<A->tl_count; i++)
	{
		nextTemp = temp->tln_next;
		if(temp->tln_self->t_priority > 0) {--(temp->tln_self->t_priority);}
		temp = nextTemp;
	}

	if(B->tl_count>0) temp = B->tl_head.tln_next;
	for(i=0; i<B->tl_count; i++)
	{
		nextTemp = temp->tln_next;
		if(temp->tln_self->t_priority > 0) {--(temp->tln_self->t_priority);}
		temp = nextTemp;
	}

	if(C->tl_count>0) temp = C->tl_head.tln_next;
	for(i=0; i<C->tl_count; i++)
	{
		nextTemp = temp->tln_next;
		if(temp->tln_self->t_priority <= 10) {--(temp->tln_self->t_priority);}

		temp = nextTemp;
	}

	//STEP 2: Shuffle around the threads to its appropiate location

	threadlist_migrate(CPU_RQ, A); //It doesn't matter if some of the CPU_RQ nodes don't belong in A.

	if(A->tl_count>0) temp = A->tl_head.tln_next;
	for(i=0; i<A->tl_count; i++)
	{
		nextTemp = temp->tln_next;
		if(temp->tln_self->t_priority > 20){
			threadlist_move(A, B, temp->tln_self);
		}
		else if(temp->tln_self->t_priority > 10){
			threadlist_move(A, C, temp->tln_self);
		}
		temp = nextTemp;
	}

	if(B->tl_count>0) temp = B->tl_head.tln_next;
	for(i=0; i<B->tl_count; i++)
	{
		nextTemp = temp->tln_next;
		if(temp->tln_self->t_priority <= 10) {
			threadlist_move(B, A, temp->tln_self);
		}
		else if(temp->tln_self->t_priority > 20){
			threadlist_move(B, C, temp->tln_self);
		}
		temp = nextTemp;
	}

	if(C->tl_count>0) temp = C->tl_head.tln_next;
	for(i=0; i<C->tl_count; i++)
	{
		nextTemp = temp->tln_next;
		if(temp->tln_self->t_priority <= 10) {
			threadlist_move(C, A, temp->tln_self);
		}
		else if(temp->tln_self->t_priority <= 20){
			threadlist_move(C, B, temp->tln_self);
		}
		temp = nextTemp;
	}

}


void threadlist_move(struct threadlist* source, struct threadlist* destination, struct thread *t){
	threadlist_remove(source, t);
	threadlist_addtail(destination, t);
}

void threadlist_migrate(struct threadlist* source, struct threadlist* destination){

	struct thread *t;
	// unsigned int num_to_migrate = source->tl_count;
	if(source->tl_count <= 0){
			//kprintf("\n No nodes to migrate \n");
			return;
	}

	while(!threadlist_isempty(source)){
			t = threadlist_remhead(source);
			threadlist_addtail(destination, t);
	}

	return;
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
<<<<<<< HEAD
		char priority = temp->tln_self->t_priority + '0';
		int pri = temp->tln_self->t_priority;
		if(pri<10){
			putch('0' + priority);
=======
		char priority;
		if (priority < 10)
			priority = temp->tln_self->t_priority + '0';
		else
			priority = temp->tln_self->t_priority + 'A' - 10;
	 	putch(priority);
	 	putch(' '); putch('-'); putch('>'); putch(' ');
	 temp = temp->tln_next;
	}
	putch('\n');
}


void threadlist_updateage(struct threadlistnode *curthread, struct threadlist *tl){

		if(tl->tl_count <= 1){return;} // List has less than 1 element

	//putch('B');putch('4');putch('A');putch('g');putch('e');putch(':');putch('\n'); printfromnode(tl->tl_head.tln_next);

	// increment the thread in the cpu
	if(curthread->tln_self->t_priority < 0xFFFF)
	{
		++(curthread->tln_self->t_priority);
	}

	struct threadlistnode *temp = tl->tl_head.tln_next;
	do{

		if (temp->tln_self->t_state == S_READY){
				if(temp->tln_self->t_priority > 0x0000)
				{
					--(temp->tln_self->t_priority);
				}
>>>>>>> 4a43e6b20f57c3a842b60b0fcd06487eddbc911d
		}
		else{
			putch('A' + priority - 10);
		}
		putch(' '); putch('-'); putch('>'); putch(' ');
		temp = temp->tln_next;
	}
	putch('\n');
}
