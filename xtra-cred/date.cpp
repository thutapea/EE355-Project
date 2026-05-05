
#include "date.h"

static const string MONTH_NAMES[] = {
    "", "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

Date::Date(string date_str) {
    // Parse "M/D/YYYY" or "MM/DD/YYYY"
    int slash1 = date_str.find('/');
    int slash2 = date_str.find('/', slash1 + 1);
    month = atoi(date_str.substr(0, slash1).c_str());
    day   = atoi(date_str.substr(slash1 + 1, slash2 - slash1 - 1).c_str());
    year  = atoi(date_str.substr(slash2 + 1).c_str());
}

void Date::print_date(string format) {
    if (format == "Month D, YYYY") {
        cout << MONTH_NAMES[month] << " " << day << ", " << year << endl;
    }
}

string Date::get_date_str() {
    char buf[20];
    sprintf(buf, "%d/%d/%d", month, day, year);
    return string(buf);
}

bool Date::operator==(const Date& rhs) {
    return month == rhs.month && day == rhs.day && year == rhs.year;
}
