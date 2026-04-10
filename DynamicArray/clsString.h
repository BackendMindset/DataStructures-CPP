#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

class clsString
{
private:
    string _Value;

    static char ToLowerChar(char c)
    {
        return static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }

    static char ToUpperChar(char c)
    {
        return static_cast<char>(toupper(static_cast<unsigned char>(c)));
    }

public:

    enum enWhatToCount
    {
        SmallLetters = 0,
        CapitalLetters = 1,
        All = 3
    };

    clsString()
    {
        _Value = "";
    }

    clsString(string Value)
    {
        _Value = Value;
    }

    void SetValue(string Value)
    {
        _Value = Value;
    }

    string GetValue()
    {
        return _Value;
    }

    __declspec(property(get = GetValue, put = SetValue)) string Value;

    static short Length(string S1)
    {
        return static_cast<short>(S1.length());
    }

    short Length()
    {
        return static_cast<short>(_Value.length());
    }

    static short CountWords(string S1)
    {
        S1 = Trim(S1);

        if (S1 == "")
            return 0;

        string delim = " ";
        short Counter = 0;
        short pos = 0;
        string sWord;

        while ((pos = static_cast<short>(S1.find(delim))) != string::npos)
        {
            sWord = S1.substr(0, pos);
            if (sWord != "")
            {
                Counter++;
            }

            S1.erase(0, pos + delim.length());
        }

        if (S1 != "")
        {
            Counter++;
        }

        return Counter;
    }

    short CountWords()
    {
        return CountWords(_Value);
    }

    static string UpperFirstLetterOfEachWord(string S1)
    {
        bool isFirstLetter = true;

        for (size_t i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ' && isFirstLetter)
            {
                S1[i] = ToUpperChar(S1[i]);
            }

            isFirstLetter = (S1[i] == ' ');
        }

        return S1;
    }

    void UpperFirstLetterOfEachWord()
    {
        _Value = UpperFirstLetterOfEachWord(_Value);
    }

    static string LowerFirstLetterOfEachWord(string S1)
    {
        bool isFirstLetter = true;

        for (size_t i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ' && isFirstLetter)
            {
                S1[i] = ToLowerChar(S1[i]);
            }

            isFirstLetter = (S1[i] == ' ');
        }

        return S1;
    }

    void LowerFirstLetterOfEachWord()
    {
        _Value = LowerFirstLetterOfEachWord(_Value);
    }

    static string UpperAllString(string S1)
    {
        for (size_t i = 0; i < S1.length(); i++)
        {
            S1[i] = ToUpperChar(S1[i]);
        }
        return S1;
    }

    void UpperAllString()
    {
        _Value = UpperAllString(_Value);
    }

    static string LowerAllString(string S1)
    {
        for (size_t i = 0; i < S1.length(); i++)
        {
            S1[i] = ToLowerChar(S1[i]);
        }
        return S1;
    }

    void LowerAllString()
    {
        _Value = LowerAllString(_Value);
    }

    static char InvertLetterCase(char Char1)
    {
        return isupper(static_cast<unsigned char>(Char1)) ? ToLowerChar(Char1) : ToUpperChar(Char1);
    }

    static string InvertAllLettersCase(string S1)
    {
        for (size_t i = 0; i < S1.length(); i++)
        {
            S1[i] = InvertLetterCase(S1[i]);
        }
        return S1;
    }

    void InvertAllLettersCase()
    {
        _Value = InvertAllLettersCase(_Value);
    }

    static short CountLetters(string S1, enWhatToCount WhatToCount = enWhatToCount::All)
    {
        if (WhatToCount == enWhatToCount::All)
        {
            return static_cast<short>(S1.length());
        }

        short Counter = 0;

        for (size_t i = 0; i < S1.length(); i++)
        {
            if (WhatToCount == enWhatToCount::CapitalLetters && isupper(static_cast<unsigned char>(S1[i])))
                Counter++;

            if (WhatToCount == enWhatToCount::SmallLetters && islower(static_cast<unsigned char>(S1[i])))
                Counter++;
        }

        return Counter;
    }

    static short CountCapitalLetters(string S1)
    {
        short Counter = 0;

        for (size_t i = 0; i < S1.length(); i++)
        {
            if (isupper(static_cast<unsigned char>(S1[i])))
                Counter++;
        }

        return Counter;
    }

    short CountCapitalLetters()
    {
        return CountCapitalLetters(_Value);
    }

    static short CountSmallLetters(string S1)
    {
        short Counter = 0;

        for (size_t i = 0; i < S1.length(); i++)
        {
            if (islower(static_cast<unsigned char>(S1[i])))
                Counter++;
        }

        return Counter;
    }

    short CountSmallLetters()
    {
        return CountSmallLetters(_Value);
    }

    static short CountSpecificLetter(string S1, char Letter, bool MatchCase = true)
    {
        short Counter = 0;

        for (size_t i = 0; i < S1.length(); i++)
        {
            if (MatchCase)
            {
                if (S1[i] == Letter)
                    Counter++;
            }
            else
            {
                if (ToLowerChar(S1[i]) == ToLowerChar(Letter))
                    Counter++;
            }
        }

        return Counter;
    }

    short CountSpecificLetter(char Letter, bool MatchCase = true)
    {
        return CountSpecificLetter(_Value, Letter, MatchCase);
    }

    static bool IsVowel(char Ch1)
    {
        Ch1 = ToLowerChar(Ch1);

        return ((Ch1 == 'a') || (Ch1 == 'e') || (Ch1 == 'i') || (Ch1 == 'o') || (Ch1 == 'u'));
    }

    static short CountVowels(string S1)
    {
        short Counter = 0;

        for (size_t i = 0; i < S1.length(); i++)
        {
            if (IsVowel(S1[i]))
                Counter++;
        }

        return Counter;
    }

    short CountVowels()
    {
        return CountVowels(_Value);
    }

    static vector<string> Split(string S1, string Delim)
    {
        vector<string> vString;

        if (Delim == "")
        {
            vString.push_back(S1);
            return vString;
        }

        size_t pos = 0;
        string sWord;

        while ((pos = S1.find(Delim)) != string::npos)
        {
            sWord = S1.substr(0, pos);
            vString.push_back(sWord);
            S1.erase(0, pos + Delim.length());
        }

        if (S1 != "")
        {
            vString.push_back(S1);
        }

        return vString;
    }

    vector<string> Split(string Delim)
    {
        return Split(_Value, Delim);
    }

    static string TrimLeft(string S1)
    {
        for (size_t i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ')
            {
                return S1.substr(i, S1.length() - i);
            }
        }
        return "";
    }

    void TrimLeft()
    {
        _Value = TrimLeft(_Value);
    }

    static string TrimRight(string S1)
    {
        if (S1.empty())
            return "";

        for (int i = static_cast<int>(S1.length()) - 1; i >= 0; i--)
        {
            if (S1[i] != ' ')
            {
                return S1.substr(0, i + 1);
            }
        }
        return "";
    }

    void TrimRight()
    {
        _Value = TrimRight(_Value);
    }

    static string Trim(string S1)
    {
        return TrimLeft(TrimRight(S1));
    }

    void Trim()
    {
        _Value = Trim(_Value);
    }

    static string JoinString(vector<string> vString, string Delim)
    {
        if (vString.empty())
            return "";

        string S1 = "";

        for (size_t i = 0; i < vString.size(); i++)
        {
            S1 = S1 + vString[i];
            if (i != vString.size() - 1)
                S1 += Delim;
        }

        return S1;
    }

    static string JoinString(string arrString[], short Length, string Delim)
    {
        if (Length <= 0)
            return "";

        string S1 = "";

        for (short i = 0; i < Length; i++)
        {
            S1 = S1 + arrString[i];
            if (i != Length - 1)
                S1 += Delim;
        }

        return S1;
    }

    static string ReverseWordsInString(string S1)
    {
        vector<string> vString = Split(Trim(S1), " ");
        string S2 = "";

        if (vString.empty())
            return "";

        vector<string>::iterator iter = vString.end();

        while (iter != vString.begin())
        {
            --iter;
            S2 += *iter;

            if (iter != vString.begin())
                S2 += " ";
        }

        return S2;
    }

    void ReverseWordsInString()
    {
        _Value = ReverseWordsInString(_Value);
    }

    static string ReplaceWord(string S1, string StringToReplace, string sRepalceTo, bool MatchCase = true)
    {
        vector<string> vString = Split(S1, " ");

        for (string& s : vString)
        {
            if (MatchCase)
            {
                if (s == StringToReplace)
                {
                    s = sRepalceTo;
                }
            }
            else
            {
                if (LowerAllString(s) == LowerAllString(StringToReplace))
                {
                    s = sRepalceTo;
                }
            }
        }

        return JoinString(vString, " ");
    }

    string ReplaceWord(string StringToReplace, string sRepalceTo)
    {
        return ReplaceWord(_Value, StringToReplace, sRepalceTo);
    }

    static string RemovePunctuations(string S1)
    {
        string S2 = "";

        for (size_t i = 0; i < S1.length(); i++)
        {
            if (!ispunct(static_cast<unsigned char>(S1[i])))
            {
                S2 += S1[i];
            }
        }

        return S2;
    }

    void RemovePunctuations()
    {
        _Value = RemovePunctuations(_Value);
    }
};