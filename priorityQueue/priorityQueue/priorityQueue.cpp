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
    
    char extract_min() {
        if (!head) {
            cout << "Empty " << endl;
            return ' ';
        }

        Node* currentNode = this->head;
        Node* nextNode = this->head;
        while (nextNode->next != NULL) {
            currentNode = nextNode;
            nextNode = nextNode->next;
        }
        currentNode->next = NULL;

        char result = nextNode->data;
        delete nextNode;
        this->currentSize--;
        return result;
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

    void clear() {
        if (empty()) {
            return;
        }
        Node* tempNode = this->head;
        while (this->currentSize > 0) {
            pop();
        }
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
    
    Node* search(char data) {
        Node* tempNode = this->head;
        if (this->currentSize > 0) {
            while (tempNode->next != NULL) {
                if (tempNode->data == data) {
                    return tempNode;
                }
                tempNode = tempNode->next;
            }
        }
        return NULL;
    }

    void update(char data, int priority) {
        if (this->head == NULL) {
            return;
        }
        Node* targetNode = search(data);

        Node* nextNode = NULL;
        Node* prevNode = NULL;
        if (targetNode == NULL) {
            return;
        }
        if (targetNode == this->head) {
            this->head = this->head->next;
        }
        else {
            prevNode = this->head;
            while (prevNode != NULL && prevNode->next != targetNode) {
                prevNode = prevNode->next;
            }
            if (prevNode->next == targetNode) {
                prevNode->next = targetNode->next;
            }
        }
        targetNode->priority = priority;
        nextNode = this->head;
        while (nextNode != NULL && nextNode->priority <= priority) {
            prevNode = nextNode;
            nextNode = nextNode->next;
        }
        if (prevNode == NULL) {
            targetNode->next = this->head;
            this->head = targetNode;
        }
        else {
            prevNode->next = targetNode;
            targetNode->next = nextNode;
        }
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

void charDataMinPriUpdateDisplay() {
    //arrange
    PriorityQueue pq;
    pq.insert('a', 1);
    pq.insert('b', 2);
    pq.insert('c', 3);
    pq.insert('d', 4);
    pq.insert('e', 5);

    //act
    pq.update('a', 6);

    //assert
    cout << "expectedResult: " << "b -> c -> d -> e -> a" << endl;
    cout << "actualResult: ";
    pq.printQueue();

    return;
}

void charDataMaxPriUpdateDisplay() {
    //arrange
    PriorityQueue pq;
    pq.insert('a', 1);
    pq.insert('b', 2);
    pq.insert('c', 3);
    pq.insert('d', 4);
    pq.insert('e', 5);

    //act
    pq.update('c', 1);

    //assert
    cout << "expectedResult: " << "a -> c -> b -> d -> e" << endl;
    cout << "actualResult: ";
    pq.printQueue();

    return;
}

void charDataMidPriUpdateDisplay() {
    //arrange
    PriorityQueue pq;
    pq.insert('a', 1);
    pq.insert('b', 2);
    pq.insert('c', 3);
    pq.insert('d', 4);
    pq.insert('e', 5);

    //act
    cout << "expectedResult: " << "b -> c -> a -> d -> e" << endl;
    cout << "actualResult: ";
    pq.update('a', 3);

    //assert
    pq.printQueue();

    return;
}

void charDataEndMidPriUpdateDisplay() {
    //arrange
    PriorityQueue pq;
    pq.insert('a', 1);
    pq.insert('b', 2);
    pq.insert('c', 3);
    pq.insert('d', 4);
    pq.insert('e', 5);

    //act
    pq.update('e', 3);

    //assert
    cout << "expectedResult: " << "a -> b -> c -> e -> d" << endl;
    cout << "actualResult: ";
    pq.printQueue();

    return;
}

int main() {
    PriorityQueue pq;

    pq.insert('c', 4);
    pq.insert('a', 1);
    pq.insert('b', 3);
    pq.insert('d', 8);
    pq.insert('e', 9);

    cout << "test ";
    pq.update('a', 3);

    charDataMinPriUpdateDisplay();
    charDataMaxPriUpdateDisplay();
    charDataMidPriUpdateDisplay();
    charDataEndMidPriUpdateDisplay();

    //pq.printQueue();

    return 0;
}

