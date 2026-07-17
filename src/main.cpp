#include <iostream>
#include <chrono>
#include "Ticket.h"
#include "BaselineSystem.h"
#include "OptimizedSystem.h"

int main() {
    std::cout << "=========================================================\n";
    std::cout << " BASELINE SYSTEM (Array-based queue, paper kiosk)\n";
    std::cout << "=========================================================\n";

    BaselineSystem baseline;
    for (int i = 1; i <= 6; i++) {
        baseline.enqueue(Ticket(i, "Student" + std::to_string(i),
                                 "token-" + std::to_string(i), "Sticker Registration"));
    }
    std::cout << "6 tickets enqueued. Queue size: " << baseline.size() << "\n";

    std::cout << "\nStudent with Ticket #3 decides not to come anymore.\n";
    std::cout << "The queue is NOT updated in any way:\n";
    std::cout << "Queue size is still: " << baseline.size() << "\n";

    std::cout << "\n--- Staff now begins calling tickets in order ---\n";
    while (!baseline.isEmpty()) {
        Ticket next = baseline.dequeue();
        if (next.ticketNumber == 3) {
            std::cout << "Calling Ticket #3 (" << next.studentId << ")... no response.\n";
        } else {
            std::cout << "Serving Ticket #" << next.ticketNumber << " (" << next.studentId << ")\n";
        }
    }

    BaselineSystem baselineForComparison;
    for (int i = 1; i <= 6; i++) {
        baselineForComparison.enqueue(Ticket(i, "Student" + std::to_string(i),
                                              "token-" + std::to_string(i), "Sticker Registration"));
    }
    bool cancelled = baselineForComparison.cancelTicket(3);
    std::cout << "Manually removed Ticket #3: " << (cancelled ? "yes" : "no") << "\n";
    std::cout << "(Internally: the list was scanned to find #3 -- O(N) -- then\n";
    std::cout << "every ticket after it was shifted down one position -- O(N).)\n";

    std::cout << "\n\n=========================================================\n";
    std::cout << " OPTIMIZED SYSTEM (Doubly Linked List + Hash Map)\n";
    std::cout << "=========================================================\n";

    OptimizedSystem optimized;
    for (int i = 1; i <= 6; i++) {
        optimized.enqueue(Ticket(i, "Student" + std::to_string(i),
                                  "token-" + std::to_string(i), "Sticker Registration"));
    }
    std::cout << "6 tickets enqueued. Queue size: " << optimized.size() << "\n";

    std::cout << "\nStudent with ticket \"3\" cancels from their phone.\n";

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
    std::cout << "\nNote: Ticket #3 does not appear above.\n";

    return 0;
}