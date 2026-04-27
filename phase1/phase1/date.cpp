#include "date.h"
#include <iostream>

using namespace std;

Date::Date(string date) {
    int i = 0;
    string temp = "";

    //input month into a string
    while (date[i] != '/') {
        temp += date[i];
        i++;
    }
    month = stoi(temp); //convert to int, which removes leading 0s
    
    
    i++; //skip slash
    temp = ""; //reset temp var
    //repeat process to get day
    while (date[i] != '/') {
        temp += date[i];
        i++;
    }
    day = stoi(temp);
    
    
    i++;
    temp = "";
    //get remaining numbers as the year
    while (i < date.length()) {
        temp += date[i];
        i++;
    }
    year = stoi(temp);
}

// convert month number to name
string Date::monthToString() {
    if (month == 1) return "January";
    if (month == 2) return "February";
    if (month == 3) return "March";
    if (month == 4) return "April";
    if (month == 5) return "May";
    if (month == 6) return "June";
    if (month == 7) return "July";
    if (month == 8) return "August";
    if (month == 9) return "September";
    if (month == 10) return "October";
    if (month == 11) return "November";
    if (month == 12) return "December";

    return "Invalid";
}

// print in format: January 13, 1961
void Date::print_date() {
    cout << monthToString() << " " << day << ", " << year << endl;
}