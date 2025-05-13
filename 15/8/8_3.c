#include <stdio.h>

// Константы
#define LAMBDA 0.5  // Значение λ
#define ALPHA (1.0 + 0.02 * 15)  // a = 1 + 0.02 * 15

// Функции для вычисления интегралов (аналитические результаты)
double integral_s() {
    return 0.5;  // ∫[0,1] s ds = 1/2
}

double integral_s3() {
    return 0.25;  // ∫[0,1] s^3 ds = 1/4
}

double integral_s5() {
    return 1.0 / 6.0;  // ∫[0,1] s^5 ds = 1/6
}

double integral_s7() {
    return 1.0 / 8.0;  // ∫[0,1] s^7 ds = 1/8
}

double integral_s9() {
    return 1.0 / 10.0;  // ∫[0,1] s^9 ds = 1/10
}

double integral_s11() {
    return 1.0 / 12.0;  // ∫[0,1] s^11 ds = 1/12
}

// Решение системы линейных уравнений для c1, c2, c3
void solve_system(double* c1, double* c2, double* c3) {
    // Коэффициенты уравнений
    double a1 = LAMBDA * integral_s();
    double a2 = LAMBDA * integral_s3();
    double a3 = LAMBDA * integral_s5();
    double b1 = LAMBDA * integral_s3();
    double b2 = LAMBDA * integral_s5();
    double b3 = LAMBDA * integral_s7();
    double c1_coeff = LAMBDA * integral_s5();
    double c2_coeff = LAMBDA * integral_s7();
    double c3_coeff = LAMBDA * integral_s9();

    // Правая часть (зависит от ALPHA)
    double rhs1 = ALPHA * a1 - 0.25;
    double rhs2 = ALPHA * a2 - 1.0 / 6.0;
    double rhs3 = ALPHA * a3 - 1.0 / 8.0;

    // Решение системы методом Гаусса (или другим методом)
    // Коэффициенты матрицы:
    // A = [[1 - a1, -b1, -c1_coeff],
    //      [-b1, 1 - b2, -c2_coeff],
    //      [-c1_coeff, -c2_coeff, 1 - c3_coeff]]
    // Правая часть:
    // B = [rhs1, rhs2, rhs3]

    double det = (1 - a1) * ((1 - b2) * (1 - c3_coeff) - (-c2_coeff) * (-c2_coeff))
                 - (-b1) * (-b1 * (1 - c3_coeff) - (-c1_coeff) * (-c2_coeff))
                 + (-c1_coeff) * (-b1 * (-c2_coeff) - (-b1) * (1 - b2));

    *c1 = (rhs1 * ((1 - b2) * (1 - c3_coeff) - (-c2_coeff) * (-c2_coeff))
           - (-b1) * (rhs2 * (1 - c3_coeff) - (-c2_coeff) * rhs3)
           + (-c1_coeff) * (rhs2 * (-c2_coeff) - rhs3 * (1 - b2))) / det;

    *c2 = ((1 - a1) * (rhs2 * (1 - c3_coeff) - (-c2_coeff) * rhs3)
           - rhs1 * (-b1 * (1 - c3_coeff) - (-c1_coeff) * (-c2_coeff))
           + (-c1_coeff) * (rhs1 * (-c2_coeff) - (-b1) * rhs3)) / det;

    *c3 = ((1 - a1) * ((1 - b2) * rhs3 - (-c2_coeff) * rhs2)
           - (-b1) * ((1 - b2) * rhs1 - (-c1_coeff) * rhs2)
           + rhs1 * ((1 - b2) * (-c2_coeff) - (-b1) * (-c1_coeff))) / det;
}

// Основная функция
int main() {
    double c1, c2, c3;
    solve_system(&c1, &c2, &c3);

    printf("Решение уравнения методом вырожденных ядер:\n");
    printf("c1 = %.6f\n", c1);
    printf("c2 = %.6f\n", c2);
    printf("c3 = %.6f\n", c3);

    printf("\nРешение y(x) в виде:\n");
    printf("y(x) = a - x^2 + (%.6f * x + %.6f * x^3 + %.6f * x^5) / 2\n", c1, c2, c3);

    return 0;
}