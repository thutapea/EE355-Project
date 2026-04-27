#ifndef DATE_H
#define DATE_H

#include <string>
using namespace std;

class Date {
private:
    int month;
    int day;
    int year;

public:
    //constructor that takes date as string
    Date(string date);

    //prints date with name of month
    void print_date();

    //helper function converting month from number into string
    string monthToString();
};

#endif