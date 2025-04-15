#include <stdio.h>
#include <stdlib.h>

#define N 3
#define h 0.1

void thomas_algorithm(double a[], double b[], double c[], double d[], double y[]) {
    for (int i = 1; i < N; i++) {
        double m = a[i] / b[i - 1];
        b[i] -= m * c[i - 1];
        d[i] -= m * d[i - 1];
    }

    y[N - 1] = d[N - 1] / b[N - 1];
    for (int i = N - 2; i >= 0; i--) {
        y[i] = (d[i] - c[i] * y[i + 1]) / b[i];
    }
}

int main() {
    double a[N], b[N], c[N], d[N], y[N + 1];

    // Boundary condition at x = 1.0: y1 - y0 = 0.5h => y1 - y0 = 0.05
    b[0] = -1;
    c[0] = 1;
    d[0] = 0.5 * h;

    // Middle node at x = 1.1
    double x1 = 1.1;
    a[1] = 1 + 0.5 * x1 * h;
    b[1] = -2 - 0.5 * h * h;
    c[1] = 1 - 0.5 * x1 * h;
    d[1] = 2 * x1 * h * h;

    // Boundary condition at x = 1.3: (2 + 1/h)y3 - (1/h)y2 = 2
    a[2] = -1.0 / h;
    b[2] = 2 + 1.0 / h;
    c[2] = 0;
    d[2] = 2;

    // Solve system
    thomas_algorithm(a, b, c, d, y);

    // Compute y(1.3)
    y[3] = (2 - (-1.0 / h) * y[2]) / (2 + 1.0 / h);

    printf("x\t\ty\n");
    for (int i = 0; i <= N; i++) {
        double xi = 1.0 + i * h;
        printf("%.2f\t%.6f\n", xi, y[i]);
    }

    return 0;
}