#include <iostream>

class DynamicIntArray {
private:
    int* data;     // Указатель на динамический массив
    int size;      // Размер массива

public:
    // Конструктор по умолчанию
    DynamicIntArray() : data(nullptr), size(0) {}

    // Деструктор
    ~DynamicIntArray() {
        delete[] data;
    }

    // Метод добавления элемента в массив
    void addElement(int element) {
        int* newData = new int[size + 1];    // Создаем новый массив большего размера

        // Копируем существующие элементы в новый массив
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }

        newData[size] = element;    // Добавляем новый элемент в конец массива

        delete[] data;              // Освобождаем память, занимаемую старым массивом
        data = newData;             // Обновляем указатель на новый массив
        size++;                     // Увеличиваем размер массива
    }

    // Метод получения количества элементов в массиве
    int getSize() const {
        return size;
    }

    // Перегрузка операции индексирования
    int& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Перегрузка операции вывода в стандартный поток ostream
    friend std::ostream& operator<<(std::ostream& os, const DynamicIntArray& array) {
        for (int i = 0; i < array.size; i++) {
            os << array.data[i] << " ";
        }
        return os;
    }
};

int main() {
    DynamicIntArray arr;

    // Добавление элементов в массив
    arr.addElement(10);
    arr.addElement(20);
    arr.addElement(30);

    // Вывод размера массива
    std::cout << "Размер массива: " << arr.getSize() << std::endl;

    // Вывод элементов массива
    std::cout << "Массив: " << arr << std::endl;

    // Изменение элемента массива
    arr[1] = 25;

    // Вывод измененного массива
    std::cout << "Измененный массив: " << arr << std::endl;

    return 0;
}
