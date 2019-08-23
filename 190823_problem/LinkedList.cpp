#include <iostream>
using namespace std;

template<typename T>
class node {
public:
    node() { prev = next = NULL; }
    node(T d) : data(d) { prev = next = NULL; }
    ~node() {}
public:
    T data;
    node<T> *prev;
    node<T> *next;
};

template<typename T>
class LinkedList {
public:
    LinkedList() {
        head = new node<T>();
        tail = new node<T>();
        head->next = tail;
        tail->prev = head;
        m_size = 0;
    }
    ~LinkedList() {
        clear();
    }
    int size() const {
        return m_size;
    }
    void clear() {
        node<T> *cur = head;
        while (cur) {
            node<T> *next = cur->next;
            delete cur;
            cur = next;
        }
    }
    void print() {
        node<T> *tmp = head->next;
        cout << "{ ";
        while (tmp != tail) {
            cout << tmp->data << ' ';
            tmp = tmp->next;
        }
        cout << "}\n";
    }
    void push_back(T data) {
        node<T> *newNode = new node<T>(data);
        tail->prev->next = newNode;
        newNode->prev = tail->prev;
        newNode->next = tail;
        tail->prev = newNode;
        ++m_size;
    }
    void push_front(T data) {
        node<T> *newNode = new node<T>(data);
        head->next->prev = newNode;
        newNode->prev = head;
        newNode->next = head->next;
        head->next = newNode;
        ++m_size;
    }
    void pop_front() {
        node<T> *delNode = head->next;
        head->next = delNode->next;
        head->next->prev = head;
        delete delNode;
        --m_size;
    }
    void pop_back() {
        node<T> *delNode = tail->prev;
        tail->prev = delNode->prev;
        tail->prev->next = tail;
        delete delNode;
        --m_size;
    }
    void update(int pos, T data) {
        if (pos < 0 || pos >= m_size)
            return;
        node<T> *tmp = head->next;
        for (int i = 0; tmp != tail && i < pos; ++i)
            tmp = tmp->next;
        tmp->data = data;
    }
    void remove(int pos) {
        if (pos < 0 || pos >= size)
            return;
        node<T> *tmp = head->next;
        for (int i = 0; tmp != tail && i < pos; ++i)
            tmp = tmp->next;
        node<T> *t = tmp;
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        delete t;
        --m_size;
    }
private:
    node<T> *head;
    node<T> *tail;
    int m_size;
};

int main() {
    LinkedList<int> a;

    cout << "push_back:\n";
    for (int i = 0; i < 5; ++i) {
        a.push_back(i * 10);
        a.print();
    }

    cout << "push_front:\n";
    for (int i = 1; i <= 5; ++i) {
        a.push_front(-i * 10);
        a.print();
    }

    cout << "pop_back:\n";
    for (int i = 0; i < 5; ++i) {
        a.pop_back();
        a.print();
    }

    cout << "pop_front:\n";
    for (int i = 0; i < 5; ++i) {
        a.pop_front();
        a.print();
    }

    return 0;
}

// author     : joonas
// date       : 2019-08-09
// description: Double Linked List with class template in C++