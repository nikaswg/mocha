#include <stdio.h>
#include <math.h>

#define N 10        // Количество точек по x
#define M 20        // Количество шагов по t
#define L 1.0       // Длина области
#define T 0.5       // Время
#define H (L/N)     // Шаг по x
#define K (T/M)     // Шаг по t
#define C (K/H)     // Численный коэффициент

// Функции начальных условий
double f(double x) {
    return 0.5 * (x + 1);
}

double Phi(double x) {
    return (x + 0.5) * cos(M_PI * x);
}

// Краевые условия
double phi(double t) {
    return 0.5;
}

double psi(double t) {
    return 2 - 3*t;
}

void explicit_scheme() {
    double u[N + 1][M + 1] = {0}; // Массив для хранения значений u
    double x;

    // Начальные условия
    for (int i = 0; i <= N; i++) {
        x = i * H;
        u[i][0] = f(x);
        if (i == 0) {
            u[i][1] = phi(K); // u(0, t)
        } else if (i == N) {
            u[i][1] = psi(K); // u(1, t)
        } else {
            u[i][1] = u[i][0] + K * Phi(x); // u_t(x, 0)
        }
    }

    // Итерация по времени
    for (int n = 1; n < M; n++) {
        for (int i = 1; i < N; i++) {
            u[i][n + 1] = 2 * u[i][n] - u[i][n - 1] + C * C * (u[i + 1][n] - 2 * u[i][n] + u[i - 1][n]);
        }
        u[0][n + 1] = phi((n + 1) * K); // Краевое условие u(0, t)
        u[N][n + 1] = psi((n + 1) * K); // Краевое условие u(1, t)
    }

    // Вывод результата для явной схемы
    printf("Результаты u(x,t) по явной схеме:\n");
    for (int n = 0; n <= M; n++) {
        for (int i = 0; i <= N; i++) {
            printf("u(%.2f, %.2f) = %.4f\n", i * H, n * K, u[i][n]);
        }
    }
}

int main() {
    explicit_scheme(); // Вызов явной схемы
    return 0;
}