#include <iostream>
#include "clsQueueLine.h"

int main()
{
    clsQueueLine PayBillsQueue("A0", 10);
    clsQueueLine SubscriptionsQueue("B0", 5);

    // Issue tickets
    for (int i = 0; i < 5; i++)
        PayBillsQueue.IssueTicket();

    for (int i = 0; i < 3; i++)
        SubscriptionsQueue.IssueTicket();

    // Pay Bills Queue
    std::cout << "\n========== Pay Bills Queue ==========\n";
    PayBillsQueue.PrintInfo();
    PayBillsQueue.PrintTicketsLineRTL();
    PayBillsQueue.PrintTicketsLineLTR();
    PayBillsQueue.PrintAllTickets();

    PayBillsQueue.ServeNextClient();
    std::cout << "\nAfter serving one client:\n";
    PayBillsQueue.PrintInfo();

    // Subscriptions Queue
    std::cout << "\n========== Subscriptions Queue ==========\n";
    SubscriptionsQueue.PrintInfo();
    SubscriptionsQueue.PrintTicketsLineRTL();
    SubscriptionsQueue.PrintTicketsLineLTR();
    SubscriptionsQueue.PrintAllTickets();

    SubscriptionsQueue.ServeNextClient();
    std::cout << "\nAfter serving one client:\n";
    SubscriptionsQueue.PrintInfo();

    return 0;
}