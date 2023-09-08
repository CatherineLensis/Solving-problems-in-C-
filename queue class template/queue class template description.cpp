#include <iostream>

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;     // Указатель на голову очереди
    Node* tail;     // Указатель на хвост очереди

public:
    // Конструктор по умолчанию
    Queue() : head(nullptr), tail(nullptr) {}

    // Деструктор
    ~Queue() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Метод добавления данных в очередь
    void enqueue(const T& value) {
        Node* newNode = new Node(value);

        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Метод извлечения данных из очереди
    T dequeue() {
        if (!head) {
            throw std::runtime_error("Queue is empty");
        }

        T data = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;

        if (!head) {
            tail = nullptr;
        }

        return data;
    }

    // Перегрузка операции вывода в стандартный поток ostream
    friend std::ostream& operator<<(std::ostream& os, const Queue& queue) {
        Node* current = queue.head;
        while (current) {
            os << current->data << " ";
            current = current->next;
        }
        return os;
    }
};

int main() {
    Queue<int> queue;

    // Добавление элементов в очередь
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    // Извлечение и вывод элементов очереди
    std::cout << "Извлеченные элементы: ";
    while (true) {
        try {
            int element = queue.dequeue();
            std::cout << element << " ";
        } catch (const std::runtime_error& e) {
            break;
        }
    }
    std::cout << std::endl;

    return 0;
}
