#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 4 // Количество точек
#define INTERPOLATION_STEP 0.1 // Шаг интерполяции

typedef struct {
    double x;
    double y;
} Point;

void cubicSplineInterpolation(Point points[], double interpolPoints[], int n) {
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
    
    // Интерполяция с помощью сплайна
    for (int i = 0; i < n - 1; i++) {
        double step = 0.1; // Шаг интерполяции
        double t = points[i].x;
        int k = 0;
        
        while (t < points[i + 1].x) {
            double delta = t - points[i].x;
            interpolPoints[k] = points[i].y + b[i] * delta + c[i] * delta * delta + d[i] * delta * delta * delta;
            t += step;
            k++;
        }
    }
}

int main() {
    Point points[N] = {{0, 0}, {1, 1}, {2, 4}, {3, 9}}; // Точки для интерполяции
    double interpolPoints[100]; // Массив для хранения интерполированных значений

    cubicSplineInterpolation(points, interpolPoints, N);

    // Открыть файл для записи
    FILE *gnuplot = popen("gnuplot -persistent", "w");
    if (gnuplot == NULL) {
        fprintf(stderr, "Ошибка при открытии GNU Plot.\n");
        return EXIT_FAILURE;
    }

    // Установить формат и имя выходного файла
    fprintf(gnuplot, "set terminal png\n");
    fprintf(gnuplot, "set output 'graph.png'\n");

    // Построить график интерполированных значений
    fprintf(gnuplot, "plot '-' with lines title 'Interpolated'\n");
    for (int i = 0; i < N - 1; i++) {
        double x = points[i].x;
        int j = 0;
        while (interpolPoints[j] != 0) {
            double y = interpolPoints[j];
            fprintf(gnuplot, "%lf %lf\n", x, y);
            x += INTERPOLATION_STEP;
            j++;
        }
    }
    fprintf(gnuplot, "e\n");

    // Закрыть файл
    fflush(gnuplot);
    pclose(gnuplot);

    printf("График успешно построен и сохранен в файле graph.png.\n");

    return 0;
}
