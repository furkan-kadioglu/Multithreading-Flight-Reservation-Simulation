# Multithreading-Flight-Reservation-Simulation
Multithreading and Synchronization exercise
## Introduction
In this project, I have implemented a simple flight reservation system. This program runs as multi-threaded by taking the synchronization issues into consideration. The scenario of the flight reservation system is that the clients arrive for seat reservation, and the program reserves the seats for them. The requirements, operations, and flow of the program are as follows:

1. The program will take an integer as argument (e.g., “./a.out 60”), between 50 and 100 (including both 50 and 100). This value represents the total number of seats that are available within the plane.
2. Upon execution, the program generates clients as separate threads, one client for each seat. The client threads are created by the main thread sequentially, without any waiting time. However, each client thread sleeps for a random time (between 50-200 milliseconds, including both 50 and 200) upon creation. Then, the client thread can start execution.
3. A server thread is created immediately when a client arrives in order to provide service to it.
4. After the creation of a client-server pair and random sleep time, the client requests a random seat for reservation among the available ones at that time.
5. If that request is successfully handled by the server thread, the seat is marked as reserved, by noting the client number (such as: Client1, Client39 etc. Note that client numbers are sorted by their arrival times.)
6. If the requested seat is not available, the client generates another request, again with a random selection of seat until it reserves one.
7. The main thread waits until all of the seats are reserved and it prints out the seat-ID pairs for each seat within the plane.
8. The important thing here is the conditions when two different clients request the same seat at the same time.

I have implemented this program in C/C++ and it is compiled by gcc/g++. 
## Details of Implementation
I have used POSIX threads provided by Linux-based systems or macOS for the implementation of this project in order to create a multi-threaded environment (Windows is not allowed).


The executable takes an integer argument that varies between 50 and 100, including both. This argument represents the number of total seats that are available within the plane. 

When the program starts executing, the clients start to arrive. Each client is represented as a separate thread within the process. Besides, there is another rule for the client operations. The main thread creates the client threads sequentially. In other words, the clients arrive one by one, without any waiting time between. However, after creating a client thread, the client sleeps (or waits) for a random time, which varies between 50-200 milliseconds (including both 50 and 200). I have taken a random sleep time for each client, not just one time. As an example case, after the first client arrives, this client waits, let’s say 63 milliseconds, before starting execution. After creating the first client thread, the second one is created immediately, and the second client waits, 52 milliseconds according to the random number generator.

For each client thread creation, the program creates its peer as a server thread (note that server is not a separate program, it is just a thread to serve the client’s request). After the creation of client/server threads and random sleep time, the client randomly selects a seat, among the ones that have not been reserved yet. By considering the synchronization issues, if that request is satisfied by its server thread, the seat is marked as reserved, and the client number is noted. For example, suppose that Client20 requests for Seat23. If it is available and there is no critical section issue, the server marks Seat23 as reserved by Client20.

After the request of a client is handled and its seat is reserved, both the client and the server threads exit. Here is an important case that I have considered: For instance, Client45 checks the available seats and randomly selects Seat67 for a reservation. After selecting this seat, suppose that the client thread is preempted from the CPU, and another client (Client68) arrives. Surprisingly, it chooses Seat67 for a possible reservation, and since it is still available (i.e., it is not reserved by another client), the server thread reserves Seat67 for Client68, and they exit. Then, Client45 takes the CPU again, but its previous choice is no more available since it is reserved by another client (Client68).

I have handled such cases. If a client chooses a seat for reservation, it is not reserved by another client even it is still not reserved by the server thread. Considering the previous example, after Client45 chooses Seat67 as a possible reservation, even if it is preempted before reservation, Client68 cannot choose it for possible reservation. The program handles this scenario.

During reservation and progress of the program, I have logged the reservations to an external file which is named as output.txt. The program continues to operate until all seats are reserved. Upon completion, the program exits.

A sample of output.txt file:
```bash
Number of total seats: 78 
Client1 reserves Seat33 
Client2 reserves Seat44 
Client4 reserves Seat1 
Client3 reserves Seat76
...
...
All seats are reserved.
```

The output log and the lines are sorted according to the reservation time, not client arrival time. Since the clients wait for a random time upon creation, the arrival order and reservation order may not be the same. For example, Client3 arrives before Client4 but Client4 reserves a seat before Client3 in the example case of output.txt above. It may be due to either OS scheduling or the random sleep times. Besides, the last line of the output.txt (“All seats are reserved”) are written by the main thread of the program, not by any other thread since it represents the end of the program.

The seat number starts from Seat1, I have not created a seat named as Seat0. Same applies for the clients. The client to arrive first is named as Client1. The output.txt is created in the directory where the main function resides.
