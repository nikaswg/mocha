#include <stdio.h>
#include <math.h>

// Функция, подлежащая интегрированию
double f(double x) {
    return sqrt(x) * exp(pow(x, 2));
}

// Производная второго порядка f''(x) для оценки ошибки
double second_derivative(double x) {
    // Вычисляем вторую производную для новой функции
    return (4 * pow(x, 2) * exp(pow(x, 2)) + (2 * exp(pow(x, 2))) / (2 * sqrt(x))) / (2 * sqrt(x));
}

// Функция для вычисления интеграла методом трапеций
double trapezoidal_rule(double a, double b, int n) {
    double h = (b - a) / n; // Шаг разбиения
    double integral = 0.5 * (f(a) + f(b)); // Первое и последнее слагаемое

    // Суммируем значения функции в промежуточных точках
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        integral += f(x);
    }

    integral *= h; // Умножаем на шаг
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
    return (pow(h, 2) * (b - a) * max_f2) / 12.0;
}

int main() {
    double a = 2.0, b = 3.0; // Границы интегрирования
    int n = 8; // Количество разбиений

    // Вычисляем интеграл методом трапеций
    double integral = trapezoidal_rule(a, b, n);

    // Оцениваем погрешность
    double error = error_estimate(a, b, n);

    // Вывод результата
    printf("Приближённое значение интеграла: %.6f\n", integral);
    printf("Оценка погрешности: %.6f\n", error);

    return 0;
}