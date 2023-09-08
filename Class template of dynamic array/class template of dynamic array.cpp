#include <iostream>

template <typename T>
class DynamicArray {
private:
    T* arr;      // Указатель на массив
    int size;    // Размер массива

public:
    // Конструктор по умолчанию
    DynamicArray() : arr(nullptr), size(0) {}

    // Деструктор
    ~DynamicArray() {
        delete[] arr;
    }

    // Метод добавления элемента в массив
    void addElement(const T& element) {
        // Создаем новый временный массив с увеличенным размером на 1
        T* tempArr = new T[size + 1];

        // Копируем существующие элементы во временный массив
        for (int i = 0; i < size; i++) {
            tempArr[i] = arr[i];
        }

        // Добавляем новый элемент в конец временного массива
        tempArr[size] = element;

        // Удаляем старый массив
        delete[] arr;

        // Обновляем указатель на новый массив и размер
        arr = tempArr;
        size++;
    }

    // Метод получения количества элементов в массиве
    int getSize() const {
        return size;
    }

    // Перегрузка операции индексирования
    T& operator[](int index) {
        return arr[index];
    }

    // Перегрузка операции вывода массива в стандартный поток ostream
    friend std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& array) {
        for (int i = 0; i < array.size; i++) {
            os << array.arr[i] << " ";
        }
        return os;
    }
};

int main() {
    DynamicArray<int> array;

    // Добавляем элементы в массив
    array.addElement(5);
    array.addElement(10);
    array.addElement(15);

    // Выводим массив в стандартный поток ostream
    std::cout << "Массив: " << array << std::endl;

    // Получаем количество элементов в массиве
    std::cout << "Количество элементов: " << array.getSize() << std::endl;

    // Используем операцию индексирования
    std::cout << "Элемент с индексом 1: " << array[1] << std::endl;

    return 0;
}