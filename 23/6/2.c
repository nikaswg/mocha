#include <stdio.h>
#include <math.h>

#define N 4          // Количество шагов
#define H 0.25       // Шаг
#define EPSILON 1e-3 // Точность
#define A 9          // Коэффициент a
#define B 2          // Коэффициент b

double boundary_condition(double x, double y) {
    return A * pow(x, 4) + B * pow(y, 4);
}

int main() {
    double u[N + 1][N + 1] = {0}; // Массив для хранения значений u
    double x, y;
    int i, j;

    // Устанавливаем граничные условия
    for (i = 0; i <= N; i++) {
        for (j = 0; j <= N; j++) {
            x = i * H;
            y = j * H;
            if (i == 0 || i == N || j == 0 || j == N) {
                u[i][j] = boundary_condition(x, y);
            }
        }
    }

    // Итерационный процесс методом Зейделя
    int iteration = 0;
    while (1) {
        double max_diff = 0.0;

        for (i = 1; i < N; i++) {
            for (j = 1; j < N; j++) {
                double new_value = (H * H / 4) * (12 * A * pow(i * H, 2) + 12 * B * pow(j * H, 2)) +
                                   0.25 * (u[i + 1][j] + u[i - 1][j] +
                                            u[i][j + 1] + u[i][j - 1]);
                
                // Вычисляем разницу для проверки сходимости
                double diff = fabs(new_value - u[i][j]);
                if (diff > max_diff) {
                    max_diff = diff;
                }
                
                // Обновляем значение
                u[i][j] = new_value;
            }
        }

        // Проверяем условие сходимости
        if (max_diff < EPSILON) {
            break;
        }

        iteration++;
    }

    // Выводим результат
    printf("Приближенное решение u(x,y):\n");
    for (i = 0; i <= N; i++) {
        for (j = 0; j <= N; j++) {
            printf("u(%.2f, %.2f) = %.6f\n", i * H, j * H, u[i][j]);
        }
    }

    return 0;
}