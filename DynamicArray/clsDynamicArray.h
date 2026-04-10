#pragma once

#include <iostream>
using namespace std;

template <class T>
class clsDynamicArray
{
private:
    int _Size = 0;
    T* _Array = nullptr;

    void _CopyData(T* Source, T* Destination, int Count)
    {
        for (int i = 0; i < Count; i++)
        {
            Destination[i] = Source[i];
        }
    }

public:

    // Constructor
    clsDynamicArray(int Size = 0)
    {
        if (Size < 0) Size = 0;

        _Size = Size;
        _Array = new T[_Size];
    }

    // Copy Constructor
    clsDynamicArray(const clsDynamicArray& Other)
    {
        _Size = Other._Size;
        _Array = new T[_Size];
        _CopyData(Other._Array, _Array, _Size);
    }

    // Assignment Operator
    clsDynamicArray& operator=(const clsDynamicArray& Other)
    {
        if (this != &Other)
        {
            delete[] _Array;

            _Size = Other._Size;
            _Array = new T[_Size];
            _CopyData(Other._Array, _Array, _Size);
        }
        return *this;
    }

    // Destructor
    ~clsDynamicArray()
    {
        delete[] _Array;
    }

    int Size() const
    {
        return _Size;
    }

    bool IsEmpty() const
    {
        return _Size == 0;
    }

    bool SetItem(int index, T Value)
    {
        if (index < 0 || index >= _Size)
            return false;

        _Array[index] = Value;
        return true;
    }

    T GetItem(int index) const
    {
        if (index < 0 || index >= _Size)
            throw out_of_range("Index out of range");

        return _Array[index];
    }

    void PrintList() const
    {
        for (int i = 0; i < _Size; i++)
        {
            cout << _Array[i] << " ";
        }
        cout << "\n";
    }

    void Resize(int NewSize)
    {
        if (NewSize < 0) NewSize = 0;

        T* NewArray = new T[NewSize];

        int MinSize = (NewSize < _Size) ? NewSize : _Size;

        _CopyData(_Array, NewArray, MinSize);

        delete[] _Array;
        _Array = NewArray;
        _Size = NewSize;
    }

    void Reverse()
    {
        for (int i = 0; i < _Size / 2; i++)
        {
            swap(_Array[i], _Array[_Size - 1 - i]);
        }
    }

    void Clear()
    {
        delete[] _Array;
        _Array = new T[0];
        _Size = 0;
    }

    bool DeleteItemAt(int index)
    {
        if (index < 0 || index >= _Size)
            return false;

        T* NewArray = new T[_Size - 1];

        for (int i = 0, j = 0; i < _Size; i++)
        {
            if (i == index) continue;
            NewArray[j++] = _Array[i];
        }

        delete[] _Array;
        _Array = NewArray;
        _Size--;

        return true;
    }

    void DeleteFirstItem()
    {
        DeleteItemAt(0);
    }

    void DeleteLastItem()
    {
        DeleteItemAt(_Size - 1);
    }

    int Find(T Value) const
    {
        for (int i = 0; i < _Size; i++)
        {
            if (_Array[i] == Value)
                return i;
        }
        return -1;
    }

    bool DeleteItem(T Value)
    {
        int index = Find(Value);
        if (index == -1)
            return false;

        return DeleteItemAt(index);
    }

    bool InsertAt(int index, T value)
    {
        if (index < 0 || index > _Size)
            return false;

        T* NewArray = new T[_Size + 1];

        for (int i = 0; i < index; i++)
        {
            NewArray[i] = _Array[i];
        }

        NewArray[index] = value;

        for (int i = index; i < _Size; i++)
        {
            NewArray[i + 1] = _Array[i];
        }

        delete[] _Array;
        _Array = NewArray;
        _Size++;

        return true;
    }

    void InsertAtBeginning(T value)
    {
        InsertAt(0, value);
    }

    bool InsertBefore(int index, T value)
    {
        return InsertAt(index, value);
    }

    bool InsertAfter(int index, T value)
    {
        return InsertAt(index + 1, value);
    }

    bool InsertAtEnd(T value)
    {
        return InsertAt(_Size, value);
    }
};