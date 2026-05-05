
#ifndef PERSON_H
#define PERSON_H

#include <vector>
#include <map>
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
    map<string, string> metadata;
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
    void addAttribute(string key, string value);
    string getAttribute(string key);
    map<string, string> getMetadata();
    bool operator==(const Person& rhs);
    bool operator!=(const Person& rhs);
};


#endif