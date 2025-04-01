#include <stdio.h>
#include <math.h>

#define H 0.1 // Шаг
#define A 0.2 // Начальное значение x
#define B 1.2 // Конечное значение x
#define STEPS 4 // Количество начальных значений для Адамса

// Функция f(x, y)
double f(double x, double y) {
    return x + sin((y + 1) / sqrt(13)); // Обновленная функция
}

// Метод Адамса-Башфорта
void adams_bashforth(double x0, double* y_values, int steps, double h) {
    for (int i = steps; (x0 + i * h) <= B; i++) {
        double x = x0 + i * h;
        double y_next = y_values[i-1] + (h / 24) * (
            55 * f(x0 + (i-1) * h, y_values[i-1]) -
            59 * f(x0 + (i-2) * h, y_values[i-2]) +
            37 * f(x0 + (i-3) * h, y_values[i-3]) -
            9 * f(x0 + (i-4) * h, y_values[i-4])
        );

        y_values[i] = y_next;
    }
}

int main() {
    double x0 = A;
    double y_values[STEPS + 10] = {1.1, 1.15, 1.2, 1.25}; // Массив начальных значений y

    // Вычисление значений с помощью метода Адамса
    adams_bashforth(x0, y_values, STEPS, H);

    // Вывод результатов
    printf("Метод Адамса-Башфорта:\n");
    printf("x\t\t y\n");
    for (int i = 0; i < STEPS + 10 && (x0 + i * H) <= B; i++) {
        printf("%.4f\t %.4f\n", x0 + i * H, y_values[i]);
    }

    return 0;
}