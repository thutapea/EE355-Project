
#ifndef PERSON_H
#define PERSON_H

#include <vector>
#include "date.h"
#include "contact.h"
#include "fstream"
class Person{
    friend class Network;

private:
	string f_name;
	string l_name;
	Date *birthdate;
    Email *email;
    Phone *phone;
    vector<Person*> myfriends;
    // the following to attributes are used in the linked list.
    Person* next;
    Person* prev;

public: 
    Person();
    ~Person();
    Person(string filename);
    Person(string f_name, string l_name, string b_date, string email, string phone);
	void print_person();
    void print_friends();
	void set_person();
	void set_person(string filename);
    void makeFriend(Person* newFriend);
    bool operator==(const Person& rhs);
    bool operator!=(const Person& rhs);
};


#endif