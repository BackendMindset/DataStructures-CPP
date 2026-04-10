#pragma once
#include "clsDynamicArray.h"
using namespace std;

template <class T>
class clsMyQueueArr
{
protected:
    clsDynamicArray<T> _MyList;

public:

    // Enqueue
    void push(const T& value)
    {
        _MyList.InsertAtEnd(value);
    }

    // Dequeue
    bool pop()
    {
        if (IsEmpty())
            return false;

        _MyList.DeleteFirstItem();
        return true;
    }

    void Print() const
    {
        _MyList.PrintList();
    }

    int Size() const
    {
        return _MyList.Size();
    }

    bool IsEmpty() const
    {
        return _MyList.IsEmpty();
    }

    T front() const
    {
        if (IsEmpty())
            throw out_of_range("Queue is empty");

        return _MyList.GetItem(0);
    }

    T back() const
    {
        if (IsEmpty())
            throw out_of_range("Queue is empty");

        return _MyList.GetItem(Size() - 1);
    }

    T GetItem(int Index) const
    {
        return _MyList.GetItem(Index);
    }

    void Reverse()
    {
        _MyList.Reverse();
    }

    bool UpdateItem(int Index, const T& NewValue)
    {
        return _MyList.SetItem(Index, NewValue);
    }

    bool InsertAfter(int Index, const T& NewValue)
    {
        return _MyList.InsertAfter(Index, NewValue);
    }

    void InsertAtFront(const T& Value)
    {
        _MyList.InsertAtBeginning(Value);
    }

    void InsertAtBack(const T& Value)
    {
        _MyList.InsertAtEnd(Value);
    }

    void Clear()
    {
        _MyList.Clear();
    }
};