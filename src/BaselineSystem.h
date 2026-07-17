#ifndef BASELINESYSTEM_H
#define BASELINESYSTEM_H

#include <vector>
#include "Ticket.h"

// Baseline: a simple array-backed queue, matching how a naive kiosk
// ticket system would work. Enqueue/dequeue at the ends are fast, but
// cancelling a ticket from the MIDDLE of the queue (a student cancels
// via their phone while away from the counter) requires:
//   1. A linear scan to find the ticket -- O(N)
//   2. Shifting every subsequent element down to fill the gap -- O(N)
class BaselineSystem {
private:
    std::vector<Ticket> tickets;

public:
    void enqueue(const Ticket& ticket);       // O(1) - amortized, add to back
    Ticket dequeue();                          // O(1) - remove from front
    bool cancelTicket(int ticketNumber);       // O(N) - scan + shift
    bool isEmpty() const;
    int size() const;
};

#endif