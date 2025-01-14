import numpy as np

matrix = np.array([
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
])

# Извлечение главной диагонали
diagonal = np.diag(matrix)

# Сумма чисел главной диагонали
sum_diagonal = np.sum(diagonal)

print("Исходная матрица:", matrix)
print("Сумма чисел главной диагонали:", sum_diagonal)
