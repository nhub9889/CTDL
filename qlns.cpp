#include <iostream>
using namespace std;

template <typename T>
class Node {
private:
    T user;
    Node* nextNode;

public:
    Node() : user(T()), nextNode(nullptr) {}
    Node(T user) : user(user), nextNode(nullptr) {}
    T getDanhSach() {
        return user;
    }
    Node* getNext() {
        return nextNode;
    }
    void setNext(Node* next) {
        nextNode = next;
    }    
    void setNode(T newValue) {
        user = newValue;
    }
};

