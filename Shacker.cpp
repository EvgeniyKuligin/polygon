#include <iostream>
#include <vector>
#include <chrono>
#include <random>

// Прототип функции
void measureSortTime(std::vector<int>& arr);

// Функция сортировки Shacker
void Shacker(std::vector<int>& vec) {
    std::size_t left = 0;
    std::size_t right = vec.size();
    bool has_changed = true;

    while (has_changed) { // O(N)
        has_changed = false;

        // Проход слева направо
        for (std::size_t i = left; i + 1 < right; ++i) { // O(N)
            if (vec[i] > vec[i + 1]) {
                std::swap(vec[i], vec[i + 1]); // O(1)
                has_changed = true;
            }
        }

        if (!has_changed) {
            break;
        }

        has_changed = false;
        --right;

        // Проход справа налево
        for (std::size_t i = right - 1; i > left; --i) { // O(N)
            if (vec[i - 1] > vec[i]) {
                std::swap(vec[i], vec[i - 1]); // O(1)
                has_changed = true;
            }
        }

        ++left;
    }
}

// Функция замера времени выполнения сортировки
void measureSortTime(std::vector<int>& arr) {
    auto start = std::chrono::high_resolution_clock::now();
    Shacker(arr);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

    std::cout << arr.size() << " " << duration.count() << std::endl;
}

// Функция для тестирования производительности сортировок
void boxPlot(void (*sort_func)(std::vector<int>&)) {
    std::vector<std::size_t> sizes = {10000, 100000};
    int runs_per_size = 25;

    for (std::size_t size : sizes) {
        std::cout << "Array Size: " << size << std::endl;

        for (int run = 1; run <= runs_per_size; ++run) {
            // Генерация случайного массива
            std::vector<int> arr(size);
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, 9999);

            for (std::size_t j = 0; j < arr.size(); ++j) {
                arr[j] = dis(gen);
            }

            // Замер времени
            auto start = std::chrono::high_resolution_clock::now();
            sort_func(arr);
            auto end = std::chrono::high_resolution_clock::now();

            double elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

            std::cout << run << " " << elapsed << std::endl;
        }

        std::cout << std::endl;
    }
}

// Основная функция
int main() {
    boxPlot(Shacker);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9999);

    for (int n = 1000; n <= 30000; n += 1000) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = dis(gen);
        }
        measureSortTime(arr);
    }

    return 0;
}

// O(N^2)
