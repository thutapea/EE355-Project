
#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
using namespace std;

class Date {
private:
    int month, day, year;
public:
    Date(string date_str);
    void print_date(string format);
    string get_date_str();
    bool operator==(const Date& rhs);
};

#endif
