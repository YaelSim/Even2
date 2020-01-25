# Even2
Linoy and Yael - Second part of project - EVEN2
Submission Date: 01/30/2020

Hello readers!

## General Description

The Goal - Creating a server that will handle multiple clients and will solve different problems. This shall be achieved
using the SOLID principles, and by implementing serveral [Design Patterns](https://en.wikipedia.org/wiki/Software_design_pattern).

The project is based on several main components:
1. Deep understanding of programming in a multi-threaded environment.

2. Taking advantage of OOP's polymorphism - We created several classes according to the UML diagram receieved.
Each class implements an important part of the logical proccess. For intance:
    Server - a class that will function as a server (a parallel/ serial one, accordingly)
    ClientHandler - a class that will manage resolving problems with a given algorithm, and will return the solution to the client.
    DFS, BFS, AStar, BestFirstSearch - Those are the search algorithms that were implemented.

3. Full understand of CPP syntax, including data structures, libraries etc. This entire project is written in CPP.

4. Full understand of CPP [templates](https://www.geeksforgeeks.org/templates-cpp/).

5.  Understanding the [Adapter](https://www.geeksforgeeks.org/adapter-pattern/) design pattern in CPP: This DP is neccessary
in order to connect between the Solver and the Searcher interfaces.

6. Understanding the [Bridge](https://www.geeksforgeeks.org/bridge-design-pattern/) design pattern in CPP: This DP was neccessary in order to seperate the different search
algorithms and the problem it was meant to solve.

7. Understanding and Taking advantage of storing different solutions in Files (Caching).
 
 
 
 
 # Explenations and Usages

## MyParallelServer, MySerialServer
Those are classes that implement the Server interface. Each of them handles clients differently;
The serial server accepts and handles clients one by one. On the other hand, the parallel server accepts and handles
clients at the same time.


## MyTestClientHandler, StringReverser
MyTestClientHandler is used within the serial server. It receives a string line and creates a StringReverser that will reverse
the string given. The reversed string will then be returned to MyTestClientHandler and later on, to the client.


## Matrix
This is a class that implements the Searchable<T> interface (with string as T). By creating this class, we are able to define
a search problem on a graph (matrix) given on part C. We'll be able to return a shortest path from one cell of the matrix
to another cell.


## MyClientHandler, ObjectAdapter
This is a class that is used within the parallel server. It will create an ObjectAdapter and set its' algorithm to [AStar](https://www.geeksforgeeks.org/a-search-algorithm/)
MyClientHandler will set the ObjectAdapter creates as its' solver. By doing so, we make sure the OA will be the responsible component
that will solve, store, and return a problem-matched solution.
This solution recieved will be sent to the client.


## CacheManager, FileCacheManager
The FileCacheManager implements the CacheManager interface. Everytime our Solver is asked to solve a problem, we will first check if a solution
to this specific problem already exists in our filesystem. If so, we don't have to solve this problem again, what saves us precious runtime.
The already-cached-saved solution will be returned to the client (using MyClientHandler).



Thanks for reading!
Yael and Linoy :)



