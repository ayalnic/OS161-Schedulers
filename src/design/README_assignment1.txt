Kong Yang
Ed Nunez

PartA Static Priority


PartB Dynamic Priority
The time unit for this was the hardclocks. It would run every AGE number of hardclocks. The AGE definition could be found at the top of the thread. It would increment or decrement the priority on the cpu threadlist based on whether it was current running in the cpu or if it was ready. Then from there the scheduler from PartA would schedule it.

PartC Multi-level feedback


Test:
[sch1]

[sch2]




[sch3]
This thread will create threads unique priorities 1 - 30. Then the scheduler should run the threads in their respective queue in a round robin.