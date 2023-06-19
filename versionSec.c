#include <stdio.h>

// Функция для интерполяции дискретным сплайном 3-ей степени
double splineInterpolation(double x0, double x1, double x2, double x3, double y0, double y1, double y2, double y3, double x) {
    // Вычисление разностей между значениями x
    double h1 = x1 - x0;
    double h2 = x2 - x1;
    double h3 = x3 - x2;
    
    // Вычисление коэффициентов сплайна
    double a0 = y0;
    double a1 = (y1 - y0) / h1;
    double a2 = ((y2 - y1) / h2 - a1) / (h2 + h1);
    double a3 = ((y3 - y2) / h3 - a2) / (h3 + h2);
    
    // Вычисление интерполированного значения при заданном x
    double t = x - x1;
    double t2 = t * t;
    double t3 = t2 * t;
    
    double result = a0 + a1 * t + a2 * t2 + a3 * t3;
    return result;
}

int main() {
    // Заданные точки и значения y
    double x0 = -1.0, y0 = 5.0;
    double x1 = 0.0, y1 = 3.0;
    double x2 = 1.0, y2 = 7.0;
    double x3 = 2.0, y3 = 4.0;
    
    // Вывод значений интерполяции для каждого интервала
    printf("Значения интерполяции для каждого интервала:\n");
    
    // Интервал (x0, x1)
    printf("Интервал (%.2f, %.2f):\n", x0, x1);
    for (double x = x0; x < x1; x += 0.1) {
        double interpolatedValue = splineInterpolation(x0, x1, x2, x3, y0, y1, y2, y3, x);
        printf("x = %.2f, y (интерполяция) = %.2f\n", x, interpolatedValue);
    }
    
    // Интервал (x1, x2)
    printf("Интервал (%.2f, %.2f):\n", x1, x2);
    for (double x = x1; x < x2; x += 0.1) {
        double interpolatedValue = splineInterpolation(x0, x1, x2, x3, y0, y1, y2, y3, x);
        printf("x = %.2f, y (интерполяция) = %.2f\n", x, interpolatedValue);
    }
    
    // Интервал (x2, x3)
    printf("Интервал (%.2f, %.2f):\n", x2, x3);
    for (double x = x2; x <= x3; x += 0.1) {
        double interpolatedValue = splineInterpolation(x0, x1, x2, x3, y0, y1, y2, y3, x);
        printf("x = %.2f, y (интерполяция) = %.2f\n", x, interpolatedValue);
    }
    
    return 0;
}
