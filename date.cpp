#include <iostream>

struct wrongDayException
{
    int days;
};

struct wrongMonthException
{
    int month;
};

struct wrongYearException
{
    int year;
};

class Date
{
private:
    int years;
    int months;
    int days;

public:
    Date(int years, int months, int days)
    {
        this->days = days;
        this->years = years;
        this->months = months;

        int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        if ((years % 4 == 0 && years % 100 != 0) || (years % 400 == 0))
        {
            daysInMonth[2] = 29;
        }

        if (days > daysInMonth[months] || days <= 0)
        {
            throw wrongDayException{days};
        }

        if (months > 12 || months <= 0)
        {
            throw wrongMonthException{months};
        }

        if (years <= 0)
        {
            throw wrongYearException{years};
        }
    }

    Date(int days) : Date(1, 1, days)
    {
    }

    int GetYears() const;
    int GetMonths() const;
    int GetDays() const;

    void AddDays(int d)
    {
        days += d;
        *this = Date(years, months, days);
    }

    Date operator+(int d) const
    {
        return Date(years, months, days + d);
    }

    Date& operator+=(int d)
    {
        days += d;
        return *this;
    }

    Date operator-(int d) const
    {
        return Date(years, months, days - d);
    }
};

std::ostream& operator<<(std::ostream& out, const Date& d)
{
    out << d.GetYears() << " / " << d.GetMonths() << " / " << d.GetDays();
    return out;
}

std::istream& operator>>(std::istream& in, Date& date)
{
    in.exceptions(std::istream::failbit);

    int y, m, d;
    char c;

    in >> d >> c;
    in >> m >> c;
    in >> y;

    date = Date(y, m, d);

    return in;
}

int Date::GetDays() const
{
    return days;
}

int Date::GetMonths() const
{
    return months;
}

int Date::GetYears() const
{
    return years;
}

int main()
{
    try
    {
        Date today(29, 11, 2023);
        //Date today(-29, 11, 2023);
        //Date today(29, -11, 2023);
        //Date today(29, -11, -2023);

        std::cout << today << std::endl;

        today.AddDays(30);
        std::cout << "+ 30 days : " << today << std::endl;

        today.AddDays(-15);
        std::cout << "-15 days: " << today << std::endl;
    }


    catch (const wrongDayException& d)
    {
        std::cerr << "error, wrong day" << std::endl;
        return 1;
    }
    catch (const wrongMonthException& m)
    {
        std::cerr << "error, wrong month" << std::endl;
        return 1;
    }
    catch (const wrongYearException& y)
    {
        std::cerr << "error, wrong year" << std::endl;
        return 1;
    }
    catch (const std::istream::failure& ex)
    {
        std::cerr << "data error" << ex.what() << std::endl;
        return 2;
    }

    catch (...)
    {
        std::cerr << "other failure" << std::endl;
        return -1;
    }

    return 0;
}
