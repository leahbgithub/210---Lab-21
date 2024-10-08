// 210 - Lab 21 - Leah Balakrishnan
#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class Goat {
private:
    int age;
    string name;
    string color;
    
    // array for randomizing names as well as colors
    static const string names[15];
    static const string colors[15];
    
public:
    // default constructor
    Goat() {
        age = rand() % 20 + 1; // randomize age between 1 and 20
        name = names[rand() % 15]; // randomize name from an array
        color = colors[rand() % 15]; // randomize colors from an array
    }
    
    // parametrized constructor
    Goat(int a, string n, string c) : age(a), name(n), color(c) {}
    
    // function that will return details of goat as string value
    string getDetails() const {
        return name + " (" + color + ", " + to_string(age) + ")";
    }
};

const string Goat::names[15] = { "Leah", "Raj", "Heena", "Shria", "Snowy", "Charlie", "Anthony", "Jason", "Macy", "Mahi", "Khaleesi", "Jon", "Jake", "Linda", "Caroline" };
const string Goat::colors[15] = { "Red", "Blue", "Green", "Yellow", "Purple", "Orange", "Pink", "White", "Black", "Grey", "Gold", "Silver", "Aqua", "Brown", "Turquoise" };

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(Goat val, Node* p = nullptr, Node* n = nullptr) : data(val), prev(p), next(n) {}
            };
    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void push_back(Goat value) {
        Node* newNode = new Node(value);
        if (!tail) // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(Goat value) {
        Node* newNode = new Node(value);
        if (!head) // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(Goat value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }
        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_node(string goatName) {
        if (!head) return; // Empty list
        Node* temp = head;
        while (temp && temp->data.getDetails().find(goatName) == string::npos)
            temp = temp->next;
        if (!temp) return; // Value not found
        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }
        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }
        delete temp;
    }

    void print() {
        if (!head) {
            cout << "List is empty" << endl;
            return;
        }
        Node* current = head;
        cout << "Forward: " << endl;
        while (current) {
            cout << "    " << current->data.getDetails() << endl;
            current = current->next;
        }
    }

    void print_reverse() {
        if (!tail) {
            cout << "List is empty" << endl;
            return;
        }
        Node* current = tail;
        cout << "Backward: " << endl;
        while (current) {
            cout << "    " << current->data.getDetails() << endl;
            current = current->prev;
        }
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    srand(time(0));
    
    DoublyLinkedList list;
    int size = rand() % (MAX_LS - MIN_LS + 1) + MIN_LS;
    
    for (int i = 0; i < size; ++i) {
        Goat randomGoat;
        list.push_back(randomGoat);
    }
    
    list.print();
    list.print_reverse();

    return 0;
}

