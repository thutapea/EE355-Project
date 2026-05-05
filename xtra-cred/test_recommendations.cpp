#include "network.h"
#include <iostream>
#include "misc.h"
using namespace std;

void setupTestMetadata(Network& net) {
    // Setup metadata for test users to demonstrate recommendations
    // Format: College, Field, Zip code for similarity scoring
    
    net.search("Julia Scarlett Elizabeth", "Louis-Dreyfus")->addAttribute("college", "Harvard");
    net.search("Julia Scarlett Elizabeth", "Louis-Dreyfus")->addAttribute("field", "Political Science");
    net.search("Julia Scarlett Elizabeth", "Louis-Dreyfus")->addAttribute("zip", "90210");
    
    net.search("Alice", "Johnson")->addAttribute("college", "USC");
    net.search("Alice", "Johnson")->addAttribute("field", "Computer Science");
    net.search("Alice", "Johnson")->addAttribute("zip", "90210");
    
    net.search("Bob", "Smith")->addAttribute("college", "USC");
    net.search("Bob", "Smith")->addAttribute("field", "Computer Science");
    net.search("Bob", "Smith")->addAttribute("zip", "90001");
    
    net.search("Carol", "Williams")->addAttribute("college", "Stanford");
    net.search("Carol", "Williams")->addAttribute("field", "Business");
    net.search("Carol", "Williams")->addAttribute("zip", "90210");
    
    net.search("David", "Brown")->addAttribute("college", "USC");
    net.search("David", "Brown")->addAttribute("field", "Engineering");
    net.search("David", "Brown")->addAttribute("zip", "90001");
    
    net.search("Emma", "Davis")->addAttribute("college", "USC");
    net.search("Emma", "Davis")->addAttribute("field", "Computer Science");
    net.search("Emma", "Davis")->addAttribute("zip", "91101");
    
    net.search("Frank", "Miller")->addAttribute("college", "USC");
    net.search("Frank", "Miller")->addAttribute("field", "Computer Science");
    net.search("Frank", "Miller")->addAttribute("zip", "91101");
    
    net.search("Grace", "Wilson")->addAttribute("college", "UCLA");
    net.search("Grace", "Wilson")->addAttribute("field", "Psychology");
    net.search("Grace", "Wilson")->addAttribute("zip", "90210");
    
    net.search("Henry", "Moore")->addAttribute("college", "USC");
    net.search("Henry", "Moore")->addAttribute("field", "Business");
    net.search("Henry", "Moore")->addAttribute("zip", "90001");
}

int main() {
    Network net("recommendTest.txt");
    
    setupTestMetadata(net);
    
    net.showMenu();
    
    return 0;
}
