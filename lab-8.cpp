#include <iostream>
#include <stdexcept>

class Vector {
private:
    double* data;// Динамический массив с типом double
    int size;// Размер вектора

public:
    // Конструктор: создает вектор заданного размера
    Vector(int size) : size(size) {
        if (size <= 0) {
            throw std::invalid_argument("Size must be positive!");
        }
        data = new double[size]; // Выделяем память
        for (int i = 0; i < size; i++) {
            data[i] = 0.0; // Инициализируем нулями
        }
    }

    // Деструктор: освобождает память
    ~Vector() {   
        delete[] data; // Удаляем массив
    }

    // Метод для задания значения элемента
    void set(int index, double value) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range!");
        }
        data[index] = value;
    }

    // Метод для получения значения элемента
    double get(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range!");
        }
        return data[index];
    }

    // Метод для получения размера вектора
    int getSize() const {
        return size;
    }

    // Метод для сложения двух векторов
    Vector add(const Vector& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Vectors must have the same size!");
        }
        Vector result(size);
        for (int i = 0; i < size; i++) {
            result.set(i, data[i] + other.get(i));
        }
        return result;
    }

    // Метод для вычитания двух векторов
    Vector subtract(const Vector& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Vectors must have the same size!");
        }
        Vector result(size);
        for (int i = 0; i < size; i++) {
            result.set(i, data[i] - other.get(i));
        }
        return result;
    }

    // Метод для умножения двух векторов
    Vector multiply(const Vector& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Vectors must have the same size!");
        }
        Vector result(size);
        for (int i = 0; i < size; i++) {
            result.set(i, data[i] * other.get(i));
        }
        return result;
    }

    // Метод для деления двух векторов
    Vector divide(const Vector& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Vectors must have the same size!");
        }
        Vector result(size);
        for (int i = 0; i < size; i++) {
            if (other.get(i) == 0.0) {
                throw std::invalid_argument("Division by zero!");
            }
            result.set(i, data[i] / other.get(i));
        }
        return result;
    }

    void print() const {
        std::cout << "[";
        for (int i = 0; i < size; i++) {
            std::cout << data[i];
            if (i < size - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }
};

int main() {
    try {
        Vector v1(3);
        Vector v2(3);

        v1.set(0, 1.0);
        v1.set(1, 2.0);
        v1.set(2, 3.0);

        v2.set(0, 4.0);
        v2.set(1, 5.0);
        v2.set(2, 6.0);

        std::cout << "Vector 1: ";
        v1.print();

        std::cout << "Vector 2: ";
        v2.print();

        // Сложение
        Vector sum = v1.add(v2);
        std::cout << "Sum: ";
        sum.print();

        // Вычитание
        Vector diff = v1.subtract(v2);
        std::cout << "Difference: ";
        diff.print();

        // Умножение
        Vector prod = v1.multiply(v2);
        std::cout << "Product: ";
        prod.print();

        // Деление
        Vector quot = v1.divide(v2);
        std::cout << "Quotient: ";
        quot.print();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
