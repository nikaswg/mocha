#include <stdio.h>
#include <math.h>

// Функция, подлежащая интегрированию
double f(double x) {
    return sqrt(exp(x) + 1); // Изменённая функция
}

// Подынтегральная функция F(x, y)
double F(double x, double y) {
    return f(x) * f(y);
}

// Функция для вычисления двойного интеграла методом Симпсона
double double_integral_simpson(double a, double b) {
    double h = (b - a) / 2.0; // Шаг

    // Вычисляем значения F в узлах
    double F1 = F(a, a);
    double F2 = F(a, b);
    double F3 = F(b, a);
    double F4 = F(b, b);
    double F5 = F(a, (a + b) / 2.0);
    double F6 = F(b, (a + b) / 2.0);
    double F7 = F((a + b) / 2.0, a);
    double F8 = F((a + b) / 2.0, b);
    double F9 = F((a + b) / 2.0, (a + b) / 2.0);

    // Применяем формулу Симпсона
    double integral = (h * h) / 9.0 * (F1 + F2 + F3 + F4 + 
                                        4 * (F5 + F6 + F7 + F8) + 
                                        16 * F9);

    return integral;
}

int main() {
    double a = 0.0, b = log(2); // Границы интегрирования

    // Вычисляем двойной интеграл
    double result = double_integral_simpson(a, b);

    // Вывод результата
    printf("Приближённое значение двойного интеграла: %.6f\n", result);

    return 0;
}