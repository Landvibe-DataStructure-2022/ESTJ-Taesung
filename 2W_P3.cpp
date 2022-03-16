#include <iostream>
#include <string>
using namespace std;

class Node {
private:
    int value;
    Node *next;

public:
    Node() {
        this->value = 0;
        this->next = nullptr;
    }

    ~Node() {
        this->value = 0;
        this->next = nullptr;
    }

    friend class LinkedList;
};

class LinkedList {
private:
    Node *head;
    Node *tail;
    int size;

public:
    //using dummy head
    LinkedList() {
        this->head = new Node();
        this->tail = head;
        this->size = 0;
    }

    ~LinkedList() {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
    }

    bool empty() {
        if (this->size == 0) {
            return true;
        } else {
            return false;
        }
    }

    void printNode() {
        if (empty()) {
            cout << "empty";
            return;
        }

        Node *curNode = this->head->next;
        while (curNode != nullptr) {
            cout << curNode->value << " ";
            curNode = curNode->next;
        }
    }

    Node* getNode(int idx){
        Node *curNode = this->head;
        for (int i = 0; i <= idx; i++) {
            curNode = curNode->next;
        }
        return curNode;
    }

    void appendNode(int x) {
        Node *appendNode = new Node;
        appendNode->value = x;
        this->tail->next = appendNode;
        this->tail = appendNode;
        this->size++;
        printNode();
    }

    int deleteNode(int index) {
        if (index >= this->size) {
            return -1;
        }
        Node *prevNode = getNode(index-1);
        Node *deleteNode = prevNode->next;
        prevNode->next = deleteNode->next;
        if (deleteNode == this->tail) {
            this->tail = prevNode;
        }

        int deleteValue = deleteNode->value;
        delete deleteNode;
        this->size--;
        return deleteValue;
    }

    void insertNode(int index, int x) {
        if (index > this->size) {
            cout << "Index Error";
            return;
        }
        if (index == this->size) {
            appendNode(x);
        } else {
            Node *insertNode = new Node;
            insertNode->value = x;
            Node *curNode = getNode(index);
            insertNode->next = curNode->next;
            curNode->next = insertNode;
            printNode();
        }
        this->size++;
    }

    void minNode() {
        if(empty()) {
            cout<<"empty";
            return;
        }

        int minValue = 10000;
        Node *curNode = this->head->next;

        while (curNode != nullptr) {
            if(curNode->value < minValue) {
                minValue = curNode->value;
            }
            curNode = curNode->next;
        }

        cout<<minValue;
    }
};

int main() {
    int m;
    cin >> m;

    LinkedList *ll = new LinkedList;

    while (m--) {
        string cmd;
        int index;
        int x;
        cin >> cmd;

        if (cmd == "Print") {
            ll->printNode();
        } else if (cmd == "Append") {
            cin >> x;
            ll->appendNode(x);
        } else if (cmd == "Delete") {
            cin >> index;
            cout << ll->deleteNode(index);
        } else if (cmd == "Insert") {
            cin >> index >> x;
            ll->insertNode(index, x);
        } else if (cmd == "Min") {
            ll->minNode();
        }
        cout << "\n";
    }

    return 0;
}


