#include "test_runner.h"

#include "airline_ticket.h"

bool operator < (Date lhs, Date rhs)
{
	if (lhs.year < rhs.year)
	{
		return true;
	}
	else if (lhs.year == rhs.year && lhs.month < rhs.month)
	{
		return true;
	}
	else if (lhs.year == rhs.year && lhs.month == rhs.month && lhs.day < rhs.day)
	{
		return true;
	}
	return false;
}
bool operator > (Date lhs, Date rhs)
{
	if (!(lhs < rhs))
	{
		return true;
	}
	return false;
}
bool operator == (Date lhs, Date rhs)
{
	return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
}
bool operator != (Date lhs, Date rhs)
{
	if (!(lhs == rhs))
	{
		return true;
	}
	return false;
}
istream& operator >> (istream& is, Date& date)
{
	is >> date.year;
	is.ignore(1);
	is >> date.month;
	is.ignore(1);
	is >> date.day;
	return is;
}
std::ostream& operator << (std::ostream& os, const Date& date)
{
	std::stringstream ss;
	ss << date.year << '.' << date.month << '.' << date.day;
	os << ss.str();
	return os;
}

bool operator < (Time lhs, Time rhs)
{
	if (lhs.hours < rhs.hours)
	{
		return true;
	}
	else if (lhs.hours == rhs.hours && lhs.minutes < rhs.minutes)
	{
		return true;
	}
	return false;
}
bool operator > (Time lhs, Time rhs)
{
	if (!(lhs < rhs))
	{
		return true;
	}
	return false;
}
bool operator == (Time lhs, Time rhs)
{
	return tie(lhs.hours, lhs.minutes) == tie(rhs.hours, rhs.minutes);
}
bool operator != (Time lhs, Time rhs)
{
	if (!(lhs == rhs))
	{
		return true;
	}
	return false;
}
istream& operator >> (istream& is, Time& time)
{
	is >> time.hours;
	is.ignore(1);
	is >> time.minutes;
	return is;
}
std::ostream& operator << (std::ostream& os, const Time& time)
{
	std::stringstream ss;
	ss << time.hours << ':' << time.minutes;
	os << ss.str();
	return os;
}

//Реализуйте этот макрос, а также необходимые операторы для классов Date и Time

#define UPDATE_FIELD(ticket, field, values) \
{											\
    auto it = values.find(#field);          \
    if (it != values.end())					\
	{										\
		istringstream is(it->second);       \
		is >> ticket.field;                 \
	}                                       \
}

void TestUpdate() 
{
	AirlineTicket t;
	t.price = 0;

	const map<string, string> updates1 = 
	{
	  {"departure_date", "2018-2-28"},
	  {"departure_time", "17:40"},
	};
	UPDATE_FIELD(t, departure_date, updates1);
	UPDATE_FIELD(t, departure_time, updates1);
	UPDATE_FIELD(t, price, updates1);

	ASSERT_EQUAL(t.departure_date, (Date{ 2018, 2, 28 }));
	ASSERT_EQUAL(t.departure_time, (Time{ 17, 40 }));
	ASSERT_EQUAL(t.price, 0);

	const map<string, string> updates2 = 
	{
	  {"price", "12550"},
	  {"arrival_time", "20:33"},
	};
	UPDATE_FIELD(t, departure_date, updates2);
	UPDATE_FIELD(t, departure_time, updates2);
	UPDATE_FIELD(t, arrival_time, updates2);
	UPDATE_FIELD(t, price, updates2);

	// updates2 не содержит ключей "departure_date" и "departure_time", поэтому
	// значения этих полей не должны измениться
	ASSERT_EQUAL(t.departure_date, (Date{ 2018, 2, 28 }));
	ASSERT_EQUAL(t.departure_time, (Time{ 17, 40 }));
	ASSERT_EQUAL(t.price, 12550);
	ASSERT_EQUAL(t.arrival_time, (Time{ 20, 33 }));
}

int main() 
{
	TestRunner tr;
	RUN_TEST(tr, TestUpdate);
}
