#pragma once

#include <stack>
#include <iostream>
using namespace std;

class clsMyString
{
private:
    stack<string> _Undo;
    stack<string> _Redo;
    string _Value;

public:

    clsMyString() = default;

    clsMyString(const string& value)
    {
        _Value = value;
    }

    void Set(const string& value)
    {
        // Save current state
        _Undo.push(_Value);

        // Clear redo (important!)
        while (!_Redo.empty())
            _Redo.pop();

        _Value = value;
    }

    string Get() const
    {
        return _Value;
    }

    __declspec(property(get = Get, put = Set)) string Value;

    bool CanUndo() const
    {
        return !_Undo.empty();
    }

    bool CanRedo() const
    {
        return !_Redo.empty();
    }

    bool Undo()
    {
        if (!CanUndo())
            return false;

        _Redo.push(_Value);
        _Value = _Undo.top();
        _Undo.pop();

        return true;
    }

    bool Redo()
    {
        if (!CanRedo())
            return false;

        _Undo.push(_Value);
        _Value = _Redo.top();
        _Redo.pop();

        return true;
    }

    void ClearHistory()
    {
        while (!_Undo.empty()) _Undo.pop();
        while (!_Redo.empty()) _Redo.pop();
    }
};