//ProgrammingAdvices.com
//Mohammed Abu-Hadhoud

#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdio>
#include "clsString.h"

class clsDate
{
private:
    short _Day = 1;
    short _Month = 1;
    short _Year = 1900;

public:
    clsDate()
    {
        time_t t = time(0);
        tm now{};
        localtime_s(&now, &t);

        _Day = static_cast<short>(now.tm_mday);
        _Month = static_cast<short>(now.tm_mon + 1);
        _Year = static_cast<short>(now.tm_year + 1900);
    }

    clsDate(const std::string& sDate)
    {
        std::vector<std::string> vDate = clsString::Split(sDate, "/");

        if (vDate.size() != 3)
        {
            _Day = 1;
            _Month = 1;
            _Year = 1900;
            return;
        }

        _Day = static_cast<short>(std::stoi(vDate[0]));
        _Month = static_cast<short>(std::stoi(vDate[1]));
        _Year = static_cast<short>(std::stoi(vDate[2]));
    }

    clsDate(short Day, short Month, short Year)
    {
        _Day = Day;
        _Month = Month;
        _Year = Year;
    }

    clsDate(short DateOrderInYear, short Year)
    {
        clsDate Date1 = GetDateFromDayOrderInYear(DateOrderInYear, Year);
        _Day = Date1.Day;
        _Month = Date1.Month;
        _Year = Date1.Year;
    }

    void SetDay(short Day) { _Day = Day; }
    short GetDay() const { return _Day; }
    __declspec(property(get = GetDay, put = SetDay)) short Day;

    void SetMonth(short Month) { _Month = Month; }
    short GetMonth() const { return _Month; }
    __declspec(property(get = GetMonth, put = SetMonth)) short Month;

    void SetYear(short Year) { _Year = Year; }
    short GetYear() const { return _Year; }
    __declspec(property(get = GetYear, put = SetYear)) short Year;

    static clsDate GetSystemDate()
    {
        time_t t = time(0);
        tm now{};
        localtime_s(&now, &t);

        return clsDate(
            static_cast<short>(now.tm_mday),
            static_cast<short>(now.tm_mon + 1),
            static_cast<short>(now.tm_year + 1900)
        );
    }

    static std::string GetSystemDateTimeString()
    {
        time_t t = time(0);
        tm now{};
        localtime_s(&now, &t);

        return std::to_string(now.tm_mday) + "/" +
               std::to_string(now.tm_mon + 1) + "/" +
               std::to_string(now.tm_year + 1900) + " - " +
               std::to_string(now.tm_hour) + ":" +
               std::to_string(now.tm_min) + ":" +
               std::to_string(now.tm_sec);
    }

    static bool isLeapYear(short Year)
    {
        return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
    }

    bool isLeapYear() const
    {
        return isLeapYear(_Year);
    }

    static short NumberOfDaysInAYear(short Year)
    {
        return isLeapYear(Year) ? 366 : 365;
    }

    short NumberOfDaysInAYear() const
    {
        return NumberOfDaysInAYear(_Year);
    }

    static short NumberOfHoursInAYear(short Year)
    {
        return NumberOfDaysInAYear(Year) * 24;
    }

    short NumberOfHoursInAYear() const
    {
        return NumberOfHoursInAYear(_Year);
    }

    static int NumberOfMinutesInAYear(short Year)
    {
        return NumberOfHoursInAYear(Year) * 60;
    }

    int NumberOfMinutesInAYear() const
    {
        return NumberOfMinutesInAYear(_Year);
    }

    static int NumberOfSecondsInAYear(short Year)
    {
        return NumberOfMinutesInAYear(Year) * 60;
    }

    int NumberOfSecondsInAYear() const
    {
        return NumberOfSecondsInAYear(_Year);
    }

    static short NumberOfDaysInAMonth(short Month, short Year)
    {
        if (Month < 1 || Month > 12)
            return 0;

        int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) : days[Month - 1];
    }

    short NumberOfDaysInAMonth() const
    {
        return NumberOfDaysInAMonth(_Month, _Year);
    }

    static short NumberOfHoursInAMonth(short Month, short Year)
    {
        return NumberOfDaysInAMonth(Month, Year) * 24;
    }

    short NumberOfHoursInAMonth() const
    {
        return NumberOfHoursInAMonth(_Month, _Year);
    }

    static int NumberOfMinutesInAMonth(short Month, short Year)
    {
        return NumberOfHoursInAMonth(Month, Year) * 60;
    }

    int NumberOfMinutesInAMonth() const
    {
        return NumberOfMinutesInAMonth(_Month, _Year);
    }

    static int NumberOfSecondsInAMonth(short Month, short Year)
    {
        return NumberOfMinutesInAMonth(Month, Year) * 60;
    }

    int NumberOfSecondsInAMonth() const
    {
        return NumberOfSecondsInAMonth(_Month, _Year);
    }

    static bool IsValidDate(const clsDate& Date)
    {
        if (Date.Month < 1 || Date.Month > 12)
            return false;

        short DaysInMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);
        if (DaysInMonth == 0)
            return false;

        if (Date.Day < 1 || Date.Day > DaysInMonth)
            return false;

        return true;
    }

    bool IsValid() const
    {
        return IsValidDate(*this);
    }

    static std::string DateToString(const clsDate& Date)
    {
        return std::to_string(Date.Day) + "/" +
               std::to_string(Date.Month) + "/" +
               std::to_string(Date.Year);
    }

    std::string DateToString() const
    {
        return DateToString(*this);
    }

    static short DayOfWeekOrder(short Day, short Month, short Year)
    {
        short a, y, m;
        a = (14 - Month) / 12;
        y = Year - a;
        m = Month + (12 * a) - 2;

        return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }

    short DayOfWeekOrder() const
    {
        return DayOfWeekOrder(_Day, _Month, _Year);
    }

    static std::string DayShortName(short DayOfWeekOrder)
    {
        std::string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

        if (DayOfWeekOrder < 0 || DayOfWeekOrder > 6)
            return "";

        return arrDayNames[DayOfWeekOrder];
    }

    static std::string DayShortName(short Day, short Month, short Year)
    {
        std::string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
        return arrDayNames[DayOfWeekOrder(Day, Month, Year)];
    }

    std::string DayShortName() const
    {
        std::string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
        return arrDayNames[DayOfWeekOrder(_Day, _Month, _Year)];
    }

    static std::string MonthShortName(short MonthNumber)
    {
        std::string Months[12] = {
            "Jan", "Feb", "Mar",
            "Apr", "May", "Jun",
            "Jul", "Aug", "Sep",
            "Oct", "Nov", "Dec"
        };

        if (MonthNumber < 1 || MonthNumber > 12)
            return "";

        return Months[MonthNumber - 1];
    }

    std::string MonthShortName() const
    {
        return MonthShortName(_Month);
    }

    static void PrintMonthCalendar(short Month, short Year)
    {
        int current = DayOfWeekOrder(1, Month, Year);
        int NumberOfDays = NumberOfDaysInAMonth(Month, Year);

        std::printf("\n  _______________%s_______________\n\n", MonthShortName(Month).c_str());
        std::printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

        int i;
        for (i = 0; i < current; i++)
            std::printf("     ");

        for (int j = 1; j <= NumberOfDays; j++)
        {
            std::printf("%5d", j);

            if (++i == 7)
            {
                i = 0;
                std::printf("\n");
            }
        }

        std::printf("\n  _________________________________\n");
    }

    void PrintMonthCalendar() const
    {
        PrintMonthCalendar(_Month, _Year);
    }

    static void PrintYearCalendar(int Year)
    {
        std::printf("\n  _________________________________\n\n");
        std::printf("           Calendar - %d\n", Year);
        std::printf("  _________________________________\n");

        for (int i = 1; i <= 12; i++)
        {
            PrintMonthCalendar(i, Year);
        }
    }

    void PrintYearCalendar() const
    {
        std::printf("\n  _________________________________\n\n");
        std::printf("           Calendar - %d\n", _Year);
        std::printf("  _________________________________\n");

        for (int i = 1; i <= 12; i++)
        {
            PrintMonthCalendar(i, _Year);
        }
    }

    static short DaysFromTheBeginingOfTheYear(short Day, short Month, short Year)
    {
        short TotalDays = 0;

        for (int i = 1; i <= Month - 1; i++)
        {
            TotalDays += NumberOfDaysInAMonth(i, Year);
        }

        TotalDays += Day;
        return TotalDays;
    }

    short DaysFromTheBeginingOfTheYear() const
    {
        return DaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
    }

    static clsDate GetDateFromDayOrderInYear(short DateOrderInYear, short Year)
    {
        short MaxDays = NumberOfDaysInAYear(Year);

        if (DateOrderInYear < 1)
            DateOrderInYear = 1;
        else if (DateOrderInYear > MaxDays)
            DateOrderInYear = MaxDays;

        clsDate Date(1, 1, Year);
        short RemainingDays = DateOrderInYear;

        while (true)
        {
            short MonthDays = NumberOfDaysInAMonth(Date.Month, Year);

            if (RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;
                Date.Month++;
            }
            else
            {
                Date.Day = RemainingDays;
                break;
            }
        }

        return Date;
    }

    void AddDays(short Days)
    {
        if (Days == 0)
            return;

        if (Days > 0)
        {
            short RemainingDays = Days + DaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
            short MonthDays = 0;

            _Month = 1;

            while (true)
            {
                MonthDays = NumberOfDaysInAMonth(_Month, _Year);

                if (RemainingDays > MonthDays)
                {
                    RemainingDays -= MonthDays;
                    _Month++;

                    if (_Month > 12)
                    {
                        _Month = 1;
                        _Year++;
                    }
                }
                else
                {
                    _Day = RemainingDays;
                    break;
                }
            }
        }
        else
        {
            for (short i = 1; i <= -Days; i++)
            {
                *this = DecreaseDateByOneDay(*this);
            }
        }
    }

    static bool IsDate1BeforeDate2(const clsDate& Date1, const clsDate& Date2)
    {
        return (Date1.Year < Date2.Year) ? true :
               (Date1.Year > Date2.Year) ? false :
               (Date1.Month < Date2.Month) ? true :
               (Date1.Month > Date2.Month) ? false :
               (Date1.Day < Date2.Day);
    }

    bool IsDateBeforeDate2(const clsDate& Date2) const
    {
        return IsDate1BeforeDate2(*this, Date2);
    }

    static bool IsDate1EqualDate2(const clsDate& Date1, const clsDate& Date2)
    {
        return (Date1.Year == Date2.Year) &&
               (Date1.Month == Date2.Month) &&
               (Date1.Day == Date2.Day);
    }

    bool IsDateEqualDate2(const clsDate& Date2) const
    {
        return IsDate1EqualDate2(*this, Date2);
    }

    static bool IsLastDayInMonth(const clsDate& Date)
    {
        return (Date.Day == NumberOfDaysInAMonth(Date.Month, Date.Year));
    }

    bool IsLastDayInMonth() const
    {
        return IsLastDayInMonth(*this);
    }

    static bool IsLastMonthInYear(short Month)
    {
        return (Month == 12);
    }

    static clsDate AddOneDay(clsDate Date)
    {
        if (IsLastDayInMonth(Date))
        {
            if (IsLastMonthInYear(Date.Month))
            {
                Date.Month = 1;
                Date.Day = 1;
                Date.Year++;
            }
            else
            {
                Date.Day = 1;
                Date.Month++;
            }
        }
        else
        {
            Date.Day++;
        }

        return Date;
    }

    void AddOneDay()
    {
        *this = AddOneDay(*this);
    }

    static void SwapDates(clsDate& Date1, clsDate& Date2)
    {
        clsDate TempDate = Date1;
        Date1 = Date2;
        Date2 = TempDate;
    }

    static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
    {
        if (IsDate1EqualDate2(Date1, Date2))
            return IncludeEndDay ? 1 : 0;

        int Days = 0;
        int Sign = 1;

        if (IsDate1AfterDate2(Date1, Date2))
        {
            SwapDates(Date1, Date2);
            Sign = -1;
        }

        while (IsDate1BeforeDate2(Date1, Date2))
        {
            Days++;
            Date1 = AddOneDay(Date1);
        }

        if (IncludeEndDay)
            Days++;

        return Days * Sign;
    }

    int GetDifferenceInDays(const clsDate& Date2, bool IncludeEndDay = false) const
    {
        return GetDifferenceInDays(*this, Date2, IncludeEndDay);
    }

    static short CalculateMyAgeInDays(const clsDate& DateOfBirth)
    {
        return static_cast<short>(GetDifferenceInDays(DateOfBirth, clsDate::GetSystemDate(), true));
    }

    static clsDate IncreaseDateByOneWeek(clsDate& Date)
    {
        for (int i = 1; i <= 7; i++)
        {
            Date = AddOneDay(Date);
        }

        return Date;
    }

    void IncreaseDateByOneWeek()
    {
        *this = IncreaseDateByOneWeek(*this);
    }

    static clsDate IncreaseDateByXWeeks(short Weeks, clsDate& Date)
    {
        for (short i = 1; i <= Weeks; i++)
        {
            Date = IncreaseDateByOneWeek(Date);
        }
        return Date;
    }

    void IncreaseDateByXWeeks(short Weeks)
    {
        *this = IncreaseDateByXWeeks(Weeks, *this);
    }

    static clsDate IncreaseDateByOneMonth(clsDate& Date)
    {
        if (Date.Month == 12)
        {
            Date.Month = 1;
            Date.Year++;
        }
        else
        {
            Date.Month++;
        }

        short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);
        if (Date.Day > NumberOfDaysInCurrentMonth)
            Date.Day = NumberOfDaysInCurrentMonth;

        return Date;
    }

    void IncreaseDateByOneMonth()
    {
        *this = IncreaseDateByOneMonth(*this);
    }

    static clsDate IncreaseDateByXDays(short Days, clsDate& Date)
    {
        for (short i = 1; i <= Days; i++)
        {
            Date = AddOneDay(Date);
        }
        return Date;
    }

    void IncreaseDateByXDays(short Days)
    {
        *this = IncreaseDateByXDays(Days, *this);
    }

    static clsDate IncreaseDateByXMonths(short Months, clsDate& Date)
    {
        for (short i = 1; i <= Months; i++)
        {
            Date = IncreaseDateByOneMonth(Date);
        }
        return Date;
    }

    void IncreaseDateByXMonths(short Months)
    {
        *this = IncreaseDateByXMonths(Months, *this);
    }

    static clsDate IncreaseDateByOneYear(clsDate& Date)
    {
        Date.Year++;
        return Date;
    }

    void IncreaseDateByOneYear()
    {
        *this = IncreaseDateByOneYear(*this);
    }

    static clsDate IncreaseDateByXYears(short Years, clsDate& Date)
    {
        Date.Year += Years;
        return Date;
    }

    void IncreaseDateByXYears(short Years)
    {
        *this = IncreaseDateByXYears(Years, *this);
    }

    static clsDate IncreaseDateByOneDecade(clsDate& Date)
    {
        Date.Year += 10;
        return Date;
    }

    void IncreaseDateByOneDecade()
    {
        *this = IncreaseDateByOneDecade(*this);
    }

    static clsDate IncreaseDateByXDecades(short Decade, clsDate& Date)
    {
        Date.Year += Decade * 10;
        return Date;
    }

    void IncreaseDateByXDecades(short Decade)
    {
        *this = IncreaseDateByXDecades(Decade, *this);
    }

    static clsDate IncreaseDateByOneCentury(clsDate& Date)
    {
        Date.Year += 100;
        return Date;
    }

    void IncreaseDateByOneCentury()
    {
        *this = IncreaseDateByOneCentury(*this);
    }

    static clsDate IncreaseDateByOneMillennium(clsDate& Date)
    {
        Date.Year += 1000;
        return Date;
    }

    void IncreaseDateByOneMillennium()
    {
        *this = IncreaseDateByOneMillennium(*this);
    }

    static clsDate DecreaseDateByOneDay(clsDate Date)
    {
        if (Date.Day == 1)
        {
            if (Date.Month == 1)
            {
                Date.Month = 12;
                Date.Day = 31;
                Date.Year--;
            }
            else
            {
                Date.Month--;
                Date.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);
            }
        }
        else
        {
            Date.Day--;
        }

        return Date;
    }

    void DecreaseDateByOneDay()
    {
        *this = DecreaseDateByOneDay(*this);
    }

    static clsDate DecreaseDateByOneWeek(clsDate& Date)
    {
        for (int i = 1; i <= 7; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }

        return Date;
    }

    void DecreaseDateByOneWeek()
    {
        *this = DecreaseDateByOneWeek(*this);
    }

    static clsDate DecreaseDateByXWeeks(short Weeks, clsDate& Date)
    {
        for (short i = 1; i <= Weeks; i++)
        {
            Date = DecreaseDateByOneWeek(Date);
        }
        return Date;
    }

    void DecreaseDateByXWeeks(short Weeks)
    {
        *this = DecreaseDateByXWeeks(Weeks, *this);
    }

    static clsDate DecreaseDateByOneMonth(clsDate& Date)
    {
        if (Date.Month == 1)
        {
            Date.Month = 12;
            Date.Year--;
        }
        else
        {
            Date.Month--;
        }

        short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);
        if (Date.Day > NumberOfDaysInCurrentMonth)
            Date.Day = NumberOfDaysInCurrentMonth;

        return Date;
    }

    void DecreaseDateByOneMonth()
    {
        *this = DecreaseDateByOneMonth(*this);
    }

    static clsDate DecreaseDateByXDays(short Days, clsDate& Date)
    {
        for (short i = 1; i <= Days; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }
        return Date;
    }

    void DecreaseDateByXDays(short Days)
    {
        *this = DecreaseDateByXDays(Days, *this);
    }

    static clsDate DecreaseDateByXMonths(short Months, clsDate& Date)
    {
        for (short i = 1; i <= Months; i++)
        {
            Date = DecreaseDateByOneMonth(Date);
        }
        return Date;
    }

    void DecreaseDateByXMonths(short Months)
    {
        *this = DecreaseDateByXMonths(Months, *this);
    }

    static clsDate DecreaseDateByOneYear(clsDate& Date)
    {
        Date.Year--;
        return Date;
    }

    void DecreaseDateByOneYear()
    {
        *this = DecreaseDateByOneYear(*this);
    }

    static clsDate DecreaseDateByXYears(short Years, clsDate& Date)
    {
        Date.Year -= Years;
        return Date;
    }

    void DecreaseDateByXYears(short Years)
    {
        *this = DecreaseDateByXYears(Years, *this);
    }

    static clsDate DecreaseDateByOneDecade(clsDate& Date)
    {
        Date.Year -= 10;
        return Date;
    }

    void DecreaseDateByOneDecade()
    {
        *this = DecreaseDateByOneDecade(*this);
    }

    static clsDate DecreaseDateByXDecades(short Decades, clsDate& Date)
    {
        Date.Year -= Decades * 10;
        return Date;
    }

    void DecreaseDateByXDecades(short Decades)
    {
        *this = DecreaseDateByXDecades(Decades, *this);
    }

    static clsDate DecreaseDateByOneCentury(clsDate& Date)
    {
        Date.Year -= 100;
        return Date;
    }

    void DecreaseDateByOneCentury()
    {
        *this = DecreaseDateByOneCentury(*this);
    }

    static clsDate DecreaseDateByOneMillennium(clsDate& Date)
    {
        Date.Year -= 1000;
        return Date;
    }

    void DecreaseDateByOneMillennium()
    {
        *this = DecreaseDateByOneMillennium(*this);
    }

    static bool IsEndOfWeek(const clsDate& Date)
    {
        return DayOfWeekOrder(Date.Day, Date.Month, Date.Year) == 6;
    }

    bool IsEndOfWeek() const
    {
        return IsEndOfWeek(*this);
    }

    static bool IsWeekEnd(const clsDate& Date)
    {
        short DayIndex = DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
        return (DayIndex == 5 || DayIndex == 6);
    }

    bool IsWeekEnd() const
    {
        return IsWeekEnd(*this);
    }

    static bool IsBusinessDay(const clsDate& Date)
    {
        return !IsWeekEnd(Date);
    }

    bool IsBusinessDay() const
    {
        return IsBusinessDay(*this);
    }

    static short DaysUntilTheEndOfWeek(const clsDate& Date)
    {
        return static_cast<short>(6 - DayOfWeekOrder(Date.Day, Date.Month, Date.Year));
    }

    short DaysUntilTheEndOfWeek() const
    {
        return DaysUntilTheEndOfWeek(*this);
    }

    static short DaysUntilTheEndOfMonth(const clsDate& Date1)
    {
        clsDate EndOfMonthDate;
        EndOfMonthDate.Day = NumberOfDaysInAMonth(Date1.Month, Date1.Year);
        EndOfMonthDate.Month = Date1.Month;
        EndOfMonthDate.Year = Date1.Year;

        return static_cast<short>(GetDifferenceInDays(Date1, EndOfMonthDate, true));
    }

    short DaysUntilTheEndOfMonth() const
    {
        return DaysUntilTheEndOfMonth(*this);
    }

    static short DaysUntilTheEndOfYear(const clsDate& Date1)
    {
        clsDate EndOfYearDate;
        EndOfYearDate.Day = 31;
        EndOfYearDate.Month = 12;
        EndOfYearDate.Year = Date1.Year;

        return static_cast<short>(GetDifferenceInDays(Date1, EndOfYearDate, true));
    }

    short DaysUntilTheEndOfYear() const
    {
        return DaysUntilTheEndOfYear(*this);
    }

    static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
    {
        short Days = 0;

        while (IsDate1BeforeDate2(DateFrom, DateTo))
        {
            if (IsBusinessDay(DateFrom))
                Days++;

            DateFrom = AddOneDay(DateFrom);
        }

        return Days;
    }

    static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
    {
        return CalculateBusinessDays(DateFrom, DateTo);
    }

    static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
    {
        short WeekEndCounter = 0;

        for (short i = 1; i <= VacationDays; i++)
        {
            if (IsWeekEnd(DateFrom))
                WeekEndCounter++;

            DateFrom = AddOneDay(DateFrom);
        }

        for (short i = 1; i <= WeekEndCounter; i++)
            DateFrom = AddOneDay(DateFrom);

        return DateFrom;
    }

    static bool IsDate1AfterDate2(const clsDate& Date1, const clsDate& Date2)
    {
        return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
    }

    bool IsDateAfterDate2(const clsDate& Date2) const
    {
        return IsDate1AfterDate2(*this, Date2);
    }

    enum enDateCompare { Before = -1, Equal = 0, After = 1 };

    static enDateCompare CompareDates(const clsDate& Date1, const clsDate& Date2)
    {
        if (IsDate1BeforeDate2(Date1, Date2))
            return enDateCompare::Before;

        if (IsDate1EqualDate2(Date1, Date2))
            return enDateCompare::Equal;

        return enDateCompare::After;
    }

    enDateCompare CompareDates(const clsDate& Date2) const
    {
        return CompareDates(*this, Date2);
    }
};
