#ifndef TETRIS_H
#define TETRIS_H

#define WIDTH 10
#define HEIGHT 20
#define FIGURE_SIZE 4

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct {
  WINDOW *game_window;
  WINDOW *information_window;
  WINDOW *hi_score_window;
  WINDOW *score_window;
  WINDOW *level_window;
  WINDOW *next_figure;
} Windos_t;

// Структура для координат фигуры
typedef struct {
  int x;
  int y;
} Coordinates_t;

// Структура фигур
typedef struct {
  int block[FIGURE_SIZE][FIGURE_SIZE];
} Figure_t;

// Структура функционала игры
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

// Структура данных игры
typedef struct {
  int **field;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

// Обработка действий пользователя
void create_action(UserAction_t *action, int move);
// Действия пользователя
void userInput(UserAction_t action, int *shift_horizontal, int *shift_vertical,
               int *rotate, int *end_game, int *game_paused, int *game_start);
// Главная функция - начало игры
void tetris();
// Геймплей игры
void start_game();
// Заполнение данными структуру GameInfo_t
void GameInfo_t_initialization(GameInfo_t *game_info);
// Отчистка памяти поля
void free_field(GameInfo_t *game_info);
// Отрисовка фигур на поле
void draw_figure_on_field(GameInfo_t *game_info, Figure_t *figure,
                          Coordinates_t *coordinates);
// Смещение фигуры вниз на одну итерацию
void delete_figure(GameInfo_t *game_info, Figure_t *figure,
                   Coordinates_t *coordinates);
// Установка координат фигурам
void coordinates_figures(int rand_figure, Coordinates_t *coordinates);
// Генерация фигур
Figure_t create_figure(int rand_figure);
// Проверка столкновения фигуры по вертикали
int figure_vertical_collision(GameInfo_t *game_info, Figure_t *figure,
                              Coordinates_t *coordinates);
// Проверка столкновения фигуры по горизонтали
int figure_horizontal_collision(GameInfo_t *game_info, Figure_t *figure,
                                Coordinates_t *coordinates,
                                int shift_horizontal);
// Перемещение фигуры вниз при нажатии
void figure_move_down(GameInfo_t *game_info, Figure_t *figure,
                      Coordinates_t *coordinates);
// Проверка на завершение игры
int check_game_over(GameInfo_t *game_info);
// Уничтожение линий
void destroy_line(GameInfo_t *game_info);
// Подсчет очков игрока
void count_score(GameInfo_t *game_info, int count_line);
// Поворот фигуры
void rotate_figure(GameInfo_t *game_info, Coordinates_t *coordinates,
                   Figure_t *figure, int rand_figure);
// Установка максимального кол-ва очков
void update_hiscore(GameInfo_t *game_info);
// Запись максимального кол-ва очков в файл
void push_hiscore_on_file(GameInfo_t *game_info);
// Взятие максимального кол-ва очков из файла
void get_hiscore_from_file(GameInfo_t *game_info);
// Обновление уровня
void update_level(GameInfo_t *game_info, int *speed_game);
// Инициализация окна паузы
void window_game_pause(WINDOW **pause_window);
// Удаление окна паузы
void delete_window_game_pause(WINDOW **pause_window);
// Проверка на возможность поворота фигур
int can_rotate_figure(GameInfo_t *game_info, Coordinates_t *coordinates);
// Поворот фигуры i (влево, вправо)
void rotate_i_figure_left(Figure_t *figure);
// Поворот фигуры i (вврех, вниз)
void rotate_i_figure_up(Figure_t *figure);
// Следующие итерации
void next_iterations(Windos_t *windows, GameInfo_t *game_info, Figure_t *figure,
                     Coordinates_t *figure_coordinates, int *rand_figure,
                     int *next_figure);
// Инициализация перменных игры
void initialize_game(GameInfo_t *game_info, Figure_t *figure,
                     Coordinates_t *figure_coordinates, Windos_t *windows,
                     int *next_figure, int *game_interation, int *game_paused,
                     int *game_start, int *rand_figure);
// Тело основго цикла игры
void handle_game_start(WINDOW *pause_window, GameInfo_t *game_info,
                       Figure_t *figure, Coordinates_t *figure_coordinates,
                       Windos_t *windows, int *next_figure, int *game_iteration,
                       int *game_paused, int *speed_game, int *shift_horizontal,
                       int *shift_vertical, int *rotate, int *end_game,
                       int *game_start, int *rand_figure);
// Начальный логотип игры
void print_logo_game();
// Отрисовка окон игры
void init_windows(GameInfo_t *game_info, Windos_t *window, int next_num_figure);
// Удаление окон
void delete_windows(Windos_t *window);
// Обновление окон
void refresh_windows(GameInfo_t *game_info, Windos_t *window,
                     int next_num_figure);
void print_next_figure(int next_num_figure, Windos_t *window);
void print_game_field(GameInfo_t *game_info, Windos_t *window);
void print_hiscore(GameInfo_t *game_info, Windos_t *window);
void print_score(GameInfo_t *game_info, Windos_t *window);
void print_level(GameInfo_t *game_info, Windos_t *window);
// Вывод о завершении игры
void print_game_over();

#endif