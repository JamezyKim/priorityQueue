#include <iostream>
using namespace std;


#include <iostream>
using namespace std;

class Node {
public:
    char data;
    int priority;
    Node* next;

    Node(char value, int priority) {
        this->data = value;
        this->priority = priority;
        next = NULL;
    }
};

class PriorityQueue {
private:
    Node* head; // Head points to the smallest element (highest priority)

public:
    int currentSize;

    PriorityQueue() {
        head = NULL;
        this->currentSize = 0;
    }

    // Insert element in sorted order (O(n))
    void insert(char data, int priority) {
        Node* newNode = new Node(data, priority);

        // If list is empty or new node has highest priority
        if (!head || this->head->priority > priority) {
            newNode->next = this->head;
            this->head = newNode;
            this->currentSize++;
            return;
        }

        // Find correct position for new node
        Node* temp = head;
        while (temp->next && temp->next->priority <= priority) {
            temp = temp->next;
        }

        newNode->next = temp->next;
        temp->next = newNode;
        this->currentSize++;
    }

    
    // Remove and return the highest priority element (O(1))
    char pop() {
        if (!head) {
            std::cerr << "Queue is empty!\n";
            return ' ';
        }
        char minValue = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        this->currentSize--;
        return minValue;
    }

    // Get the highest priority element without removing (O(1))
    char top() {
        if (!head) {
            cout << "Queue is empty!\n";
            return ' ';
        }
        return head->data;
    }

    // Check if queue is empty
    bool empty() {
        return head == NULL;
    }

    // Print the queue
    void printQueue() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << "(" << temp->priority << ")" << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }


    // Destructor to free memory
    ~PriorityQueue() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};



int main() {
    PriorityQueue pq;

    pq.insert('d', 4);
    pq.insert('d', 1);
    pq.insert('d', 3);
    pq.insert('d', 8);
    pq.insert('d', 9);

    cout << "test ";
    pq.printQueue();

    //std::cout << "Priority Queue (Linked List): ";
    //pq.printQueue();

    //std::cout << "Top element: " << pq.top() << std::endl;

    //std::cout << "Removing elements in priority order: ";
    //while (!pq.empty()) {
    //    std::cout << pq.pop() << " ";
    //}
    //std::cout << std::endl;

    return 0;
}

