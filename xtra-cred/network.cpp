
#include "network.h"
#include <limits>
#include "misc.h"
#include <fstream>
#include <string>

// ─── Constructors / Destructor ────────────────────────────────────────────────

Network::Network() {
    head = NULL;
    tail = NULL;
    count = 0;
}


Network::Network(string fileName) {
    head = NULL; tail = NULL; count = 0;
    loadDB(fileName);
}

Network::~Network() {
    Person* ptr = head;
    while (ptr != NULL) {
        Person* next = ptr->next;
        delete ptr;
        ptr = next;
    }
}


// ─── Search ───────────────────────────────────────────────────────────────────

Person* Network::search(Person* searchEntry) {
    // Searches the Network for searchEntry
    // if found, returns a pointer to it, else returns NULL
    Person* ptr = head;
    while (ptr != NULL) {
        if (*ptr == *searchEntry)
            return ptr;
        ptr = ptr->next;
    }
    return NULL;
}


Person* Network::search(string fname, string lname) {
    // Search by first and last name only
    // if found, returns a pointer to it, else returns NULL
    Person* ptr = head;
    while (ptr != NULL) {
        if (ptr->f_name == fname && ptr->l_name == lname)
            return ptr;
        ptr = ptr->next;
    }
    return NULL;
}


// ─── Load / Save ──────────────────────────────────────────────────────────────

void Network::loadDB(string filename) {
    // Erase current list first
    Person* ptr = head;
    while (ptr != NULL) {
        Person* next = ptr->next;
        delete ptr;
        ptr = next;
    }
    head = tail = NULL;
    count = 0;

    ifstream file(filename.c_str());
    string fname;
    while (getline(file, fname)) {
        // Skip separator lines and blank lines
        if (fname.empty() || fname.find("---") != string::npos)
            continue;

        string lname, date_str, line1, line2;
        if (!getline(file, lname))   break;
        if (!getline(file, date_str)) break;
        if (!getline(file, line1))   break;
        if (!getline(file, line2))   break;

        // Detect email vs phone by '@'
        string emailStr, phoneStr;
        if (line1.find('@') != string::npos) {
            emailStr = line1; phoneStr = line2;
        } else {
            phoneStr = line1; emailStr = line2;
        }

        Person* p = new Person(fname, lname, date_str, emailStr, phoneStr);
        push_back(p);
    }
    file.close();
}

void Network::saveDB(string filename) {
    // Save all Person info in the loadable file format
    ofstream file(filename.c_str());
    Person* ptr = head;
    while (ptr != NULL) {
        file << ptr->f_name << "\n";
        file << ptr->l_name << "\n";
        file << ptr->birthdate->get_date_str() << "\n";
        file << ptr->email->get_contact("full") << "\n";
        file << ptr->phone->get_contact("full") << "\n";
        file << "--------------------\n";
        ptr = ptr->next;
    }
    file.close();
}


// ─── printDB ──────────────────────────────────────────────────────────────────

void Network::printDB() {
    // Leave me alone! I know how to print!
    // Note: Notice that we don't need to update this even after adding to Person attributes
    // This is a feature of OOP, classes are supposed to take care of themselves!
    cout << "Number of people: " << count << endl;
    cout << "------------------------------" << endl;
    Person* ptr = head;
    while (ptr != NULL) {
        ptr->print_person();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}


// ─── push_front / push_back ───────────────────────────────────────────────────

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


void Network::push_back(Person* newEntry) {
    // Adds a new Person (newEntry) to the back of LL
    newEntry->next = NULL;
    newEntry->prev = tail;

    if (tail != NULL)
        tail->next = newEntry;
    else
        head = newEntry;

    tail = newEntry;
    count++;
}


// ─── remove ───────────────────────────────────────────────────────────────────

bool Network::remove(string fname, string lname) {
    Person* target = search(fname, lname);
    if (target == NULL)
        return false;

    if (target->prev != NULL)
        target->prev->next = target->next;
    else
        head = target->next;

    if (target->next != NULL)
        target->next->prev = target->prev;
    else
        tail = target->prev;

    delete target;
    count--;
    return true;
}

// helper function to get rid of email and phone number descriptors
static string getValueOnly(string s) {
    int pos = s.find(')');
    if (pos != string::npos) {
        return s.substr(pos + 2);
    }
    return s;
}

// ─── showMenu ─────────────────────────────────────────────────────────────────

void Network::showMenu() {
    // All the prompts are given to you,
    // You should add code before, between and after prompts!

    int opt;
    while (1) {
        cout << "\033[2J\033[1;1H";
        printMe("banner"); // from misc library

        cout << "Select from below: \n";
        cout << "1. Save network database \n";
        cout << "2. Load network database \n";
        cout << "3. Add a new person \n";
        cout << "4. Remove a person \n";
        cout << "5. Print people with last name  \n";
        cout << "6. Connect \n";
        cout << "7. Wise Search \n";
        cout << "8. Friend Recommendations \n";
        cout << "\nSelect an option ... ";

        if (cin >> opt) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Wrong option! " << endl;
            return;
        }

        string fname, lname, fileName, bdate;
        cout << "\033[2J\033[1;1H";

        if (opt == 1) {
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            getline(cin, fileName);
            saveDB(fileName);
            cout << "Network saved in " << fileName << endl;
        }
        else if (opt == 2) {
            cout << "Loading network database \n";
            // Print all .txt files in the current directory
            DIR* dir = opendir(".");
            struct dirent* entry;
            if (dir != NULL) {
                while ((entry = readdir(dir)) != NULL) {
                    string name = entry->d_name;
                    if (name.size() >= 4 &&
                        name.substr(name.size() - 4) == ".txt")
                        cout << name << "\n";
                }
                closedir(dir);
            }
            cout << "Enter the name of the load file: ";
            getline(cin, fileName);
            ifstream test(fileName.c_str());
            if (!test.good()) {
                cout << "File " << fileName << " does not exist!" << endl;
            } else {
                test.close();
                loadDB(fileName);
                cout << "Network loaded from " << fileName
                     << " with " << count << " people \n";
            }
        }
        else if (opt == 3) {
            // Add a new Person ONLY if it does not exist; use push_front
            cout << "Adding a new person \n";
            Person* p = new Person();
            if (search(p) != NULL) {
                cout << "Person already exists!\n";
                delete p;
            } else {
                push_front(p);
                cout << "Person added!\n";
            }
        }
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
        else if (opt == 5) {
            // Print all people with the given last name
            cout << "Print people with last name \n";
            cout << "Last name: ";
            getline(cin, lname);
            bool found = false;
            Person* ptr = head;
            while (ptr != NULL) {
                if (ptr->l_name == lname) {
                    ptr->print_person();
                    cout << "------------------------------\n";
                    found = true;
                }
                ptr = ptr->next;
            }
            if (!found)
                cout << "Person not found! \n";
        }
        else if (opt == 6) {
            cout << "Make friends\n";

            cout << "Person 1\n";
            cout << "First Name: ";
            getline(cin, fname);
            cout << "Last Name: ";
            getline(cin, lname);

            Person* p1 = search(fname, lname);
            if (p1 == NULL) {
                cout << "Person not found" << endl;
            }
            else {
                string fname2, lname2;

                cout << "Person 2\n";
                cout << "First Name: ";
                getline(cin, fname2);
                cout << "Last Name: ";
                getline(cin, lname2);

                Person* p2 = search(fname2, lname2);
                if (p2 == NULL) {
                    cout << "Person not found" << endl;
                }
                else {
                    cout << endl;
                    p1->print_person();
                    cout << endl;
                    p2->print_person();

                    p1->makeFriend(p2);
                    p2->makeFriend(p1);
                }
            }
        }
        else if (opt == 7) {
            cout << "Wise Search\n";
            cout << "Search By:\n";

            string searchStr;
            getline(cin, searchStr);

            bool found = false;
            Person* ptr = head;

            while (ptr != NULL) {
                string phoneStr = getValueOnly(ptr->phone->get_contact("full"));
                string emailStr = getValueOnly(ptr->email->get_contact("full"));

                if (ptr->f_name == searchStr ||
                    ptr->l_name == searchStr ||
                    ptr->birthdate->get_date_str() == searchStr ||
                    phoneStr == searchStr ||
                    emailStr == searchStr) {

                    cout << endl;
                    ptr->print_person();
                    found = true;
                    break;
                }

                ptr = ptr->next;
            }

            if (!found) {
                cout << "Person not found" << endl;
            }
        }
        else if (opt == 8) {
            cout << "Friend Recommendations\n";
            cout << "Enter first name: ";
            getline(cin, fname);
            cout << "Enter last name: ";
            getline(cin, lname);
            
            recommendFriends(fname, lname, 5);
        }
        else {
            cout << "Nothing matched!\n";
        }

        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        std::getline(std::cin, temp);
        cout << "\033[2J\033[1;1H";
    }
}

// ─── Recommendation System ─────────────────────────────────────────────────────

double Network::calculateSimilarity(Person* user1, Person* user2) {
    double score = 0.0;
    double maxScore = 0.0;

    // Age difference (max 25 points) - closer age is better
    int age1 = user1->birthdate->get_date_str()[user1->birthdate->get_date_str().length() - 4] - '0';
    int age2 = user2->birthdate->get_date_str()[user2->birthdate->get_date_str().length() - 4] - '0';
    int yearDiff = abs(age1 - age2);
    if (yearDiff <= 5) score += 25;
    else if (yearDiff <= 10) score += 15;
    else if (yearDiff <= 20) score += 5;
    maxScore += 25;

    // Email domain similarity (max 20 points)
    string email1 = user1->email->get_contact("full");
    string email2 = user2->email->get_contact("full");
    size_t at1 = email1.find('@');
    size_t at2 = email2.find('@');
    if (at1 != string::npos && at2 != string::npos) {
        string domain1 = email1.substr(at1);
        string domain2 = email2.substr(at2);
        if (domain1 == domain2) score += 20;
    }
    maxScore += 20;

    // Phone area code similarity (max 15 points)
    string phone1 = user1->phone->get_contact("full");
    string phone2 = user2->phone->get_contact("full");
    if (phone1.length() >= 3 && phone2.length() >= 3) {
        if (phone1.substr(1, 3) == phone2.substr(1, 3)) score += 15;
    }
    maxScore += 15;

    // Metadata attributes matching (max 40 points)
    map<string, string> meta1 = user1->getMetadata();
    map<string, string> meta2 = user2->getMetadata();
    
    // College match
    if (!meta1["college"].empty() && !meta2["college"].empty()) {
        if (meta1["college"] == meta2["college"]) score += 15;
    }
    
    // Field of study match
    if (!meta1["field"].empty() && !meta2["field"].empty()) {
        if (meta1["field"] == meta2["field"]) score += 15;
    }
    
    // Zip code match
    if (!meta1["zip"].empty() && !meta2["zip"].empty()) {
        if (meta1["zip"] == meta2["zip"]) score += 10;
    }
    
    maxScore += 40;

    // Normalize score to 0-100
    if (maxScore > 0) {
        return (score / maxScore) * 100;
    }
    return 0.0;
}

void Network::recommendFriends(string fname, string lname, int topN) {
    Person* user = search(fname, lname);
    if (user == NULL) {
        cout << "Person not found!\n";
        return;
    }

    cout << "\n--- Friend Recommendations for " << fname << " " << lname << " ---\n\n";

    // Calculate similarity scores for all users
    vector<pair<Person*, double>> scores;
    Person* ptr = head;
    
    while (ptr != NULL) {
        // Skip the user themselves and already connected friends
        if (ptr->f_name != fname || ptr->l_name != lname) {
            bool isFriend = false;
            for (int i = 0; i < user->myfriends.size(); i++) {
                if (user->myfriends[i] == ptr) {
                    isFriend = true;
                    break;
                }
            }
            
            if (!isFriend) {
                double sim = calculateSimilarity(user, ptr);
                scores.push_back(make_pair(ptr, sim));
            }
        }
        ptr = ptr->next;
    }

    // Sort by similarity score (descending)
    for (int i = 0; i < scores.size(); i++) {
        for (int j = 0; j < scores.size() - 1; j++) {
            if (scores[j].second < scores[j + 1].second) {
                pair<Person*, double> temp = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = temp;
            }
        }
    }

    // Print top N recommendations
    int count = (topN < scores.size()) ? topN : scores.size();
    if (count == 0) {
        cout << "No recommendations available.\n";
        return;
    }

    for (int i = 0; i < count; i++) {
        cout << (i + 1) << ". " << scores[i].first->l_name << ", " 
             << scores[i].first->f_name << " (Compatibility: " 
             << (int)scores[i].second << "%)\n";
    }
    cout << endl;
}