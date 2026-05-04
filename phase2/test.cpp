#include "network.h"
#include <iostream>
#include "misc.h"
using namespace std;


int main() {
    Network net("networkDB.txt");  // load file
    
    net.showMenu();
    

    return 0;
}

