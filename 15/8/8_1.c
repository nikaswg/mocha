#include <stdio.h>
#include <math.h>

#define A 1.3        // Значение параметра a
#define LAMBDA 0.5   // Значение λ
#define K_MAX 3      // Максимальное число итераций
#define N 100        // Количество точек для интеграла (метод прямоугольников)

// Функция ядра K(x, s)
double kernel(double x, double s) {
    double xs = x * s;
    return xs + pow(xs, 3) / 6.0 + pow(xs, 5) / 120.0;
}

// Функция f(x) = a - x^2
double f(double x) {
    return A - x * x;
}

// Метод вычисления интеграла от 0 до 1 (метод прямоугольников)
double integrate(double x, double (*phi)(double, int), int k) {
    double h = 1.0 / N;  // Шаг интегрирования
    double sum = 0.0;

    for (int i = 0; i < N; i++) {
        double s = i * h + h / 2;  // Точка в середине интервала
        sum += kernel(x, s) * phi(s, k);  // Ядро * текущая аппроксимация
    }
    return sum * h;
}

// Итерационные функции φ_k(x)
double phi(double x, int k) {
    if (k == 0) {
        return f(x);  // Начальное приближение
    } else {
        // Вычисляем приближение φ_k(x) с помощью предыдущего значения
        return f(x) + LAMBDA * integrate(x, phi, k - 1);
    }
}

// Основная функция
int main() {
    printf("Решение интегрального уравнения методом последовательных приближений:\n");
    printf("y(x) = sum(lambda^k * phi_k(x)), k = 0..%d\n", K_MAX);
    printf("Параметры: a = %.1f, lambda = %.1f\n\n", A, LAMBDA);

    // Вывод результата для нескольких значений x
    printf("%-8s", "x");
    for (int k = 0; k <= K_MAX; k++) {
        printf("phi_%d(x)   ", k);
    }
    printf("\n");

    for (double x = 0.0; x <= 1.0; x += 0.1) {
        printf("%-8.2f", x);

        for (int k = 0; k <= K_MAX; k++) {
            printf("%-12.6f", phi(x, k));  // Вычисляем φ_k(x) для текущего x
        }

        printf("\n");
    }

    return 0;
}