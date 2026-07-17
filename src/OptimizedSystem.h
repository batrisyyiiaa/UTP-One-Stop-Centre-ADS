#ifndef OPTIMIZEDSYSTEM_H
#define OPTIMIZEDSYSTEM_H

#include <unordered_map>
#include <string>
#include "Ticket.h"

// One node in the doubly linked list. Holds pointers to both its
// neighbors, which is what allows a node to unlink itself in O(1)
// without needing to know its position in the list.
struct DLLNode {
    Ticket ticket;
    DLLNode* prev;
    DLLNode* next;

    DLLNode(const Ticket& t) : ticket(t), prev(nullptr), next(nullptr) {}
};

// Optimized: a Doubly Linked List (preserves FIFO order) combined with
// a Hash Map (token -> node pointer). The hash map lets us jump
// STRAIGHT to any ticket's node without scanning the list at all --
// this is what makes cancellation O(1) instead of O(N).
//
// Uses sentinel head/tail nodes (dummy nodes that are never removed)
// so insert/remove logic never has to special-case an empty list or
// the ends of the list with null-pointer checks.
class OptimizedSystem {
private:
    DLLNode* head; // sentinel -- head->next is the actual front of the queue
    DLLNode* tail; // sentinel -- tail->prev is the actual back of the queue
    std::unordered_map<std::string, DLLNode*> tokenMap;
    int count;

public:
    OptimizedSystem();
    ~OptimizedSystem(); // cleans up all nodes, including sentinels

    void enqueue(const Ticket& ticket);      // O(1)
    Ticket dequeue();                         // O(1)
    bool cancelTicket(const std::string& token); // O(1) via hash map lookup
    bool isEmpty() const;
    int size() const;
};

#endif