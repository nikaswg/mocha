#include <stdio.h>
#include <stdlib.h>

#define N 3  // Number of internal nodes (y1, y2, y3)
#define h 0.1

void gauss_elimination(double A[N][N+1], double x[N]) {
    for (int i = 0; i < N; i++) {
        for (int k = i + 1; k < N; k++) {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j <= N; j++) {
                A[k][j] -= factor * A[i][j];
            }
        }
    }

    for (int i = N - 1; i >= 0; i--) {
        x[i] = A[i][N];
        for (int j = i + 1; j < N; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
}

int main() {
    double A[N][N+1] = {0};
    double x[N] = {0};
    double y[N+1] = {0};

    // Internal nodes: x = 1.0, 1.1, 1.2
    for (int i = 1; i < N - 1; i++) {
        double xi = 1.0 + i * h;
        A[i][i-1] = 1 + 0.5 * xi * h;
        A[i][i]   = -2 - 0.5 * h * h;
        A[i][i+1] = 1 - 0.5 * xi * h;
        A[i][N]   = 2 * xi * h * h;
    }

    // Boundary condition at x = 1.0: y'(1) = 0.5 => (y1 - y0)/h = 0.5 => y1 - y0 = 0.5h
    A[0][0] = -1;
    A[0][1] = 1;
    A[0][N] = 0.5 * h;

    // Boundary condition at x = 1.3: 2y - y'/h = 2 => 2y3 - (y3 - y2)/h = 2
    // => (2 + 1/h) y3 - (1/h) y2 = 2
    A[2][1] = -1.0 / h;
    A[2][2] = 2 + 1.0 / h;
    A[2][N] = 2;

    // Solve the system
    gauss_elimination(A, x);

    // Reconstruct full y array
    y[0] = x[0];  // y1: x=1.0
    y[1] = x[1];  // y2: x=1.1
    y[2] = x[2];  // y3: x=1.2
    y[3] = (2 - (-1.0 / h) * y[2]) / (2 + 1.0 / h);  // y(1.3) from boundary

    printf("x\t\ty\n");
    for (int i = 0; i <= N; i++) {
        double xi = 1.0 + i * h;
        printf("%.2f\t%.6f\n", xi, y[i]);
    }

    return 0;
}