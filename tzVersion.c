#include <stdio.h>

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
    // Задание количества точек
    int n;
    printf("vvedite kollichestvo tochek: ");
    scanf("%d", &n);

    // Ввод точек xi
    double xi[n];
    printf("vvedite znacchenie tochek xi:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &xi[i]);
    }

    // Ввод значений fi
    double fi[n];
    printf("vvedite znachenie in zadannix tochkax fi:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &fi[i]);
    }

    // Интерполирование
    int numInterpolatedPoints = 10;            // Количество интерполированных точек
    double stepSize = (xi[n - 1] - xi[0]) / (numInterpolatedPoints - 1);

    printf("Interpolated values:\n");
    for (int i = 0; i < numInterpolatedPoints; i++) {
        double interpolatePoint = xi[0] + i * stepSize;
        double interpolatedValue = cubicSplineInterpolation(interpolatePoint, xi, fi, n);

        printf("x=%.2f, f=%.2f\n", interpolatePoint, interpolatedValue);
    }

    system ("pause");
    return 0;
}
