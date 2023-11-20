 #include <iostream>

class Date 
{
private:

    int years;
    int months;
    int days;

    void Normalize()
    {
        int daysInMonths[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        if (months != 12)
        {
            years += months / 12;
            months %= 12;
        }

        if (months < 0)
        {
            months = 12 + months;
            years -= 1;
        }

        if ((years % 4 == 0 && years % 100 != 0) || (years % 400 == 0))
        {
            daysInMonths[2] = 29;
        }


        while (days > daysInMonths[months - 1])
        {
            days -= daysInMonths[months - 1];
            months += 1;

            if (months > 12)
            {
                years += months / 12;
                months %= 12;
            }
        }

        while (days <= 0)
        {
            months -= 1;

            if (months < 1)
            {
                months = 12;
                years -= 1;
            }

            days += daysInMonths[months - 1];
        }
    }

public:
    Date(int y, int m, int d);
    int GetYears() const;
    int GetMonths() const;
    int GetDays() const;

    Date(int d) : Date(0, 0, d) {}

    void AddDays(int d)
    {
        days += d;
        Normalize();
    }

    Date operator+ (int d) const
    {
        return Date(years, months, days + d);
    }

    Date& operator += (int d)
    {
        days += d;
        Normalize();
        return *this;
    }

    Date operator- (int d) const
    {
        return Date(years, months, days - d);
    }
};

std::ostream& operator << (std::ostream& out, const Date& d)
{
    out << d.GetYears() << " / " << d.GetMonths() << " / " << d.GetDays();
    return out;
}

std::istream& operator >> (std::istream& in, Date& date)
{
    int y, m, d;
    char c;

    in >> d >> c;
    in >> m >> c;
    in >> y >> c;
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


Date::Date(int y, int m, int d)
{
    years = y;
    months = m;
    days = d;

    Normalize();
}

int main()
{
    Date d(2023, 12, 12);
    std::cout << "\t\tdate : " << d << std::endl;

    d.AddDays(10);
    std::cout << "  date + d.AddDays() : " << d << std::endl;

    d.AddDays(-7);
    std::cout << "  date + d.AddDays() : " << d << std::endl;
}