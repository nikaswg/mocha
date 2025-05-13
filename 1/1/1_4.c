#include <stdio.h>
#include <math.h>

// Функция, подлежащая интегрированию
double f(double x) {
    return 1 / x;
}

// Функция для вычисления интеграла по формуле Гаусса (n = 3)
double gauss_integral(double a, double b) {
    // Коэффициенты и узлы для формулы Гаусса с n = 3
    double weights[3] = {5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0};
    double nodes[3] = {-sqrt(3.0 / 5.0), 0.0, sqrt(3.0 / 5.0)};
    
    double integral = 0.0;
    double midpoint = (a + b) / 2.0;
    double half_length = (b - a) / 2.0;

    // Вычисляем интеграл
    for (int i = 0; i < 3; i++) {
        double x = midpoint + half_length * nodes[i];
        integral += weights[i] * f(x);
    }

    integral *= half_length; // Умножаем на длину отрезка
    return integral;
}

int main() {
    double a = 2.0, b = 3.0; // Границы интегрирования

    // Вычисляем интеграл по формуле Гаусса
    double integral = gauss_integral(a, b);

    // Вывод результата
    printf("Приближённое значение интеграла по формуле Гаусса (n = 3): %.6f\n", integral);

    return 0;
}