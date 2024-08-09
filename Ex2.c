#include <stdio.h>

// Define the function to be integrated
double f(double x) {
    return (140000.0 / (140000.0 - 2100.0 * x)) - 9.8 * x;
}

// Function to perform numerical integration using the trapezoidal rule
double trapezoidal_rule(double a, double b, int n) {
    double h = (b - a) / n; // Width of each segment
    double sum = (f(a) + f(b)) / 2.0;

    for (int i = 1; i < n; i++) {
        double xi = a + i * h;
        sum += f(xi);
    }

    return sum * h;
}

// linear regression
void linear_regression(int n, double x[], double y[], double *m, double *c) {
    double sum_x = 0.0, sum_y = 0.0;
    double sum_x2 = 0.0, sum_xy = 0.0;

    // Calculate the sums needed for the formulas
    for (int i = 0; i < n; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_x2 += x[i] * x[i];
        sum_xy += x[i] * y[i];
    }

    // Compute the slope (m) and intercept (c)
    *m = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    *c = (sum_y - (*m) * sum_x) / n;
}

int main() {
    // Numerical Integration
    {
        double a = 8.0;    // Lower limit of integration
        double b = 30.0;   // Upper limit of integration
        int n = 10000;     // Number of segments

        double result = trapezoidal_rule(a, b, n);
        printf("The integral of the function from %f to %f is approximately %f\n", a, b, result);
    }

    // Linear Regression
    {
        // Example data
        int n = 5; // Number of data points
        double x[] = {1, 2, 3, 4, 5};
        double y[] = {2, 4, 6, 8, 10};

        double m, c; // Slope and intercept

        // Perform linear regression
        linear_regression(n, x, y, &m, &c);

        // Print the results
        printf("Slope (m): %f\n", m);
        printf("Intercept (c): %f\n", c);
    }

    return 0;
}
