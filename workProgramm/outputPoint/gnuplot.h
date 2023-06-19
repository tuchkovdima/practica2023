#ifndef GNUPLOT_H
#define GNUPLOT_H

// Структура для представления команды gnuplot
typedef struct {
    FILE *pipe; // Поток для взаимодействия с gnuplot
} gnuplot_ctrl;

// Функции для работы с gnuplot

gnuplot_ctrl *gnuplot_init();
void gnuplot_close(gnuplot_ctrl *h);
void gnuplot_cmd(gnuplot_ctrl *h, const char *cmd);

#endif // GNUPLOT_H
