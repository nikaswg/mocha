#include <stdio.h>
#include <math.h>

// Функция f(x)
double f(double x) {
    return (x + 1) / sqrt(x);
}

// Подынтегральная функция F(x, y)
double F(double x, double y) {
    return f(x) * f(y);
}

// Функция для вычисления двойного интеграла по формуле Симпсона
double double_integral_simpson(double a, double b) {
    double h_x = (b - a) / 2.0; // Шаг по x
    double h_y = (b - a) / 2.0; // Шаг по y

    // Узлы
    double x0 = a, x1 = a + h_x, x2 = b;
    double y0 = a, y1 = a + h_y, y2 = b;

    // Вычисляем интеграл по формуле Симпсона
    double integral = (h_x * h_y / 9.0) * (
        F(x0, y0) + F(x0, y2) + F(x2, y0) + F(x2, y2) +
        4 * (F(x1, y1) + F(x1, y0) + F(x0, y1) + F(x2, y1) + F(x1, y2))
    );

    return integral;
}

int main() {
    double a = 2.0, b = 3.0; // Границы интегрирования

    // Вычисляем двойной интеграл
    double result = double_integral_simpson(a, b);

    // Вывод результата
    printf("Приближённое значение двойного интеграла: %.6f\n", result);

    return 0;
}