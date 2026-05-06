For full documentation see `Final Project README.pdf`

# TrojanBook 🎓
TrojanBook is a command-line social network application written in C++. It allows users to store, manage, 
and connect people in a contact database, similar to a simplified version of Facebook or LinkedIn. 
People are stored in a Doubly Linked List (DLL) and can be saved and loaded from text files.

---

## How to Compile and Run

**System:**
```bash
Compile: g++ -std=c++11 -o test_rec test_recommendations.cpp network.cpp person.cpp date.cpp contact.cpp misc.cpp
Run: ./test_rec
```

---

## Project Structure
| Folder | Description |
|---|---|
| `phase1/` | Contact management — add, remove, save, load, search |
| `phase2/` | Friend connections between people (double sided). Wise Search — search by name, phone, email, or birthday|
| `phase3/` | Friend Recommendation System with similarity scoring (extra credit)|

---

## Menu Options
| Option | Feature |
|---|---|
| 1 | Save network to file |
| 2 | Load network from file |
| 3 | Add a new person |
| 4 | Remove a person |
| 5 | Print people by last name |
| 6 | Connect two people as friends |
| 7 | Wise Search (search by any field) |
| 8 | Friend Recommendations (Extra Credit) |

---

## Extra Credit — Friend Recommendation System
Recommends the top 5 potential friends based on a weighted similarity score:

| Factor | Weight |
|---|---|
| Age Difference | 25% |
| Email Domain | 20% |
| Phone Area Code | 15% |
| College | 15% |
| Field of Study | 15% |
| Zip Code | 10% |
