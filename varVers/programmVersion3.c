#include <stdio.h>
#include <math.h>

#define N 4 // Количество точек

typedef struct {
    double x;
    double y;
} Point;

void cubicSplineInterpolation(Point points[], double interpolPoints[], int n, double x0, double y0, double x1, double y1) {
    double h[N], alpha[N], l[N], mu[N], z[N], c[N], b[N], d[N];
    
    // Вычисление разностей x
    for (int i = 0; i < n - 1; i++) {
        h[i] = points[i + 1].x - points[i].x;
    }
    
    // Вычисление коэффициентов alpha
    for (int i = 1; i < n - 1; i++) {
        alpha[i] = (3 / h[i]) * (points[i + 1].y - points[i].y) - (3 / h[i - 1]) * (points[i].y - points[i - 1].y);
    }
    
    // Вычисление прогоночных коэффициентов
    l[0] = 1;
    mu[0] = 0;
    z[0] = 0;
    
    for (int i = 1; i < n - 1; i++) {
        l[i] = 2 * (points[i + 1].x - points[i - 1].x) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }
    
    l[n - 1] = 1;
    z[n - 1] = 0;
    c[n - 1] = 0;
    
    // Вычисление коэффициентов c
    for (int j = n - 2; j >= 0; j--) {
        c[j] = z[j] - mu[j] * c[j + 1];
        b[j] = (points[j + 1].y - points[j].y) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
        d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
    }
    
    // Интерполяция на интервале между x0 и x1
    double step = 0.1; // Шаг интерполяции
    double t = x0;
    int k = 0;
    
    while (t <= x1) {
        // Находим соответствующие коэффициенты для интерполяции на данном интервале
        int intervalIndex = -1;
        for (int i = 0; i < n - 1; i++) {
            if (points[i].x <= t && t <= points[i + 1].x) {
                intervalIndex = i;
                break;
            }
        }
        
        if (intervalIndex != -1) {
            double delta = t - points[intervalIndex].x;
            double interpolatedValue = points[intervalIndex].y + b[intervalIndex] * delta + c[intervalIndex] * delta * delta + d[intervalIndex] * delta * delta * delta;
            interpolPoints[k] = interpolatedValue;
        } else {
            // Вне заданного интервала, присваиваем значение y0 или y1
            interpolPoints[k] = (t < x0) ? y0 : y1;
        }
        
        t += step;
        k++;
    }
}

int main() {
    Point points[N] = {{0, 0}, {1, 1}, {2, 4}, {3, 9}}; // Точки для интерполяции
    double interpolPoints[100]; // Массив для хранения интерполированных значений
    
    double x0 = 1.5; // Начальное значение интервала
    double y0 = 2.5; // Интерполированное значение для x0
    double x1 = 2.5; // Конечное значение интервала
    double y1 = 6.25; // Интерполированное значение для x1
    
    cubicSplineInterpolation(points, interpolPoints, N, x0, y0, x1, y1);
    
    printf("+------+------------+\n");
    printf("|   x  | Interpolated |\n");
    printf("+------+------------+\n");
    
    for (int i = 0; i < N - 1; i++) {
        printf("| %4.1f | %10.8f |\n", points[i].x, points[i].y);
        
        int j = 0;
        while (interpolPoints[j] != 0) {
            printf("| %4.1f | %10.8f |\n", x0 + (j + 1) * 0.1, interpolPoints[j]);
            j++;
        }
        
        printf("+------+------------+\n");
    }
    
    return 0;
}
