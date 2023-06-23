#include <stdio.h>
#include <stdlib.h>

// Функция для вычисления интерполированного значения
double cubicSplineInterpolation(double x, double xi[], double fi[], int n) {
    int i;

    for (i = 0; i < n - 1; i++) {
        if (x >= xi[i] && x <= xi[i + 1]) {
            break;
        }
    }

    double h1 = xi[i + 1] - xi[i];
    double h2 = xi[i + 2] - xi[i + 1];
    double delta1 = (fi[i + 1] - fi[i]) / h1;
    double delta2 = (fi[i + 2] - fi[i + 1]) / h2;

    double a0 = fi[i];
    double a1 = (((xi[i + 1] - xi[i]) / (xi[i + 1] - xi[i - 1])) * ((fi[i + 1] - fi[i - 1]) / (xi[i] - xi[i - 1]))) +
                (((xi[i] - xi[i - 1]) / (xi[i + 1] - xi[i - 1])) * ((fi[i] - fi[i - 1]) / (xi[i] - xi[i - 1])));
    double a2 = (1 / (xi[i + 1] - xi[i])) *
                (3 * ((fi[i + 1] - fi[i]) / (xi[i + 1] - xi[i])) -
                 2 * ((xi[i + 1] - xi[i]) / (xi[i + 1] - xi[i - 1])) * ((fi[i] - fi[i - 1]) / (xi[i] - xi[i - 1])) -
                 (((xi[i + 2] - xi[i + 1]) / (xi[i + 2] - xi[i])) *
                  ((fi[i + 1] - fi[i]) / (xi[i + 1] - xi[i])) +
                  ((xi[i + 1] - xi[i]) / (xi[i + 2] - xi[i])) * ((fi[i + 2] - fi[i + 1]) / (xi[i + 2] - xi[i + 1]))));
    double a3 = (1 / ((xi[i + 1] - xi[i]) * (xi[i + 1] - xi[i]))) /
                (-2 * ((fi[i + 1] - fi[i]) / (xi[i + 1] - xi[i])) +
                 ((xi[i + 1] - xi[i]) / (xi[i + 1] - xi[i - 1])) * ((fi[i] - fi[i - 1]) / (xi[i] - xi[i - 1])) +
                 (xi[i] - xi[i - 1]) +
                 (((xi[i] - xi[i - 1]) / (xi[i + 1] - xi[i - 1])) *
                  ((fi[i + 1] - fi[i]) / (xi[i + 1] - xi[i])) +
                  ((xi[i + 1] - xi[i]) / (xi[i + 2] - xi[i])) * ((fi[i + 2] - fi[i + 1]) / (xi[i + 2] - xi[i + 1])) *
                      ((fi[i + 1] - fi[i]) / (xi[i + 1] - xi[i])) +
                  ((xi[i + 1] - xi[i]) / (xi[i + 2] - xi[i])) * ((fi[i + 2] - fi[i + 1]) / (xi[i + 2] - xi[i + 1])) *
                      ((fi[i + 1] - fi[i]) / (xi[i + 1] - xi[i]))));

    double result = 0;
    double xPow = 1;

    for (int j = 0; j < 4; j++) {
        result += (a0 + a1 * xPow + a2 * xPow * xPow + a3 * xPow * xPow * xPow);
        xPow *= (x - xi[i]);
    }

    return result;
}

int main() {
    // Заданные точки и значения
    double xi[] = {1.0, 2.0, 3.0, 4.0, 5.0};    // Заданные точки xi
    double fi[] = {4.0, 5.0, 6.0, 8.0, 2.0};    // Значения в заданных точках fi
    int n = sizeof(xi) / sizeof(xi[0]);        // Количество точек

    // Интерполирование
    int numInterpolatedPoints = 10;            // Количество интерполированных точек
    double stepSize = (xi[n - 1] - xi[0]) / (numInterpolatedPoints - 1);

    FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
    fprintf(gnuplotPipe, "plot '-' with lines\n");

    for (int i = 0; i < numInterpolatedPoints; i++) {
        double interpolatePoint = xi[0] + i * stepSize;
        double interpolatedValue = cubicSplineInterpolation(interpolatePoint, xi, fi, n);

        fprintf(gnuplotPipe, "%f %f\n", interpolatePoint, interpolatedValue);
    }

    fprintf(gnuplotPipe, "e\n");
    pclose(gnuplotPipe);

    return 0;
}
