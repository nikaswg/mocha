#include <stdio.h>
#include <math.h>

// Функция, подлежащая интегрированию
double f(double x) {
    return 1 / (1 + x * x);
}

// Подынтегральная функция F(x, y)
double F(double x, double y) {
    return f(x) * f(y);
}

// Функция для вычисления двойного интеграла методом Гаусса
double double_integral_gauss(double a, double b) {
    // Узлы и веса для n = 2
    double nodes[2] = { -1.0 / sqrt(3.0), 1.0 / sqrt(3.0) };
    double weight = 1.0;

    double integral = 0.0;

    // Преобразуем узлы к пределам интегрирования
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            double x = (b - a) / 2.0 * nodes[i] + (a + b) / 2.0;
            double y = (b - a) / 2.0 * nodes[j] + (a + b) / 2.0;
            integral += weight * weight * F(x, y);
        }
    }

    integral *= (b - a) * (b - a) / 4.0; // Умножаем на площадь области интегрирования
    return integral;
}

int main() {
    double a = 2.0, b = 3.0; // Границы интегрирования

    // Вычисляем двойной интеграл
    double result = double_integral_gauss(a, b);

    // Вывод результата
    printf("Приближённое значение двойного интеграла: %.6f\n", result);

    return 0;
}