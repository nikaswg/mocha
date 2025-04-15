#include <stdio.h>
#include <math.h>

#define H 0.1 // Шаг
#define A 2.1 // Начальное значение x
#define B 3.1 // Конечное значение x
#define Y0 2.5 // Начальное значение y

// Функция f(x, y)
double f(double x, double y) {
    return x + cos(y / sqrt(11));
}

// Метод Эйлера
void euler(double x0, double y0) {
    printf("Метод Эйлера:\n");
    printf("x\t\t y\n");
    for (double x = x0; x <= B + H; x += H) { // Изменено условие
        printf("%.4f\t %.4f\n", x, y0);
        y0 += H * f(x, y0);
    }
}

// Модифицированный метод Эйлера-Коши
void euler_koshi(double x0, double y0) {
    printf("\nМодифицированный метод Эйлера-Коши:\n");
    printf("x\t\t y\n");
    for (double x = x0; x <= B + H; x += H) { // Изменено условие
        printf("%.4f\t %.4f\n", x, y0);
        double y_temp = y0 + H * f(x, y0);
        y0 += H * (f(x, y0) + f(x + H, y_temp)) / 2.0;
    }
}

// Метод Эйлера с итерационным уточнением
void euler_iter(double x0, double y0) {
    printf("\nМетод Эйлера с итерационным уточнением:\n");
    printf("x\t\t y\n");
    for (double x = x0; x <= B + H; x += H) { // Изменено условие
        printf("%.4f\t %.4f\n", x, y0);
        double y_temp = y0 + H * f(x, y0);
        // Итерационное уточнение
        ййЙfor (int i = 0; i < 5; i++) { // 5 итераций
            y_temp = y0 + H * f(x + H, y_temp);
        }
        y0 = y_temp;
    }
}

int main() {
    double x0 = A;
    double y0 = Y0;

    euler(x0, y0);
    euler_koshi(x0, y0);
    euler_iter(x0, y0);

    return 0;
}