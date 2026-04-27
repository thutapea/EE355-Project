#include "person.h"
#include <iostream>
#include <fstream>
#include <string>

Person::Person(){
    next = NULL;
    prev = NULL;
    set_person();
}

Person::~Person(){
    delete birthdate;
    delete email;
    delete phone;
}

Person::Person(string f_name, string l_name, string b_date, string email, string phone){
    this->f_name = f_name;
    this->l_name = l_name;
    this->birthdate = new Date(b_date);
    this->next = NULL;
    this->prev = NULL;

    // Parse full email string: e.g., "(Work) julia@wh.com"
    size_t e_paren = email.find(')');
    string e_type = email.substr(1, e_paren - 1);
    string e_addr = email.substr(e_paren + 2);
    this->email = new Email(e_type, e_addr);

    // Parse full phone string: e.g., "(Home) 310-192-2011"
    size_t p_paren = phone.find(')');
    string p_type = phone.substr(1, p_paren - 1);
    string p_num = phone.substr(p_paren + 2);
    this->phone = new Phone(p_type, p_num);
}

Person::Person(string filename){
    next = NULL;
    prev = NULL;
    set_person(filename);
}

void Person::set_person(){
    string temp;
    string type;

    cout << "First Name: ";
    std::getline(std::cin,f_name);

    cout << "Last Name: ";
    std::getline(std::cin,l_name);

    cout << "Birthdate (M/D/YYYY): ";
    std::getline(std::cin,temp);
    birthdate = new Date(temp); 

    cout << "Type of email address: ";
    std::getline(std::cin, type);
    cout << "Email address: ";
    std::getline(std::cin, temp);
    email = new Email(type, temp);

    cout << "Type of phone number: ";
    std::getline(std::cin, type);
    cout << "Phone number: ";
    std::getline(std::cin, temp);
    phone = new Phone(type, temp);
}

void Person::set_person(string filename){
    std::ifstream file(filename);
    
    if (file.is_open()) {
        std::getline(file, f_name);
        std::getline(file, l_name);
        
        string b_date;
        std::getline(file, b_date);
        birthdate = new Date(b_date);
        
        string p_str;
        std::getline(file, p_str);
        size_t p_paren = p_str.find(')');
        string p_type = p_str.substr(1, p_paren - 1);
        string p_num = p_str.substr(p_paren + 2);
        phone = new Phone(p_type, p_num);
        
        string e_str;
        std::getline(file, e_str);
        size_t e_paren = e_str.find(')');
        string e_type = e_str.substr(1, e_paren - 1);
        string e_addr = e_str.substr(e_paren + 2);
        email = new Email(e_type, e_addr);
        
        file.close();
    } else {
        std::cout << "Unable to open file: " << filename << std::endl;
    }
}

bool Person::operator==(const Person& rhs){
    // Check first name, last name, and dereferenced birthdate
    return (this->f_name == rhs.f_name && 
            this->l_name == rhs.l_name && 
            *(this->birthdate) == *(rhs.birthdate));
}

bool Person::operator!=(const Person& rhs){ 
    return !(*this == rhs);
}

void Person::print_person(){
    cout << l_name <<", " << f_name << endl;
    birthdate->print_date("Month D, YYYY");
    phone->print();
    email->print();
}