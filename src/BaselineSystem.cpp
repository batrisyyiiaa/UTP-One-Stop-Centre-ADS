#include "BaselineSystem.h"
#include <stdexcept>
#include <algorithm>

void BaselineSystem::enqueue(const Ticket& ticket) {
    tickets.push_back(ticket);
}

Ticket BaselineSystem::dequeue() {
    if (tickets.empty()) {
        throw std::runtime_error("No tickets in queue.");
    }
    Ticket next = tickets.front();
    tickets.erase(tickets.begin()); // O(N) -- everything shifts down by one
    return next;
}

bool BaselineSystem::cancelTicket(int ticketNumber) {
    // Step 1: linear scan to find the ticket -- O(N)
    int index = -1;
    for (size_t i = 0; i < tickets.size(); i++) {
        if (tickets[i].ticketNumber == ticketNumber) {
            index = static_cast<int>(i);
            break;
        }
    }

    if (index == -1) {
        return false; // not found
    }

    // Step 2: shift every element after it down by one -- O(N)
    tickets.erase(tickets.begin() + index);
    return true;
}

bool BaselineSystem::isEmpty() const {
    return tickets.empty();
}

int BaselineSystem::size() const {
    return tickets.size();
}