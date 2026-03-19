#ifndef LINKEDLIST_H
#define LINKEDLIST_H
template <typename T>
struct ListNode {
    T data;
    ListNode* next;
    ListNode(const T& d) : data(d), next(nullptr) {}
};

template <typename T>
class LinkedList {
public:
    ListNode<T>* head;
    LinkedList() : head(nullptr) {}
    void push_front(const T& val) {
        ListNode<T>* node = new ListNode<T>(val);
        node->next = head;
        head = node;
    }
    ~LinkedList() {
        while (head) {
            ListNode<T>* tmp = head;
            head = head->next;
            delete tmp;
        }
    }
};
#endif