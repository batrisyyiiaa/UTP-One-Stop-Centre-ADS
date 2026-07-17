#include <iostream>
#include <chrono>
#include "Ticket.h"
#include "BaselineSystem.h"
#include "OptimizedSystem.h"

int main() {
    std::cout << "=========================================================\n";
    std::cout << " BASELINE SYSTEM (Array-based queue)\n";
    std::cout << "=========================================================\n";

    BaselineSystem baseline;
    for (int i = 1; i <= 6; i++) {
        baseline.enqueue(Ticket(i, "Student" + std::to_string(i),
                                 "token-" + std::to_string(i), "Sticker Registration"));
    }
    std::cout << "6 tickets enqueued. Queue size: " << baseline.size() << "\n";

    std::cout << "\nStudent with Ticket #3 leaves the premises and cancels\n";
    std::cout << "from their phone (a 'ghost ticket' being cleaned up)...\n";

    bool cancelled = baseline.cancelTicket(3);
    std::cout << "Cancelled: " << (cancelled ? "yes" : "no")
               << " | Queue size now: " << baseline.size() << "\n";
    std::cout << "(Internally: every ticket after #3 was shifted down one\n";
    std::cout << "position in the array -- an O(N) operation.)\n";

    std::cout << "\n\n=========================================================\n";
    std::cout << " OPTIMIZED SYSTEM (Doubly Linked List + Hash Map)\n";
    std::cout << "=========================================================\n";

    OptimizedSystem optimized;
    for (int i = 1; i <= 6; i++) {
        optimized.enqueue(Ticket(i, "Student" + std::to_string(i),
                                  "token-" + std::to_string(i), "Sticker Registration"));
    }
    std::cout << "6 tickets enqueued. Queue size: " << optimized.size() << "\n";

    std::cout << "\nStudent with token \"token-3\" cancels from their phone...\n";

    cancelled = optimized.cancelTicket("token-3");
    std::cout << "Cancelled: " << (cancelled ? "yes" : "no")
               << " | Queue size now: " << optimized.size() << "\n";
    std::cout << "(Internally: the hash map found the node instantly, then\n";
    std::cout << "only 2 pointers were reassigned -- an O(1) operation,\n";
    std::cout << "regardless of how many tickets are in the queue.)\n";

    std::cout << "\nRemaining queue, served in order:\n";
    while (!optimized.isEmpty()) {
        Ticket next = optimized.dequeue();
        std::cout << "  Serving Ticket #" << next.ticketNumber
                   << " (" << next.studentId << ")\n";
    }
    std::cout << "\nNote: Ticket #3 does not appear above -- it was cancelled.\n";

    return 0;
}