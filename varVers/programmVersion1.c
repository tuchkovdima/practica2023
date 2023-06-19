#include <stdio.h>

typedef struct {
    double x;
    double y;
} Point;

double cubicSplineInterpolation(double x, Point points[]) {
    double h[3], alpha[3], l[3], mu[3], z[3], c[4], b[4], d[4];
    
    // Вычисление разностей x
    for (int i = 0; i < 3; i++) {
        h[i] = points[i + 1].x - points[i].x;
    }
    
    // Вычисление коэффициентов alpha
    for (int i = 1; i < 3; i++) {
        alpha[i] = (3 / h[i]) * (points[i + 1].y - points[i].y) - (3 / h[i - 1]) * (points[i].y - points[i - 1].y);
    }
    
    // Вычисление прогоночных коэффициентов
    l[0] = 1;
    mu[0] = 0;
    z[0] = 0;
    
    for (int i = 1; i < 3; i++) {
        l[i] = 2 * (points[i + 1].x - points[i - 1].x) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }
    
    l[2] = 1;
    z[2] = 0;
    c[3] = 0;
    
    // Вычисление коэффициентов c
    for (int j = 2; j >= 0; j--) {
        c[j] = z[j] - mu[j] * c[j + 1];
        b[j] = (points[j + 1].y - points[j].y) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
        d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
    }
    
    // Интерполяция с помощью сплайна
    int i;
    for (i = 0; i < 3; i++) {
        if (x >= points[i].x && x <= points[i + 1].x) {
            break;
        }
    }
    
    double delta = x - points[i].x;
    double interpolatedValue = points[i].y + b[i] * delta + c[i] * delta * delta + d[i] * delta * delta * delta;
    
    return interpolatedValue;
}

int main() {
   Point points[4] = {{1.0, 2.0}, {2.0, 3.0}, {3.0, 5.0}, {4.0, 7.0}}; // Заданные точки для интерполяции
    
    double x = 2.5; // Значение x, для которого нужно выполнить интерполяцию
    double interpolatedValue = cubicSplineInterpolation(x, points);
    
    printf("Interpolated value at x = %.2f: %.2f\n", x, interpolatedValue);
    
    return 0;
}
