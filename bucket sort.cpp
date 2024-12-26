#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

// Функция bucketSort изменена для работы с std::vector<int>
void bucketSort(std::vector<int>& arr) {
    int n = arr.size();
    if (n <= 0) return;

    // минимальное и максимальное значение в массиве
    int minVal = std::min_element(arr.begin(), arr.end())[0]; // O(n)
    int maxVal = std::max_element(arr.begin(), arr.end())[0]; // O(n)

    int range = maxVal - minVal; //  

    // Создаём корзины
    std::vector<std::vector<int>> buckets(n); // O(n)

    // Распределяем элементы по корзинам
    for (int num : arr) { // O(n)
        int bucketIndex = static_cast<int>(n * (num - minVal) / range); //  
        if (bucketIndex == n) bucketIndex = n - 1; //  
        buckets[bucketIndex].push_back(num); //  
    }

    // Сортируем каждую корзину
    for (std::vector<int>& bucket : buckets) { // O(n)
        std::sort(bucket.begin(), bucket.end()); // O(k log k), где k — количество элементов в корзине
    }

    // Сливаем все корзины обратно в массив
    int index = 0; //  
    for (const std::vector<int>& bucket : buckets) { // O(n)
        for (int num : bucket) { // O(k) кол-во элементов в массиве
            arr[index++] = num;
        }
    }
}

// Функция замера времени выполнения сортировки
void measureSortTime(std::vector<int>& arr) {
    auto start = std::chrono::high_resolution_clock::now();
    bucketSort(arr);
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
    boxPlot(bucketSort);

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

// O(n+ klogk)