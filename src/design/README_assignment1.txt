================================================

CSCI 5103 - GROUP AC

	Kong Yang (Dropped the class)
	Ed Nunez

================================================
README

----------------------------------------
SECTION 1: COMPILING THE SOURCE CODE
----------------------------------------

The steps for compiling the source code is not any different from the steps given in the Programming Assignment 0 document. The main directory of this project contains the directories "root", "src" and a two bash scripts. The script build_everything.sh when called from its existing directory should build everything including the userland and kernel. The build_kernel.sh script only builds the kernel section.

In the CSE Lab machines, perform 'module load os161' prior to building the project.

To run os161 from the virtual machine navigate to the "root" folder and run the command "sys161 kernel".

----------------------------------------
SECTION 2: CHANGING THE SCHEDULERS
----------------------------------------

Three different schedulers were implemented in this project: STATIC_PRIORITY, DYNAMIC_PRIORITY, and MULTI_LEVEL. To change the scheduler in use by the project, open thread.c in a text editor and edit the preprocessor statement '#define SCHEDULE_MODE *' with any of these options:

#define SCHEDULE_MODE STATIC_PRIOIRTY

	or


#define SCHEDULE_MODE DYNAMIC_PRIORITY

	or


#define SCHEDULE_MODE MULTI_LEVEL


There is an aditional parameter that can be changed, and this is the AGING_FREQUENCY. This defines how often aging occurs per each X calls of hardclock(). Example: if AGING_FREQUENCY is set to 2, the age will be updated every other call of hardclock().



----------------------------------------
SECTION 3: RUNNING THE TESTS
----------------------------------------

Three tests were created to prove the correctness of the scheduling methods. They can be found in the file /src/kern/test/schedulerstest.c.

From the os161 prompt, the tests can be run by calling "sch1", "sch2" and "sch3".

The tests were desinged by printing out a unique identifier of a running thread instead of priorities, since we expect priorities to change for part B and C.


Test: [sch1]
------------
This test is mainly intended to proof the correctenss of the threadlist sorting algorithm, used by STATIC_PRIORITY and DYNAMIC_PRIORITY schedulers. It has the following ID and starting priorities associated with each thread:

 <ID, STARTING PRIORITY>
   1         1
   2         2
   3         3
   4         4
   5         9

What is unique about this test is that it schedules the threads in the scattered order 2->4->1->3->5->2->4->[...], and does so 30 times. When running in STATIC, one should see the threads initiated in a scattered order and upon the first call to the scheduler they are quickly reordered and we obtain an output similar to 11111122222333334.

When running this in DYNAMIC, one should see the high priority thread 9 running alongside with the other threads as thread 9 de-ages and is capable of being scheduled.


Test: [sch2]
------------
This test is scheduled with initial priorities in sorted ordered unlike sch1. It is mainly intended to prove the correctness of the aging and deaging operations of the STATIC_PRIORITY and MULTI_LEVEL schedulers. The key value pairs are as follows:

 <ID, STARTING PRIORITY>
   1         1
   2         2
   3         3
   4         4
   5         5
   6         14
   7         16
   8         18
   9         20
   0         22

All of these threads are scheduled in order 30 times.


This test is useful because it has two dispersed groups of priorities, 1-5 being VERY low priorities and 6-10 being VERY high priorities. This large disparity makes it very easy to tell if the aging operations are doing what they should. For both DYNAMIC_PRIORITY and MULTI_LEVEL what we should be observing is an output primarily containing digits 1 through 5, as more threads are scheduled we see a larger amount of threads with IDs 6 through 0 being scheduled.


Test: [sch3]
------------
This test's main purpose is to validate the multiqueue operation of the MULTI_LEVEL scheduler.

 <ID, STARTING PRIORITY>
   1         3
   2         6

   3         14
   4         15
   5         25

   6         26
   7         27
   8         28
   9         29
   0         30

All of these threads are scheduled in order 30 times.

Telling from the <ID, PRIORITY> pairs, we see a very small sized group that belongs in the queue containing 1-10,  we see a medium sized group belonging in the 11-20 queue , and we see a large size group containing threads belonging in the 21+ queue.

As the thread runs, at first we will notice a lot of threads '1' and '2' being scheduled because they belong to the 1-10 queue. Throughout time they will age and get put into lower tier queues allowing the threads in the medium queue to get scheduled more and finally the nodes with initial priorities  larger than 20 have a chance to be scheduled as well.
