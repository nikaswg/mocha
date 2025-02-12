#include <stdio.h>
#include <math.h>

// Функция, подлежащая интегрированию
double f(double x) {
    return (x + 1) / sqrt(x);
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

// Формула Ричардсона
double richardson(double I_n, double I_2n) {
    return I_2n + (I_2n - I_n) / 3.0; // Уточнение результата
}

// Формула Эйлера
double euler(double I_n, double I_2n) {
    return (2 * I_2n + I_n) / 3.0; // Уточнение результата
}

// Формула Ромберга
double romberg(double I_n, double I_2n) {
    return (I_n + I_2n) / 2.0; // Уточнение результата
}

int main() {
    double a = 2.0, b = 3.0; // Границы интегрирования

    // Вычисляем интеграл для n = 4
    int n1 = 4;
    double I_n1 = trapezoidal_rule(a, b, n1);
    printf("Интеграл для n = %d: %.6f\n", n1, I_n1);

    // Вычисляем интеграл для n = 8
    int n2 = 8;
    double I_n2 = trapezoidal_rule(a, b, n2);
    printf("Интеграл для n = %d: %.6f\n", n2, I_n2);

    // Уточнение по формуле Ричардсона
    double I_richardson = richardson(I_n1, I_n2);
    printf("Результат по формуле Ричардсона: %.6f\n", I_richardson);

    // Уточнение по формуле Эйлера с n = 6
    int n_euler = 6;
    double I_n_euler = trapezoidal_rule(a, b, n_euler);
    double I_euler = euler(I_n1, I_n_euler);
    printf("Результат по формуле Эйлера: %.6f\n", I_euler);

    // Уточнение по формуле Ромберга с n = 8
    double I_romberg = romberg(I_n1, I_n2);
    printf("Результат по формуле Ромберга: %.6f\n", I_romberg);

    return 0;
}