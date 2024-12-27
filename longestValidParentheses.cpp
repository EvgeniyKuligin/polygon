#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

// Функция для нахождения длины самой длинной корректной подстроки
int longestValidParentheses(const std::string& s) {
    int n = s.size();
    if (n == 0) return 0;

    std::vector<int> dp(n, 0); // O(n), 4n байт для хранения DP-массива
    int maxLength = 0;

    for (int i = 1; i < n; ++i) { // O(n)
        if (s[i] == ')') { // Проверяем только закрывающие скобки
            if (s[i - 1] == '(') { // Случай "()", добавляем 2
                dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
            } else if (i - dp[i - 1] - 1 >= 0 && s[i - dp[i - 1] - 1] == '(') {
                // Случай "(...))", добавляем длину предыдущей подстроки
                dp[i] = dp[i - 1] + ((i - dp[i - 1] - 2 >= 0) ? dp[i - dp[i - 1] - 2] : 0) + 2;
            }
            maxLength = std::max(maxLength, dp[i]); // Обновляем максимальную длину
        }
    }

    return maxLength;
    // сложность: O(n), память: 4n байт
}

void runTests() {
    assert(longestValidParentheses("") == 0);
    assert(longestValidParentheses("))))") == 0);
    assert(longestValidParentheses("((((") == 0);
    assert(longestValidParentheses("()") == 2);
    assert(longestValidParentheses("(()))") == 4);
    assert(longestValidParentheses("((()))") == 6);
    assert(longestValidParentheses(")()())") == 4);
    assert(longestValidParentheses("(()(((()") == 2);
    assert(longestValidParentheses("(()())") == 6);
    assert(longestValidParentheses("()()") == 4);

    std::cout << "Все тесты успешно пройдены!" << std::endl;
}

int main() {
    runTests();
    return 0;
}
