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
    // Ввод количества точек и значений
    int n;
    printf("vvedite collichestvo tochek:: ");
    scanf("%d", &n);

    // Выделение памяти для массивов
    double* xi = malloc(n * sizeof(double));
    double* fi = malloc(n * sizeof(double));

    // Ввод точек и значений
    printf("vvedite znachenie tochek xi and  znachenie fi: \n");
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &xi[i], &fi[i]);
    }

    // Интерполирование
    int numInterpolatedPoints = 10;            // Количество интерполированных точек
    double stepSize = (xi[n - 1] - xi[0]) / (numInterpolatedPoints - 1);

    // Создание файла для сохранения данных
    FILE* dataFile = fopen("data.txt", "w");
    if (dataFile == NULL) {
        printf("error open file.\n");
        return 1;
    }

    // Сохранение данных в файл
    for (int i = 0; i < numInterpolatedPoints; i++) {
        double interpolatePoint = xi[0] + i * stepSize;
        double interpolatedValue = cubicSplineInterpolation(interpolatePoint, xi, fi, n);

        fprintf(dataFile, "%f %f\n", interpolatePoint, interpolatedValue);
    }

    fclose(dataFile);

    // Освобождение памяти
    free(xi);
    free(fi);

    // Выполнение команды Python для построения графика
    system("python D:\\PRACTICA2023\\practica2023\\usinPyton\\plot_graph.py");

    return 0;
}
