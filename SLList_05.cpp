#include <iostream>
#include <memory>

struct Node {
    int data;
    std::unique_ptr<Node> next;
    Node(int data) : data{data}, next{nullptr} {}
};

struct List {
    List() : head{nullptr} {};

    void push(int data) {
        auto temp{std::make_unique<Node>(data)};
        if(head) {
            temp->next = std::move(head);
            head = std::move(temp);

        } else {
            head = std::move(temp);
        }
    }

    void pop() {
        if(head == nullptr) {
            return;
        }

        std::unique_ptr<Node> temp = std::move(head);
        head = std::move(temp->next);
    }

    void clean() {
        while(head) {
            head = std::move(head->next);
        }
    }

    ~List() {
        clean();
    }

    friend std::ostream& operator<<(std::ostream &os, const List &list);

private:
    std::unique_ptr<Node> head;
};

std::ostream& operator<<(std::ostream &os, const List &list) {
    Node *head = list.head.get();
    while(head) {
        os << head->data << ' ';
        head = head->next.get();
    }
    return os;
}

int main() {
    List list;

    list.push(-10);
    std::cout << list << '\n';

    list.pop();
    std::cout << list << '\n';

    for(int i = 0; i < 10; ++i) {
        list.push(i);
    }
    std::cout << list << '\n';

    list.pop();
    list.pop();
    list.pop();
    std::cout << list << '\n';

    list.push(-20);
    list.push(-30);
    std::cout << list << '\n';

    list.clean();
    std::cout << list << '\n';

    list.push(-1);
    list.push(-2);
    std::cout << list << '\n';
}
