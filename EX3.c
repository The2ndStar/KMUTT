#include <stdio.h>
#include <math.h>

#define N 4 // Size of the matrix

void gaussianElimination(double a[N][N], double b[N], double x[N]) {
    for (int i = 0; i < N; i++) {
        // Search for the maximum in this column
        double maxEl = fabs(a[i][i]);
        int maxRow = i;
        for (int k = i + 1; k < N; k++) {
            if (fabs(a[k][i]) > maxEl) {
                maxEl = fabs(a[k][i]);
                maxRow = k;
            }
        }

        // Swap the maximum row with the current row
        for (int k = i; k < N; k++) {
            double tmp = a[maxRow][k];
            a[maxRow][k] = a[i][k];
            a[i][k] = tmp;
        }
        double tmp = b[maxRow];
        b[maxRow] = b[i];
        b[i] = tmp;

        // Make all rows below this one 0 in the current column
        for (int k = i + 1; k < N; k++) {
            double c = -a[k][i] / a[i][i];
            for (int j = i; j < N; j++) {
                if (i == j) {
                    a[k][j] = 0;
                } else {
                    a[k][j] += c * a[i][j];
                }
            }
            b[k] += c * b[i];
        }
    }

    // Solve equation Ax = b for an upper triangular matrix
    for (int i = N - 1; i >= 0; i--) {
        x[i] = b[i] / a[i][i];
        for (int k = i - 1; k >= 0; k--) {
            b[k] -= a[k][i] * x[i];
        }
    }
}

int main() {
    // Matrix A
    double a[N][N] = {
        {1, -2, 2, -3},
        {3, 2, -1, 5},
        {2, -3, 4, -1},
        {3, -2, -1, 2}
    };

    // Vector b
    double b[N] = {-7, 22, -3, 12};

    // Solution vector x
    double x[N];

    gaussianElimination(a, b, x);

    // Print the solution
    printf("Solution:\n");
    for (int i = 0; i < N; i++) {
        printf("x%d = %lf\n", i + 1, x[i]);
    }

    return 0;
}
