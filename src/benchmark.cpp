#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include "Ticket.h"
#include "BaselineSystem.h"
#include "OptimizedSystem.h"

int main() {
    std::vector<int> testSizes = {100, 1000, 5000, 10000, 50000};

    std::cout << std::left
               << std::setw(12) << "Tickets"
               << std::setw(28) << "Baseline Cancel (mid-queue)"
               << "Optimized Cancel (mid-queue)\n";
    std::cout << std::string(70, '-') << "\n";

    for (int size : testSizes) {
        // ---------- Baseline ----------
        BaselineSystem baseline;
        for (int i = 1; i <= size; i++) {
            baseline.enqueue(Ticket(i, "Student" + std::to_string(i),
                                     "token-" + std::to_string(i), "Sticker Registration"));
        }
        int middleTicket = size / 2;

        auto startBaseline = std::chrono::high_resolution_clock::now();
        baseline.cancelTicket(middleTicket);
        auto endBaseline = std::chrono::high_resolution_clock::now();
        double baselineMs = std::chrono::duration<double, std::milli>(endBaseline - startBaseline).count();

        // ---------- Optimized ----------
        OptimizedSystem optimized;
        for (int i = 1; i <= size; i++) {
            optimized.enqueue(Ticket(i, "Student" + std::to_string(i),
                                      "token-" + std::to_string(i), "Sticker Registration"));
        }
        std::string middleToken = "token-" + std::to_string(middleTicket);

        auto startOptimized = std::chrono::high_resolution_clock::now();
        optimized.cancelTicket(middleToken);
        auto endOptimized = std::chrono::high_resolution_clock::now();
        double optimizedMs = std::chrono::duration<double, std::milli>(endOptimized - startOptimized).count();

        std::cout << std::left
                   << std::setw(12) << size
                   << std::setw(28) << (std::to_string(baselineMs) + " ms")
                   << (std::to_string(optimizedMs) + " ms") << "\n";
    }

    std::cout << "\nBaseline: O(N) -- scans to find the ticket, then shifts every\n";
    std::cout << "          subsequent ticket down by one position.\n";
    std::cout << "Optimized: O(1) -- hash map jumps straight to the node, then\n";
    std::cout << "           only 2 pointers are reassigned. Stays fast\n";
    std::cout << "           regardless of how many tickets are in the queue.\n";

    return 0;
}