
#include "contact.h"

// ─── Email ────────────────────────────────────────────────────────────────────

Email::Email(string type, string email_addr) {
    this->type       = type;
    this->email_addr = email_addr;
}

void Email::set_contact() {
    cout << "Enter the type of email address: ";
    getline(cin, type);
    cout << "Enter email address: ";
    getline(cin, email_addr);
}

string Email::get_contact(string style) {
    // Note: We have default argument in declaration and not in definition!
    if (style == "full")
        return "(" + type + ") " + email_addr;
    else
        return email_addr;
}

void Email::print() {
    cout << "Email (" << type << "): " << email_addr << endl;
}


// ─── Phone ────────────────────────────────────────────────────────────────────

static long parsePhoneNumber(const string& num) {
    // Strip any non-digit characters (e.g. dashes) then convert to long
    // Note: We don't want to use C++11! stol is not valid!
    string digits;
    for (int i = 0; i < (int)num.size(); i++) {
        if (num[i] >= '0' && num[i] <= '9')
            digits += num[i];
    }
    return atol(digits.c_str());
}

static string formatPhoneNumber(long n) {
    // Format 10-digit number as "XXX-XXX-XXXX"
    long area   = n / 10000000L;
    long middle = (n / 10000L) % 1000L;
    long last   = n % 10000L;
    char buf[20];
    sprintf(buf, "%03ld-%03ld-%04ld", area, middle, last);
    return string(buf);
}

Phone::Phone(string type, string phone_number) {
    // It is possible that num includes "-" or not, manage it!
    // Note: We don't want to use C++11! stol is not valid!
    this->type      = type;
    this->phone_num = parsePhoneNumber(phone_number);
}

void Phone::set_contact() {
    string num;
    cout << "Enter the type of phone number: ";
    getline(cin, type);
    cout << "Enter the phone number: ";
    getline(cin, num);
    phone_num = parsePhoneNumber(num);
}

string Phone::get_contact(string style) {
    if (style == "full")
        return "(" + type + ") " + formatPhoneNumber(phone_num);
    else
        return formatPhoneNumber(phone_num);
}

void Phone::print() {
    cout << "Phone (" << type << "): " << formatPhoneNumber(phone_num) << endl;
}
