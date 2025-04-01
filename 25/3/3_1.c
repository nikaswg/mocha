#include <stdio.h>
#include <math.h>

#define H 0.1 // Шаг
#define A 0.2 // Начальное значение x
#define B 1.2 // Конечное значение x
#define Y0 1.1 // Начальное значение y

// Функция f(x, y)
double f(double x, double y) {
    return x + sin((y + 1) / sqrt(13)); // Обновленная функция
}

// Метод Рунге-Кутты 4-го порядка
void runge_kutta(double x0, double y0) {
    printf("Метод Рунге-Кутты 4-го порядка:\n");
    printf("x\t\t y\n");
    for (double x = x0; x <= B; x += H) { // Изменено условие на x <= B
        printf("%.4f\t %.4f\n", x, y0);
        double k1 = H * f(x, y0);
        double k2 = H * f(x + H / 2, y0 + k1 / 2);
        double k3 = H * f(x + H / 2, y0 + k2 / 2);
        double k4 = H * f(x + H, y0 + k3);
        y0 += (k1 + 2 * k2 + 2 * k3 + k4) / 6;
    }
}

int main() {
    double x0 = A;
    double y0 = Y0;

    runge_kutta(x0, y0);

    return 0;
}