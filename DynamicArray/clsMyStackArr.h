#pragma once

#include <iostream>
#include "clsMyQueueArr.h"
using namespace std;

template <class T>
class clsMyStackArr : public clsMyQueueArr<T>
{

public:

    // Push to top (LIFO)
    void push(const T& item)
    {
        this->_MyList.InsertAtBeginning(item);
    }

    // Pop from top
    bool pop()
    {
        if (this->IsEmpty())
            return false;

        this->_MyList.DeleteFirstItem();
        return true;
    }

    // Get top element
    T top() const
    {
        if (this->IsEmpty())
            throw out_of_range("Stack is empty");

        return this->_MyList.GetItem(0);
    }

    // Get bottom element
    T bottom() const
    {
        if (this->IsEmpty())
            throw out_of_range("Stack is empty");

        return this->_MyList.GetItem(this->Size() - 1);
    }

};