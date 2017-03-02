Kong Yang
Ed Nunez

PartA Static Priority
We sorted the cpu run queue using bubble sort. We chose this sorting algorithm because it was the only one we were able to implement. However, under low number of threads the sorting algorithm does not suffer terribly. The sorting algorithm would be called everytime schedule() was called; after being sorted the cpu would pick out the thread that was placed in the front of the queue. For the first few cycles, schedule is not called, so the first few threads run like a FIFO scheduler. 

We first tried to implment this using merge sort, however we were unable to correctly implement this. However, with mergesort we would ideally be able to handle large number of threads without suffering too much of a time penalty that the bubble sort would suffer through.


PartB Dynamic Priority
The time unit for this was the hardclocks. It would run every AGE number of hardclocks. The AGE definition could be found at the top of the thread. It would increment or decrement the priority on the cpu threadlist based on whether it was current running in the cpu or if it was ready. Then from there the scheduler from PartA would schedule it.


PartC Multi-level feedback




Test:
[sch1]
The test will create threads with increasing priorities. The static priority scheduler will not be affected by this one too much, it will simply run like a FIFO. The dynamic priority scheduler will move all the threads to the median and then they will all run in a round robin. The multi-level feedback will run the first 10, then the second 10 and then any remainer, this will also age, so threads will jump between the queues.


[sch2]
This will create a random assortment of threads with different or same priorities. The static priority and dynamic priorities will sort them and then run the threads respectively. The multi-level feedback scheduler will sort out these threads into their respective queues and then run them based off of the queue priorities.


[sch3]
15 threads will have priority 5 and 15 will have priority 25. Static will run all the threads with priortiy 5 first and then the ones with priority 25. Dynamic will make all the threads converge to some priority level. The multi-level feedback will run all the ones with 5 first and then some of them will move to the second queue, also some of the threads with priority 25 will move down the the second queue.