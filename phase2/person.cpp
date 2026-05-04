#include "misc.h"
#include "person.h"
#include <fstream>

// helpers

// Parse type from "(Type) value" → "Type"
static string extractType(const string& s) {
    int end = s.find(')');
    return s.substr(1, end - 1);
}

// Parse value from "(Type) value" → "value"
static string extractValue(const string& s) {
    int end = s.find(')');
    return s.substr(end + 2);   // skip ') '
}

// ─── Constructors / Destructor ────────────────────────────────────────────────
Person::Person() {
    // I'm already done!
    next = prev = NULL;
    set_person();
}


Person::~Person() {
    delete birthdate;
    delete email;
    delete phone;
}


Person::Person(string fn, string ln, string b_date, string emailStr, string phoneStr) {
    // phone and email strings are in full version, e.g. "(Work) julia@wh.com"
    f_name = fn;
    l_name = ln;
    birthdate = new Date(b_date);
    email = new Email(extractType(emailStr), extractValue(emailStr));
    phone = new Phone(extractType(phoneStr), extractValue(phoneStr));
    next = prev = NULL;
}


Person::Person(string filename) {
    next = prev = NULL;
    set_person(filename);
}


// ─── set_person ───────────────────────────────────────────────────────────────
void Person::set_person() {
    // prompts for the information of the user from the terminal
    // first/last name can have spaces!
    // date format must be "M/D/YYYY"
    // We are sure user enters info in correct format.

    string temp, emailType, emailAddr, phoneType, phoneNum;

    cout << "First Name: ";
    // pay attention to how we read first name, as it can have spaces!
    std::getline(std::cin, f_name);

    cout << "Last Name: ";
    std::getline(std::cin, l_name);

    cout << "Birthdate (M/D/YYYY): ";
    std::getline(std::cin, temp);
    // pay attention to how we passed argument to the constructor of a new object created dynamically using new command
    birthdate = new Date(temp);

    cout << "Type of email address: ";
    std::getline(std::cin, emailType);
    cout << "Email address: ";
    std::getline(std::cin, emailAddr);
    email = new Email(emailType, emailAddr);

    cout << "Type of phone number: ";
    std::getline(std::cin, phoneType);
    cout << "Phone number: ";
    std::getline(std::cin, phoneNum);
    phone = new Phone(phoneType, phoneNum);
}


void Person::set_person(string filename) {
    // reads a Person from a file
    // Look at person_template files as examples.
    // Phone number in files can have '-' or not.
    ifstream file(filename.c_str());

    string fname, lname, date_str, line1, line2;
    getline(file, fname);
    getline(file, lname);
    getline(file, date_str);
    getline(file, line1);
    getline(file, line2);
    file.close();

    f_name = fname;
    l_name = lname;
    birthdate = new Date(date_str);

    // Detect which line is email vs phone by the '@' character
    string emailLine, phoneLine;
    if (line1.find('@') != string::npos) {
        emailLine = line1;
        phoneLine = line2;
    } else {
        phoneLine = line1;
        emailLine = line2;
    }

    email = new Email(extractType(emailLine), extractValue(emailLine));
    phone = new Phone(extractType(phoneLine), extractValue(phoneLine));
}


// ─── Operators ────────────────────────────────────────────────────────────────
bool Person::operator==(const Person& rhs) {
    // check first name, last name, and birthday
    // refer to bool Date::operator==(const Date& rhs)
    return f_name == rhs.f_name && l_name == rhs.l_name &&
           *birthdate == *rhs.birthdate;
}

bool Person::operator!=(const Person& rhs) {
    return !(*this == rhs);
}

// Make Friend
void Person::makeFriend(Person* newFriend) {
    // do nothing if already friends
    for (int i = 0; i < myfriends.size(); i++) {
        if (myfriends[i] == newFriend) {
            return;
        }
    }

    myfriends.push_back(newFriend);
}


// ─── print_person ─────────────────────────────────────────────────────────────
void Person::print_person() {
    cout << l_name << ", " << f_name << endl;
    birthdate->print_date("Month D, YYYY");
    phone->print();
    email->print();

    print_friends();
}

// ─── print friends ────────────────────────────────────────────────────────────
void Person::print_friends() {
    if (myfriends.size() == 0) {
        return;
    }

    vector<Person*> temp = myfriends;

    for (int i = 0; i < temp.size(); i++) {
        for (int j = 0; j < temp.size() - 1; j++) {
            string code1 = codeName(temp[j]->f_name, temp[j]->l_name);
            string code2 = codeName(temp[j + 1]->f_name, temp[j + 1]->l_name);

            char c1_1 = code1[0];
            char c1_2 = code1[1];
            char c2_1 = code2[0];
            char c2_2 = code2[1];

            if (c1_1 > c2_1 || (c1_1 == c2_1 && c1_2 > c2_2)) {
                Person* t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
    }

    cout << "--------------------------------" << endl << endl;

    for (int i = 0; i < temp.size(); i++) {
        cout << temp[i]->f_name << ", " << temp[i]->l_name << endl;

        if (i != temp.size() - 1) {
            cout << endl;
        }
    }
}