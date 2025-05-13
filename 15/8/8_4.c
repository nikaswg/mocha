#include <stdio.h>
#include <math.h>

#define ALPHA 1.3  // Заданное значение α
#define H 0.25     // Шаг по x

double integral(int k) {
    return 1.0 / (k + 1);
}

void solve_system(double matrix[4][5], double results[4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            double factor = matrix[j][i] / matrix[i][i];
            for (int k = i; k < 5; k++) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }
    for (int i = 3; i >= 0; i--) {
        results[i] = matrix[i][4];
        for (int j = i + 1; j < 4; j++) {
            results[i] -= matrix[i][j] * results[j];
        }
        results[i] /= matrix[i][i];
    }
}

int main() {
    double matrix[4][5] = {0};
    double results[4] = {0};

    for (int i = 0; i < 4; i++) {
        double x_i = (i + 1) * H;
        matrix[i][0] = 1.0;  // Коэффициент при c_0 (α)
        for (int j = 1; j <= 4; j++) {
            matrix[i][j] = pow(x_i, j);
        }
        // Измените правую часть так, чтобы добиться одинаковых c_1, c_2, c_3
        matrix[i][4] = ALPHA - x_i * x_i; // Можно изменить это выражение
    }

    solve_system(matrix, results);

    printf("Решение методом коллокации:\n");
    for (int i = 0; i < 4; i++) {
        printf("c_%d = %.6f\n", i + 1, results[i]);
    }

    return 0;
}