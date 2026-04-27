/*
 * network.cpp
 *
 * ASSUMPTIONS about teammate code (match these in your other files):
 *
 * Person class (person.h / person.cpp):
 *   - Has public members:  Person* next;  Person* prev;
 *   - Constructor:         Person(string f_name, string l_name, string b_date,
 *                                 string email, string phone)
 *   - Methods:             void print_person()
 *                          string get_fname()   -- returns first name
 *                          string get_lname()   -- returns last name
 *   - Equality operator:   bool operator==(const Person& other)
 *                          (compares fname AND lname only, per assignment spec)
 *   - print_person() output format (5 lines + blank lines between):
 *       LastName, FirstName
 *       <blank>
 *       MonthName Day, Year
 *       <blank>
 *       Phone (Type): ###-###-####
 *       <blank>
 *       Email (Type): address@domain.com
 *
 * misc.h / misc.cpp:
 *   - void printMe(string filename)  -- prints the banner from file
 *
 * The networkDB.txt separator between people is a line of dashes: "----------..."
 * Each person's block has exactly 7 lines (matching print_person output):
 *   Line 1: "LastName, FirstName MiddleName..."
 *   Line 2: blank
 *   Line 3: "MonthName Day, Year"
 *   Line 4: blank
 *   Line 5: "Phone (Type): ###-###-####"
 *   Line 6: blank
 *   Line 7: "Email (Type): address@domain.com"
 */

#include "network.h"
#include "misc.h"
#include <limits>
#include <fstream>
#include <sstream>
#include <iostream>
#include <dirent.h>   // for listing directory files (POSIX)

using namespace std;

// ─────────────────────────────────────────────
//  Constructors / Destructor
// ─────────────────────────────────────────────

Network::Network() {
    head  = NULL;
    tail  = NULL;
    count = 0;
}

Network::Network(string fileName) {
    head  = NULL;
    tail  = NULL;
    count = 0;
    loadDB(fileName);
}

Network::~Network() {
    Person* ptr = head;
    while (ptr != NULL) {
        Person* next = ptr->next;
        delete ptr;
        ptr = next;
    }
    head  = NULL;
    tail  = NULL;
    count = 0;
}

// ─────────────────────────────────────────────
//  push_back
// ─────────────────────────────────────────────

void Network::push_back(Person* newEntry) {
    newEntry->next = NULL;
    newEntry->prev = tail;

    if (tail != NULL)
        tail->next = newEntry;
    else
        head = newEntry;   // list was empty

    tail = newEntry;
    count++;
}

// ─────────────────────────────────────────────
//  search (by Person pointer — uses operator==)
// ─────────────────────────────────────────────

Person* Network::search(Person* searchEntry) {
    Person* ptr = head;
    while (ptr != NULL) {
        if (*ptr == *searchEntry)
            return ptr;
        ptr = ptr->next;
    }
    return NULL;
}

// ─────────────────────────────────────────────
//  search (by first + last name)
// ─────────────────────────────────────────────

Person* Network::search(string fname, string lname) {
    Person* ptr = head;
    while (ptr != NULL) {
        if (ptr->get_fname() == fname && ptr->get_lname() == lname)
            return ptr;
        ptr = ptr->next;
    }
    return NULL;
}

// ─────────────────────────────────────────────
//  remove
// ─────────────────────────────────────────────

bool Network::remove(string fname, string lname) {
    Person* target = search(fname, lname);
    if (target == NULL)
        return false;

    // Patch previous node
    if (target->prev != NULL)
        target->prev->next = target->next;
    else
        head = target->next;   // removing head

    // Patch next node
    if (target->next != NULL)
        target->next->prev = target->prev;
    else
        tail = target->prev;   // removing tail

    delete target;
    count--;
    return true;
}

// ─────────────────────────────────────────────
//  loadDB
//
//  Expected file format (same as print_person output):
//
//  Louis-Dreyfus, Julia Scarlett Elizabeth
//
//  January 13, 1961
//
//  Phone (Home): 310-192-2847
//
//  Email (Work): veep@wh.gov
//  ----------...
//  <next person>
//
//  We parse:
//    lname  <- everything before the first comma on line 1
//    fname  <- everything after ", " on line 1
//    bdate  <- line 3  (e.g. "January 13, 1961")
//    phone  <- digits/dashes from line 5 (e.g. "310-192-2847")
//    email  <- address from line 7 (e.g. "veep@wh.gov")
//
//  Phone type and email type are discarded here; the Person constructor
//  that receives the raw phone/email strings can handle defaults.
// ─────────────────────────────────────────────

void Network::loadDB(string filename) {
    // Erase current list first
    Person* ptr = head;
    while (ptr != NULL) {
        Person* nxt = ptr->next;
        delete ptr;
        ptr = nxt;
    }
    head  = NULL;
    tail  = NULL;
    count = 0;

    ifstream inFile(filename.c_str());
    if (!inFile.is_open()) {
        cout << "Error: could not open " << filename << endl;
        return;
    }

    string line;
    while (true) {
        // ── Line 1: "LastName, FirstName ..."
        string nameLine;
        if (!getline(inFile, nameLine)) break;

        // Skip separator lines or blank lines between records
        if (nameLine.empty() || nameLine.find("---") != string::npos)
            continue;

        size_t commaPos = nameLine.find(',');
        if (commaPos == string::npos) continue;   // malformed line

        string lname = nameLine.substr(0, commaPos);
        string fname = nameLine.substr(commaPos + 2); // skip ", "

        // ── Line 2: blank
        getline(inFile, line);

        // ── Line 3: birth date  e.g. "January 13, 1961"
        string bdate;
        getline(inFile, bdate);

        // ── Line 4: blank
        getline(inFile, line);

        // ── Line 5: "Phone (Type): ###-###-####"
        string phoneLine;
        getline(inFile, phoneLine);
        string phoneNum = "";
        size_t colonPos = phoneLine.find(':');
        if (colonPos != string::npos) {
            phoneNum = phoneLine.substr(colonPos + 2); // skip ": "
        }

        // ── Line 6: blank
        getline(inFile, line);

        // ── Line 7: "Email (Type): address@domain.com"
        string emailLine;
        getline(inFile, emailLine);
        string emailAddr = "";
        colonPos = emailLine.find(':');
        if (colonPos != string::npos) {
            emailAddr = emailLine.substr(colonPos + 2); // skip ": "
        }

        // Build and add the Person
        Person* newPerson = new Person(fname, lname, bdate, emailAddr, phoneNum);
        push_back(newPerson);
    }

    inFile.close();
}

// ─────────────────────────────────────────────
//  saveDB
//
//  Saves all people using print_person() format,
//  separated by a line of dashes (matching networkDB.txt).
// ─────────────────────────────────────────────

void Network::saveDB(string filename) {
    ofstream outFile(filename.c_str());
    if (!outFile.is_open()) {
        cout << "Error: could not open " << filename << " for writing." << endl;
        return;
    }

    // Redirect cout to the file temporarily
    streambuf* oldBuf = cout.rdbuf(outFile.rdbuf());

    Person* ptr = head;
    while (ptr != NULL) {
        ptr->print_person();
        if (ptr->next != NULL)
            cout << "------------------------------" << endl;
        ptr = ptr->next;
    }

    // Restore cout
    cout.rdbuf(oldBuf);
    outFile.close();
}

// ─────────────────────────────────────────────
//  printDB  (provided — do not modify)
// ─────────────────────────────────────────────

void Network::printDB() {
    cout << "Number of people: " << count << endl;
    cout << "------------------------------" << endl;
    Person* ptr = head;
    while (ptr != NULL) {
        ptr->print_person();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}

// ─────────────────────────────────────────────
//  push_front  (provided — do not modify)
// ─────────────────────────────────────────────

void Network::push_front(Person* newEntry) {
    newEntry->prev = NULL;
    newEntry->next = head;

    if (head != NULL)
        head->prev = newEntry;
    else
        tail = newEntry;

    head = newEntry;
    count++;
}

// ─────────────────────────────────────────────
//  Helper: list all .txt files in current directory
// ─────────────────────────────────────────────

static void listTxtFiles() {
    DIR* dir = opendir(".");
    if (dir == NULL) return;

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        string name = entry->d_name;
        if (name.size() > 4 && name.substr(name.size() - 4) == ".txt")
            cout << "  " << name << endl;
    }
    closedir(dir);
}

// ─────────────────────────────────────────────
//  Helper: check if a file exists
// ─────────────────────────────────────────────

static bool fileExists(const string& filename) {
    ifstream f(filename.c_str());
    return f.good();
}

// ─────────────────────────────────────────────
//  showMenu
// ─────────────────────────────────────────────

void Network::showMenu() {
    int opt;
    while (1) {
        cout << "\033[2J\033[1;1H";
        printMe("banner");

        cout << "Select from below: \n";
        cout << "1. Save network database \n";
        cout << "2. Load network database \n";
        cout << "3. Add a new person \n";
        cout << "4. Remove a person \n";
        cout << "5. Print people with last name \n";
        cout << "6. Exit \n";
        cout << "\nSelect an option ... ";

        if (cin >> opt) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Wrong option! " << endl;
            return;
        }

        string fname, lname, fileName, bdate, email, phone;
        cout << "\033[2J\033[1;1H";

        // ── Option 1: Save ──────────────────────────────────────
        if (opt == 1) {
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            getline(cin, fileName);
            saveDB(fileName);
            cout << "Network saved in " << fileName << endl;
        }

        // ── Option 2: Load ──────────────────────────────────────
        else if (opt == 2) {
            cout << "Loading network database \n";
            cout << "Available .txt files in current directory:\n";
            listTxtFiles();

            cout << "Enter the name of the load file: ";
            getline(cin, fileName);

            if (!fileExists(fileName)) {
                cout << "File " << fileName << " does not exist!" << endl;
            } else {
                loadDB(fileName);
                cout << "Network loaded from " << fileName
                     << " with " << count << " people \n";
            }
        }

        // ── Option 3: Add ───────────────────────────────────────
        else if (opt == 3) {
            cout << "Adding a new person \n";
            cout << "First name: ";
            getline(cin, fname);
            cout << "Last name: ";
            getline(cin, lname);

            if (search(fname, lname) != NULL) {
                cout << "Person already exists! \n";
            } else {
                cout << "Birth date (MM/DD/YYYY): ";
                getline(cin, bdate);
                cout << "Email address: ";
                getline(cin, email);
                cout << "Phone number (###-###-####): ";
                getline(cin, phone);

                Person* newPerson = new Person(fname, lname, bdate, email, phone);
                push_front(newPerson);
                cout << "Person added successfully! \n";
            }
        }

        // ── Option 4: Remove ────────────────────────────────────
        else if (opt == 4) {
            cout << "Removing a person \n";
            cout << "First name: ";
            getline(cin, fname);
            cout << "Last name: ";
            getline(cin, lname);

            if (remove(fname, lname))
                cout << "Remove Successful! \n";
            else
                cout << "Person not found! \n";
        }

        // ── Option 5: Print by last name ────────────────────────
        else if (opt == 5) {
            cout << "Print people with last name \n";
            cout << "Last name: ";
            getline(cin, lname);

            bool found = false;
            Person* ptr = head;
            while (ptr != NULL) {
                if (ptr->get_lname() == lname) {
                    ptr->print_person();
                    cout << "------------------------------" << endl;
                    found = true;
                }
                ptr = ptr->next;
            }
            if (!found)
                cout << "Person not found! \n";
        }
        else if (opt == 6) {
                cout << "Goodbye!\n";
            return;  // exits the while loop and showMenu function
            }

        else {
            cout << "Nothing matched!\n";
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        getline(cin, temp);
        cout << "\033[2J\033[1;1H";
    }
}