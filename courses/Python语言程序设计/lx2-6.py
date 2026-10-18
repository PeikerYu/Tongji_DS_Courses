import random

matrix = [[random.randint(0, 1) for _ in range(10)] for _ in range(10)]

print("原始10*10矩阵：")
for row in matrix:
    for num in row:
        print(num, " ", end="")
    print()

result = [row.copy() for row in matrix]

max_area = 0
max_i, max_j, max_h, max_w = 0, 0, 0, 0

for i in range(10):
    for j in range(10):
        if matrix[i][j] == 1:
            current_max_w = 10 - j
            for h in range(1, 10 - i + 1):
                if matrix[i + h - 1][j] != 1:
                    break
                w = 0
                while j + w < 10 and matrix[i + h - 1][j + w] == 1:
                    w += 1
                current_max_w = min(current_max_w, w)
                area = h * current_max_w
                if area > max_area:
                    max_area = area
                    max_i, max_j, max_h, max_w = i, j, h, current_max_w

if max_area > 0:
    for row in range(max_i, max_i + max_h):
        for col in range(max_j, max_j + max_w):
            result[row][col] = '*'

print("改变后：")
for row in result:
    for num in row:
        print(num, " ", end="")
    print()