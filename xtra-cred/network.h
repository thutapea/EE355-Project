
#ifndef NETWORK_H
#define NETWORK_H

#include "person.h"
#include "date.h"
#include <stdlib.h>
#include <dirent.h>

class Network{

    private:
        Person* head;
        Person* tail;
        int count;
        double calculateSimilarity(Person* user1, Person* user2);

    public:
        Person* search(Person* searchEntry);
        Person* search(string fname, string lname);
        Network();
        Network(string fileName);
        ~Network();
        void printDB();
        void push_front(Person* newEntry);
        void push_back(Person* newEntry);
        bool remove(string fname, string lname);
        void loadDB(string filename);
        void saveDB(string filename);
        void showMenu();
        void recommendFriends(string fname, string lname, int topN);
};

#endif
