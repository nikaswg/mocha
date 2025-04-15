#include <stdio.h>
#include <math.h>

#define A 1.3        // Параметр a
#define N 4          // Количество узлов разбиения (h = 1 / N)
#define LAMBDA 0.5   // Значение λ

// Узлы сетки
double x[N + 1];

// Ядро K(x, s)
double kernel(double x, double s) {
    double xs = x * s;
    return xs + pow(xs, 3) / 6.0 + pow(xs, 5) / 120.0;
}

// Правая часть f(x) = a - x^2
double f(double x) {
    return A - x * x;
}

// Квадратурные коэффициенты для формулы Симпсона
void simpson_weights(double *weights) {
    weights[0] = 1;
    weights[N] = 1;
    for (int i = 1; i < N; i++) {
        weights[i] = (i % 2 == 0) ? 2 : 4;
    }
}

// Решение системы линейных уравнений методом Гаусса
void gauss_solve(double a[N + 1][N + 2], double *y) {
    int i, j, k;
    for (i = 0; i <= N; i++) {
        // Нормализация строки
        for (j = i + 1; j <= N; j++) {
            double factor = a[j][i] / a[i][i];
            for (k = i; k <= N + 1; k++) {
                a[j][k] -= factor * a[i][k];
            }
        }
    }
    // Обратный ход
    for (i = N; i >= 0; i--) {
        y[i] = a[i][N + 1];
        for (j = i + 1; j <= N; j++) {
            y[i] -= a[i][j] * y[j];
        }
        y[i] /= a[i][i];
    }
}

int main() {
    double h = 1.0 / N;  // Шаг разбиения
    double weights[N + 1];  // Квадратурные коэффициенты Симпсона
    double a[N + 1][N + 2];  // Матрица СЛАУ (коэффициенты + правая часть)
    double y[N + 1];  // Решение (значения y(x) в узлах)

    // Инициализация узлов сетки
    for (int i = 0; i <= N; i++) {
        x[i] = i * h;
    }

    // Вычисление квадратурных коэффициентов
    simpson_weights(weights);

    // Построение матрицы СЛАУ
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            a[i][j] = (i == j ? 1.0 : 0.0) - LAMBDA * (h / 3.0) * weights[j] * kernel(x[i], x[j]);
        }
        a[i][N + 1] = f(x[i]);  // Правая часть
    }

    // Решение СЛАУ методом Гаусса
    gauss_solve(a, y);

    // Вывод результатов
    printf("Решение интегрального уравнения методом конечных сумм (формула Симпсона):\n");
    printf("%-8s %-12s\n", "x", "y(x)");
    for (int i = 0; i <= N; i++) {
        printf("%-8.2f %-12.6f\n", x[i], y[i]);
    }

    return 0;
}