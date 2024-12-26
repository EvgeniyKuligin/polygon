#include <iostream>
#include <vector>
#include <chrono>
#include <random>

// Восстанавливает свойства кучи, начиная с узла index
void SiftDown(std::vector<int>& vec, int index, int size) {
  while (true) { // O(N)
    int left = index * 2 + 1; // Индекс левого дочернего узла
    int right = index * 2 + 2; // Индекс правого дочернего узла
    if (left >= size) { // Если у узла нет дочерних элементов, завершить
      break;
    }
    int condidate = index;
    if (vec[left] > vec[condidate]) { 
      condidate = left;
    }
    if (right < size && vec[right] > vec[condidate]) {
      condidate = right;
    }
    if (condidate == index) { 
      break;
    }
    std::swap(vec[index], vec[condidate]);
    index = condidate;
  }
}

// Реализация сортировки кучей
void HeapSort(std::vector<int>& vec) {
  // Построение кучи
  for (int i = vec.size(); i > 0; --i) { // O(N)
    SiftDown(vec, i - 1, vec.size());
  }
  int size = vec.size();
  // Сортировка
  for (int i = 0; i < vec.size(); ++i) { // O(N)
    --size; // Уменьшаем размер кучи
    std::swap(vec[0], vec[size]); // Перемещаем максимальный элемент в конец
    SiftDown(vec, 0, size); // Восстанавливаем свойства кучи
  }
}
// Функция замера времени выполнения сортировки
void measureSortTime(std::vector<int>& arr) {
    auto start = std::chrono::high_resolution_clock::now();
    HeapSort(arr);
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
    boxPlot(HeapSort);

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
// O(n^2)