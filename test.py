def create_matrix(n):
    """Функция для создания и заполнения исходной матрицы пользователем"""
    matrix = []
    for i in range(n):
        row = []
        for j in range(n):
            val = int(input(f"Введите элемент [{i+1}, {j+1}]: "))
            row.append(val)
        matrix.append(row)
    return matrix

def print_matrix(matrix):
    """Функция для вывода исходной матрицы"""
    print("Исходная матрица:")
    for row in matrix:
        print(" ".join(map(str, row)))

def custom_order(matrix, n):
    """Функция для вывода элементов матрицы в заданном порядке"""
    result = []
    
    # Первый проход слева направо по верхнему ряду
    for j in range(n):
        result.append(matrix[0][j])
    
    # Далее зигзагообразный спуск по столбцам и строкам
    i = 1
    while i < n:
        if i % 2 == 1:
            # Спуск вниз по первому столбцу
            for j in range(n-1, -1, -1):
                result.append(matrix[i][j])
        else:
            # Подъем вверх по правому столбцу
            for j in range(n):
                result.append(matrix[i][j])
        i += 1

    print("Элементы матрицы в заданном порядке:")
    print(" ".join(map(str, result)))

def main():
    N = int(input("Введите размер матрицы N (от 2 до 9): "))
    
    if N < 2 or N > 9:
        print("Неверный ввод! Размер матрицы должен быть от 2 до 9.")
        return
    
    matrix = create_matrix(N)
    print_matrix(matrix)
    custom_order(matrix, N)

if __name__ == "__main__":
    main()
