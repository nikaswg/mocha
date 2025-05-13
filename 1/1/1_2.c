#include <stdio.h>
#include <math.h>

// Функция, подлежащая интегрированию
double f(double x) {
    return 1 / x;
}

// Производная второго порядка f''(x) для оценки ошибки
double second_derivative(double x) {
    return 2 / (x * x * x);
}

// Функция для вычисления интеграла по обобщенной формуле Симпсона
double simpson_rule(double a, double b, int n) {
    double h = (b - a) / n; // Шаг разбиения
    double integral = f(a) + f(b); // Первое и последнее слагаемое

    // Суммируем значения функции для чётных и нечётных индексов
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        if (i % 2 == 0) {
            integral += 2 * f(x); // Чётные индексы
        } else {
            integral += 4 * f(x); // Нечётные индексы
        }
    }

    integral *= h / 3; // Умножаем на шаг и делим на 3
    return integral;
}

// Функция для оценки погрешности
double error_estimate(double a, double b, int n) {
    double h = (b - a) / n; // Шаг разбиения
    double max_f2 = 0.0; // Максимум |f''(x)| на [a, b]

    // Поиск максимального значения модуля f''(x) на отрезке
    for (double x = a; x <= b; x += h / 10) { // Берём больше точек для точности
        double f2 = fabs(second_derivative(x));
        if (f2 > max_f2) {
            max_f2 = f2;
        }
    }

    // Оценка погрешности по формуле
    return (pow(h, 4) * (b - a) * max_f2) / 180.0;
}

int main() {
    double a = 2.0, b = 3.0; // Границы интегрирования
    int n = 4; // Количество разбиений

    // Вычисляем интеграл методом Симпсона
    double integral = simpson_rule(a, b, n);

    // Оцениваем погрешность
    double error = error_estimate(a, b, n);

    // Вывод результата
    printf("Приближённое значение интеграла: %.6f\n", integral);
    printf("Оценка погрешности: %.6f\n", error);

    return 0;
}