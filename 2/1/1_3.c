#include <stdio.h>
#include <math.h>

// Функция, подлежащая интегрированию
double f(double x) {
    return 1 / (1 + x * x);
}

// Производная второго порядка f''(x) для оценки ошибки
double second_derivative(double x) {
    return ((6 * x * x) - 2) / pow((1 + x*x),3); 
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

// Функция для нахождения максимума второй производной на отрезке [a, b]
double max_second_derivative(double a, double b) {
    double max_f2 = fabs(second_derivative(a));
    for (double x = a; x <= b; x += (b - a) / 100) { // Дискретизация для поиска максимума
        double f2 = fabs(second_derivative(x));
        if (f2 > max_f2) {
            max_f2 = f2;
        }
    }
    return max_f2;
}

// Функция для оценки погрешности
double error_estimate(double a, double b, int n) {
    double h = (b - a) / n; // Шаг разбиения
    double max_f2 = max_second_derivative(a, b);
    return (pow(h, 2) * (b - a) * max_f2) / 12.0; // Оценка погрешности
}

int main() {
    double a = 2.0, b = 3.0; // Границы интегрирования
    double epsilon = 0.001; // Заданная точность
    int n = 1; // Начальное количество разбиений

    printf("n\tИнтеграл\tПогрешность\n");
    
    // Итерация для увеличения n до достижения заданной точности
    while (1) {
        double integral = trapezoidal_rule(a, b, n);
        double error = error_estimate(a, b, n);

        printf("%d\t%.6f\t%.6f\n", n, integral, error);

        // Проверяем, достигнута ли заданная точность
        if (error < epsilon) {
            break;
        }
        n++; // Увеличиваем количество разбиений
    }

    printf("Необходимое количество разбиений n: %d\n", n);

    return 0;
}