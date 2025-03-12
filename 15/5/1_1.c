#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define L 1.0        // Длина интервала
#define T 0.02       // Время
#define H 0.1        // Шаг по пространству
#define TAU 0.01     // Шаг по времени
#define N ((int)(L/H)) // Количество пространственных точек
#define M ((int)(T/TAU)) // Количество временных точек

// Начальные условия
double u_0(double x) {
    return x * x + 0.5;
}

// Левое краевое условие
double u_1(double t) {
    return 3 * t * (t + 20);
}

// Правое краевое условие
double u_2(double t) {
    return t + 0.75;
}

// Функция f(x,t)
double f(double x, double t) {
    return x * x + 0.5 * t;
}

// Явная схема
void explicit_scheme(double u[N + 1][M + 1]) {
    for (int j = 0; j <= N; j++) {
        u[j][0] = u_0(j * H); // Начальные условия
    }

    for (int i = 1; i <= M; i++) {
        u[0][i] = u_1(i * TAU); // Левое краевое условие
        u[N][i] = u_2(i * TAU); // Правое краевое условие
        for (int j = 1; j < N; j++) {
            u[j][i] = u[j][i - 1] + TAU * (u[j - 1][i - 1] - 2 * u[j][i - 1] + u[j + 1][i - 1] + f(j * H, (i - 1) * TAU));
        }

        // Вывод промежуточных значений
        printf("Explicit Scheme at t=%.2f:\n", i * TAU);
        for (int j = 0; j <= N; j++) {
            printf("u(%.2f, %.2f) = %.4f\n", j * H, i * TAU, u[j][i]);
        }
        printf("\n");
    }
}

// Симметрическая схема
void symmetric_scheme(double u[N + 1][M + 1]) {
    for (int j = 0; j <= N; j++) {
        u[j][0] = u_0(j * H);
    }

    for (int i = 1; i <= M; i++) {
        u[0][i] = u_1(i * TAU);
        u[N][i] = u_2(i * TAU);
        for (int j = 1; j < N; j++) {
            u[j][i] = u[j][i - 1] + TAU / 2 * (u[j - 1][i - 1] - 2 * u[j][i - 1] + u[j + 1][i - 1] + f(j * H, (i - 1) * TAU) +
                                                u[j - 1][i] - 2 * u[j][i] + u[j + 1][i]);
        }

        // Вывод промежуточных значений
        printf("Symmetric Scheme at t=%.2f:\n", i * TAU);
        for (int j = 0; j <= N; j++) {
            printf("u(%.2f, %.2f) = %.4f\n", j * H, i * TAU, u[j][i]);
        }
        printf("\n");
    }
}

// Схема с опережением
void predictor_corrector_scheme(double u[N + 1][M + 1]) {
    for (int j = 0; j <= N; j++) {
        u[j][0] = u_0(j * H);
    }

    for (int i = 1; i <= M; i++) {
        u[0][i] = u_1(i * TAU);
        u[N][i] = u_2(i * TAU);
        for (int j = 1; j < N; j++) {
            u[j][i] = u[j][i - 1] + TAU * (u[j - 1][i - 1] - 2 * u[j][i - 1] + u[j + 1][i - 1] + f(j * H, (i - 1) * TAU));
        }

        // Вывод промежуточных значений
        printf("Predictor-Corrector Scheme at t=%.2f:\n", i * TAU);
        for (int j = 0; j <= N; j++) {
            printf("u(%.2f, %.2f) = %.4f\n", j * H, i * TAU, u[j][i]);
        }
        printf("\n");
    }
}

// Функция для вывода результатов в таблице
void print_table(double u[N + 1][M + 1], const char *scheme_name) {
    printf("Results for %s:\n", scheme_name);
    printf("t/x\t");
    for (int j = 0; j <= N; j++) {
        printf("%.2f\t", j * H);
    }
    printf("\n");

    for (int i = 0; i <= M; i++) {
        printf("%.2f\t", i * TAU);
        for (int j = 0; j <= N; j++) {
            printf("%.4f\t", u[j][i]);
        }
        printf("\n");
    }
}

int main() {
    double u[N + 1][M + 1];

    // Явная схема
    explicit_scheme(u);
    print_table(u, "Explicit Scheme");

    // Симметрическая схема
    symmetric_scheme(u);
    print_table(u, "Symmetric Scheme");

    // Схема с опережением
    predictor_corrector_scheme(u);
    print_table(u, "Predictor-Corrector Scheme");

    return 0;
}