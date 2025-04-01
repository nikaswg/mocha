#include <stdio.h>
#include <math.h>


#define H 0.1 // Шаг
#define A 0.6 // Начальное значение x
#define B 1.6 // Конечное значение x
#define Y0 0.8 // Начальное значение y

// Функция f(x, y)
double f(double x, double y) {
    return x + sin(y / sqrt(10));
}

// Метод Рунге-Кутты 4-го порядка
void runge_kutta(double x0, double y0) {
    printf("Метод Рунге-Кутты 4-го порядка:\n");
    printf("x\t\t y\n");
    for (double x = x0; x <= B + H; x += H) {
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