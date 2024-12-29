#include <vector>
#include <cmath>
#include <algorithm>

class Solution {
public:
    int findMinMoves(std::vector<int>& machines) {
        int n = machines.size(); 
        
        // Считаем общее количество платьев вручную
        int total = 0;
        for (int dresses : machines) {
            total += dresses; // O(n)
        }

        // Проверяем, можно ли выровнять
        if (total % n != 0) return -1;

        int target = total / n;
        int balance = 0;
        int maxMoves = 0;

        for (int dresses : machines) {
            // Вычисляем текущий баланс
            balance += dresses - target; // O(n)
            // Находим максимальное значение перемещений
            maxMoves = std::max(maxMoves, std::max(std::abs(balance), dresses - target)); // O(1) по времени
        }

        return maxMoves;
    }
};
// память: O(n) из-за machines
// сложность: O(n)
