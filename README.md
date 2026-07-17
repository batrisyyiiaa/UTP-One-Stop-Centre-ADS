# UTP OSC Queue Management System

TEB1113 Algorithm and Data Structure group project.

Re-engineers the queue system used at the UTP One Stop Centre (OSC), which currently relies on a manual paper ticketing process. We compare a baseline array based queue against an optimized queue built with a Doubly Linked List and a Hash Map.

## Problem

Students take a paper ticket and wait for their number to be called. If a student leaves without being served, there is no way to update the queue. Staff only find out when they call the number and nobody responds, which wastes time during busy periods.

## Baseline System

A plain array based queue.

- Enqueue: O(1) amortized
- Dequeue: O(N), shifting elements after removal
- Cancel by ticket number: O(N), requires scanning the array to find the ticket

The baseline has no real cancellation feature for students. The demo shows what actually happens when a ticket is abandoned (a no-show), and separately shows the cost if a staff member manually removes a ticket after being told in person.

## Optimized System

A Doubly Linked List combined with a Hash Map (token to node pointer).

- Enqueue: O(1)
- Dequeue: O(1)
- Cancel by token: O(1), the hash map finds the node directly, no scanning required

This is what makes self-service cancellation from a phone actually possible.

## Project Structure

```
src/
  Ticket.h              Ticket data model
  BaselineSystem.h/.cpp Array based queue
  OptimizedSystem.h/.cpp Doubly Linked List + Hash Map queue
  main.cpp              Demo comparing both systems
  benchmark.cpp          Performance test across increasing queue sizes
```

## How to Run

Demo:
```
g++ -std=c++17 src/main.cpp src/BaselineSystem.cpp src/OptimizedSystem.cpp -o demo
./demo
```

Benchmark:
```
g++ -std=c++17 -O2 src/benchmark.cpp src/BaselineSystem.cpp src/OptimizedSystem.cpp -o benchmark
./benchmark
```

On Windows, run `.\demo` and `.\benchmark` instead.

## Prototype

A working prototype (queue display screen and phone based ticket view) is included separately as `prototype.html`. It can be opened directly in any browser, no server or installation needed.
