Kong Yang
Ed Nunez


PartB
The time unit for this was the hardclocks. It would run every AGE number of hardclocks. The AGE definition could be found at the top of the thread. It would increment or decrement the priority on the cpu threadlist based on whether it was current running in the cpu or if it was ready. Then from there the scheduler from PartA would schedule it.





Test:
[sch1]
This will test the fixed priority scheduler by creating threads with higher priorities first. The schedule() function will correct the run queue so that the priorities closer to one will run first.

[sch2]
This test will create 



[sch3]