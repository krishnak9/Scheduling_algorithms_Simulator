# Scheduling_algorithms_Simulator
A simulator C program which emulates the process queue according to the algorithm used.

#How to use:

1. Clone this repository. 
2. Compile the algorithm to use for simulation by using command "gcc -o sjfemulator simulation_sjf.c".<br>
    (For fcfs algo use simulation_fcfs.c)<br>
3. Prepare input text file having processes in format.<br>
  
  Processno Arrival-time Burst-time(this line should not be included)<br>
    P1 0 1<br>
    P2 0 7<br>
    P3 1 4<br>
    P4 1 3<br>
    P5 2 2<br>
4. Run the program using command "./sjfemulator".<br>
5. Enter input filename.<br>
6. Simulated process sequence will be produced.

