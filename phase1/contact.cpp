
#include "contact.h"
// TODO: Add needed libraries! 

Email::Email(string type, string email_addr){
    // TODO: Complete me!
    this->type = type;
    this->email_addr = email_addr;
}


void Email::set_contact(){
    // TODO: Do not change the prompts!
	
    cout << "Enter the type of email address: ";
    // some code here
    getline(cin, type);
    cout << "Enter email address: ";
    // some code here
    getline(cin, email_addr);
}


string Email::get_contact(string style){
    // Note: We have default argument in declaration and not in definition!
    if (style=="full")
	    return "(" + type + ") " + email_addr;
    else 
        return email_addr;
}


void Email::print(){
    // Note: get_contact is called with default argument
	cout << "Email" << get_contact() << endl;
}


Phone::Phone(string type, string num){
    // TODO: It is possible that num includes "-" or not, manage it!
    // TODO: Complete this method!
    // Note: We don't want to use C++11! stol is not valid!
    this->type = type;

    long long result = 0;
    for (size_t i = 0; i < num.length(); ++i){
        if (num[i] >= '0' && num[i] <= '9'){
            result = result * 10 + (num[i] - '0');
        }
    }



}


void Phone::set_contact(){
    // TODO: Complete this method
    // Use the same prompts as given!
	cout <<"Enter the type of phone number: ";
    getline(cin, type);
	cout << "Enter the phone number: ";
    string num;
    getline(cin, num);
    long long result = 0;
    for (size_t i = 0; i < num.length(); ++i){
        if (num[i] >= '0' && num[i] <= '9'){
            result = result * 10 + (num[i] - '0');
        }
    }

}


string Phone::get_contact(string style){
    // TODO: Complete this method, get hint from Email 
    string num_str = "";
    long long temp = phone_num;
    if (temp == 0) num_str = "0000000000";
    while (temp > 0){
        num_str = (char)('0' + (temp % 10)) + num_str;
        temp /= 10;
    }
    while (num_str.length() < 10){
        num_str = "0" + num_str;
    }

    string formatted = num_str.substr(0, 3) + "-" + num_str.substr(3,3) +  "=" + num_str.substr(6, 4);

    if (style == "full"){
        return "(" + type + ")" + formatted;
    
    }
    else 
        return formatted;
}


void Phone::print(){
    // Note: get_contact is called with default argument
	cout << "Phone " << get_contact() << endl;
}

