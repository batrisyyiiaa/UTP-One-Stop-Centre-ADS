#include "OptimizedSystem.h"
#include <stdexcept>

OptimizedSystem::OptimizedSystem() : count(0) {
    // Create sentinel nodes with a placeholder ticket. These are never
    // shown to the user -- they just simplify insert/remove logic by
    // guaranteeing every real node always has a valid prev and next.
    Ticket dummy(-1, "", "", "");
    head = new DLLNode(dummy);
    tail = new DLLNode(dummy);
    head->next = tail;
    tail->prev = head;
}

OptimizedSystem::~OptimizedSystem() {
    DLLNode* current = head;
    while (current != nullptr) {
        DLLNode* next = current->next;
        delete current;
        current = next;
    }
}

void OptimizedSystem::enqueue(const Ticket& ticket) {
    // Insert just before the tail sentinel -- O(1), no scanning needed.
    DLLNode* newNode = new DLLNode(ticket);
    DLLNode* lastActiveNode = tail->prev;

    lastActiveNode->next = newNode;
    newNode->prev = lastActiveNode;
    newNode->next = tail;
    tail->prev = newNode;

    tokenMap[ticket.token] = newNode; // register for O(1) future lookup
    count++;
}

Ticket OptimizedSystem::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("No tickets in queue.");
    }

    // The real front of the queue is head->next -- O(1), no scanning.
    DLLNode* frontNode = head->next;
    Ticket result = frontNode->ticket;

    head->next = frontNode->next;
    frontNode->next->prev = head;

    tokenMap.erase(result.token);
    delete frontNode;
    count--;

    return result;
}

bool OptimizedSystem::cancelTicket(const std::string& token) {
    // Step 1: O(1) hash map lookup -- no scanning the list at all.
    auto it = tokenMap.find(token);
    if (it == tokenMap.end()) {
        return false; // token not found / already served
    }

    DLLNode* nodeToRemove = it->second;

    // Step 2: O(1) pointer re-assignment -- unlink the node directly.
    DLLNode* leftNode = nodeToRemove->prev;
    DLLNode* rightNode = nodeToRemove->next;
    leftNode->next = rightNode;
    rightNode->prev = leftNode;

    // Step 3: clean up.
    tokenMap.erase(it);
    delete nodeToRemove;
    count--;

    return true;
}

bool OptimizedSystem::isEmpty() const {
    return count == 0;
}

int OptimizedSystem::size() const {
    return count;
}