#pragma once

#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include "clsDate.h"

class clsQueueLine
{
private:
    short _TotalTickets = 0;
    short _AverageServeTime = 0;
    std::string _Prefix = "";

    class clsTicket
    {
    private:
        short _Number = 0;
        std::string _Prefix;
        std::string _TicketTime;
        short _WaitingClients = 0;
        short _AverageServeTime = 0;

    public:
        explicit clsTicket(const std::string& Prefix, short Number, short WaitingClients, short AverageServeTime)
            : _Number(Number),
            _Prefix(Prefix),
            _WaitingClients(WaitingClients),
            _AverageServeTime(AverageServeTime)
        {
            _TicketTime = clsDate::GetSystemDateTimeString();
        }

        std::string FullNumber() const
        {
            return _Prefix + std::to_string(_Number);
        }

        short ExpectedServeTime() const
        {
            return _AverageServeTime * _WaitingClients;
        }

        void Print() const
        {
            std::cout << "\n\t\t\t  _______________________\n";
            std::cout << "\n\t\t\t\t    " << FullNumber();
            std::cout << "\n\n\t\t\t    " << _TicketTime;
            std::cout << "\n\t\t\t    Waiting Clients = " << _WaitingClients;
            std::cout << "\n\t\t\t    Serve Time In";
            std::cout << "\n\t\t\t    " << ExpectedServeTime() << " Minutes.";
            std::cout << "\n\t\t\t  _______________________\n";
        }
    };

    std::queue<clsTicket> _QueueLine;

public:

    clsQueueLine(const std::string& Prefix, short AverageServeTime)
        : _Prefix(Prefix), _AverageServeTime(AverageServeTime)
    {
    }

    void IssueTicket()
    {
        _TotalTickets++;
        clsTicket Ticket(_Prefix, _TotalTickets, WaitingClients(), _AverageServeTime);
        _QueueLine.push(Ticket);
    }

    int WaitingClients() const
    {
        return static_cast<int>(_QueueLine.size());
    }

    std::string WhoIsNext() const
    {
        if (_QueueLine.empty())
            return "No Clients Left.";

        return _QueueLine.front().FullNumber();
    }

    bool ServeNextClient()
    {
        if (_QueueLine.empty())
            return false;

        _QueueLine.pop();
        return true;
    }

    short ServedClients() const
    {
        return static_cast<short>(_TotalTickets - WaitingClients());
    }

    void PrintInfo() const
    {
        std::cout << "\n\t\t\t _________________________\n";
        std::cout << "\n\t\t\t\tQueue Info";
        std::cout << "\n\t\t\t _________________________\n";
        std::cout << "\n\t\t\t    Prefix         = " << _Prefix;
        std::cout << "\n\t\t\t    Total Tickets  = " << _TotalTickets;
        std::cout << "\n\t\t\t    Served Clients = " << ServedClients();
        std::cout << "\n\t\t\t    Waiting Clients = " << WaitingClients();
        std::cout << "\n\t\t\t _________________________\n\n";
    }

    void PrintTicketsLineRTL() const
    {
        if (_QueueLine.empty())
        {
            std::cout << "\n\t\tTickets: No Tickets.\n";
            return;
        }

        std::cout << "\n\t\tTickets: ";

        std::queue<clsTicket> TempQueue = _QueueLine;

        while (!TempQueue.empty())
        {
            std::cout << TempQueue.front().FullNumber() << " <-- ";
            TempQueue.pop();
        }

        std::cout << "\n";
    }

    void PrintTicketsLineLTR() const
    {
        if (_QueueLine.empty())
        {
            std::cout << "\n\t\tTickets: No Tickets.\n";
            return;
        }

        std::cout << "\n\t\tTickets: ";

        std::queue<clsTicket> TempQueue = _QueueLine;
        std::stack<clsTicket> TempStack;

        while (!TempQueue.empty())
        {
            TempStack.push(TempQueue.front());
            TempQueue.pop();
        }

        while (!TempStack.empty())
        {
            std::cout << TempStack.top().FullNumber() << " --> ";
            TempStack.pop();
        }

        std::cout << "\n";
    }

    void PrintAllTickets() const
    {
        if (_QueueLine.empty())
        {
            std::cout << "\n\n\t\t\t---No Tickets---\n";
            return;
        }

        std::cout << "\n\n\t\t\t---Tickets---";

        std::queue<clsTicket> TempQueue = _QueueLine;

        while (!TempQueue.empty())
        {
            TempQueue.front().Print();
            TempQueue.pop();
        }
    }
};