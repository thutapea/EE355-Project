#include "contact.h"

Email::Email(string type, string email_addr) {
    this->type = type;
    this->email_addr = email_addr;
}

void Email::set_contact() {
    cout << "Enter the type of email address: ";
    cin >> type;
    cout << "Enter email address: ";
    cin >> email_addr;
}

string Email::get_contact(string style) {
    if (style == "full")
        return "(" + type + ") " + email_addr;
    else 
        return email_addr;
}

void Email::print() {
    cout << "Email " << get_contact() << endl;
}

Phone::Phone(string type, string num) {
    this->type = type;
    
    // Clean the input string to remove any dashes
    string clean_num = "";
    for(size_t i = 0; i < num.length(); i++) {
        if(num[i] != '-') {
            clean_num += num[i];
        }
    }
    this->phone_num = clean_num;
}

void Phone::set_contact() {
    cout << "Enter the type of phone number: ";
    cin >> type;
    cout << "Enter the phone number: ";
    string raw_num;
    cin >> raw_num;
    
    string clean_num = "";
    for(size_t i = 0; i < raw_num.length(); i++) {
        if(raw_num[i] != '-') {
            clean_num += raw_num[i];
        }
    }
    this->phone_num = clean_num;
}

string Phone::get_contact(string style) {
    // Format the phone number to "XXX-XXX-XXXX"
    string formatted = "";
    if (phone_num.length() == 10) {
        formatted = phone_num.substr(0, 3) + "-" + phone_num.substr(3, 3) + "-" + phone_num.substr(6);
    } else {
        formatted = phone_num; // Fallback if number isn't exactly 10 digits
    }

    if (style == "full")
        return "(" + type + ") " + formatted;
    else 
        return formatted;
}

void Phone::print() {
    cout << "Phone " << get_contact() << endl;
}