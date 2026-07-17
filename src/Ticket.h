#ifndef TICKET_H
#define TICKET_H

#include <string>

struct Ticket {
    int ticketNumber;
    std::string studentId;
    std::string token;       // secure session key, used for O(1) hash map lookup
    std::string serviceType; // e.g. "Sticker Registration", "Student ID Card"

    Ticket(int number, std::string student, std::string tok, std::string service)
        : ticketNumber(number), studentId(std::move(student)),
          token(std::move(tok)), serviceType(std::move(service)) {}
};

#endif