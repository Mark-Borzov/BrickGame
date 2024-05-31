#include "tetris.h"

Figure_t create_o_figure() {
  Figure_t o_figure = {0};
  o_figure.block[0][0] = 1;
  o_figure.block[0][1] = 1;
  o_figure.block[1][0] = 1;
  o_figure.block[1][1] = 1;
  return o_figure;
}

Figure_t create_i_figure() {
  Figure_t i_figure = {0};
  i_figure.block[0][0] = 1;
  i_figure.block[0][1] = 1;
  i_figure.block[0][2] = 1;
  i_figure.block[0][3] = 1;
  return i_figure;
}

Figure_t create_t_figure() {
  Figure_t t_figure = {0};
  t_figure.block[0][1] = 1;
  t_figure.block[1][0] = 1;
  t_figure.block[1][1] = 1;
  t_figure.block[1][2] = 1;
  return t_figure;
}

Figure_t create_l_figure() {
  Figure_t l_figure = {0};
  l_figure.block[0][2] = 1;
  l_figure.block[1][0] = 1;
  l_figure.block[1][1] = 1;
  l_figure.block[1][2] = 1;
  return l_figure;
}

Figure_t create_j_figure() {
  Figure_t j_figure = {0};
  j_figure.block[0][0] = 1;
  j_figure.block[1][0] = 1;
  j_figure.block[1][1] = 1;
  j_figure.block[1][2] = 1;
  return j_figure;
}

Figure_t create_s_figure() {
  Figure_t s_figure = {0};
  s_figure.block[0][1] = 1;
  s_figure.block[0][2] = 1;
  s_figure.block[1][0] = 1;
  s_figure.block[1][1] = 1;
  return s_figure;
}

Figure_t create_z_figure() {
  Figure_t z_figure = {0};
  z_figure.block[0][0] = 1;
  z_figure.block[0][1] = 1;
  z_figure.block[1][1] = 1;
  z_figure.block[1][2] = 1;
  return z_figure;
}

void tetris() {
  int game_started = 1;
  print_logo_game();
  while (game_started != 0) {
    mvprintw(11, 1, "To start the game, press the 'f' key.");
    flushinp();
    if (getch() == 'f' || getch() == 'F') {
      game_started = 0;
      clear();
      refresh();
    }
  }
  start_game();
}

void start_game() {
  GameInfo_t game_info;
  Figure_t figure;
  Coordinates_t figure_coordinates;
  Windos_t windows;
  int next_figure;
  WINDOW *pause_window;
  int rand_figure = rand() % 7;
  int game_iteration;
  int game_paused;
  int game_start;
  initialize_game(&game_info, &figure, &figure_coordinates, &windows,
                  &next_figure, &game_iteration, &game_paused, &game_start,
                  &rand_figure);
  while (game_iteration) {
    UserAction_t action;
    int speed_game = 500000;
    int shift_horizontal = 0;
    int shift_vertical = 0;
    int rotate = 0;
    int end_game = 0;
    if (game_paused) {
      while (game_paused) {
        window_game_pause(&pause_window);
        create_action(&action, getch());
        userInput(action, &shift_horizontal, &shift_vertical, &rotate,
                  &end_game, &game_paused, &game_start);
      }
    } else if (game_start) {
      handle_game_start(pause_window, &game_info, &figure, &figure_coordinates,
                        &windows, &next_figure, &game_iteration, &game_paused,
                        &speed_game, &shift_horizontal, &shift_vertical,
                        &rotate, &end_game, &game_start, &rand_figure);
    }
  }
  free_field(&game_info);
  delete_windows(&windows);
}

void handle_game_start(WINDOW *pause_window, GameInfo_t *game_info,
                       Figure_t *figure, Coordinates_t *figure_coordinates,
                       Windos_t *windows, int *next_figure, int *game_iteration,
                       int *game_paused, int *speed_game, int *shift_horizontal,
                       int *shift_vertical, int *rotate, int *end_game,
                       int *game_start, int *rand_figure) {
  delete_window_game_pause(&pause_window);
  UserAction_t action;
  create_action(&action, getch());
  flushinp();
  userInput(action, shift_horizontal, shift_vertical, rotate, end_game,
            game_paused, game_start);
  draw_figure_on_field(game_info, figure, figure_coordinates);
  refresh_windows(game_info, windows, *next_figure);
  delete_figure(game_info, figure, figure_coordinates);
  figure_horizontal_collision(game_info, figure, figure_coordinates,
                              *shift_horizontal);

  if (check_game_over(game_info)) {
    *game_iteration = 0;
  } else if (figure_vertical_collision(game_info, figure, figure_coordinates)) {
    next_iterations(windows, game_info, figure, figure_coordinates, rand_figure,
                    next_figure);
  } else if (*shift_vertical == 1) {
    while (figure_vertical_collision(game_info, figure, figure_coordinates) ==
           0) {
      figure_move_down(game_info, figure, figure_coordinates);
    }
  } else if (*rotate == 1) {
    rotate_figure(game_info, figure_coordinates, figure, *rand_figure);
    figure_coordinates->x++;
  } else if (*end_game == 1) {
    *game_iteration = 0;
  } else {
    figure_coordinates->x++;
  }
  update_level(game_info, speed_game);
  update_hiscore(game_info);
  usleep(*speed_game);
}

void initialize_game(GameInfo_t *game_info, Figure_t *figure,
                     Coordinates_t *figure_coordinates, Windos_t *windows,
                     int *next_figure, int *game_interation, int *game_paused,
                     int *game_start, int *rand_figure) {
  GameInfo_t_initialization(game_info);
  *next_figure = rand() % 7;
  coordinates_figures(*rand_figure, figure_coordinates);
  *figure = create_figure(*rand_figure);
  init_windows(game_info, windows, *next_figure);
  get_hiscore_from_file(game_info);
  *game_interation = 1;
  *game_paused = 0;
  *game_start = 1;
}

void next_iterations(Windos_t *windows, GameInfo_t *game_info, Figure_t *figure,
                     Coordinates_t *figure_coordinates, int *rand_figure,
                     int *next_figure) {
  draw_figure_on_field(game_info, figure, figure_coordinates);
  *rand_figure = *next_figure;
  coordinates_figures(*rand_figure, figure_coordinates);
  *figure = create_figure(*rand_figure);
  *next_figure = rand() % 7;
  refresh_windows(game_info, windows, *next_figure);
  destroy_line(game_info);
}

void rotate_figure(GameInfo_t *game_info, Coordinates_t *coordinates,
                   Figure_t *figure, int rand_figure) {
  if (rand_figure == 0) {
    return;  // Фигура типа O не может вращаться
  } else if (rand_figure == 1) {
    if (can_rotate_figure(game_info, coordinates)) {
      if (figure->block[1][1] == 0) {
        rotate_i_figure_left(figure);
      } else if (figure->block[1][1] == 1) {
        rotate_i_figure_up(figure);
      }
    }
  } else {
    if (can_rotate_figure(game_info, coordinates)) {
      Figure_t temp_figure = {0};
      for (int i = 0; i < FIGURE_SIZE; i++) {
        for (int j = 0; j < FIGURE_SIZE; j++) {
          temp_figure.block[j][(FIGURE_SIZE - 1) - 1 - i] = figure->block[i][j];
        }
      }
      *figure = temp_figure;
    }
  }
}

void rotate_i_figure_left(Figure_t *figure) {
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      figure->block[i][j] = 0;
      if (j == 1) {
        figure->block[i][j] = 1;
      }
    }
  }
}

void rotate_i_figure_up(Figure_t *figure) {
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      figure->block[i][j] = 0;
      if (i == 0) {
        figure->block[i][j] = 1;
      }
    }
  }
}

int can_rotate_figure(GameInfo_t *game_info, Coordinates_t *coordinates) {
  int result = 1;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (coordinates->x + i >= HEIGHT || coordinates->y + j >= WIDTH ||
          coordinates->y + j < 0 ||
          game_info->field[coordinates->x + i][coordinates->y + j] != 0) {
        // Фигура не может вращаться из-за стены или занятых клеток
        result = 0;
      }
    }
  }
  return result;
}

void create_action(UserAction_t *action, int move) {
  if (move == KEY_LEFT) {
    *action = Left;
  } else if (move == KEY_RIGHT) {
    *action = Right;
  } else if (move == KEY_DOWN) {
    *action = Down;
  } else if (move == KEY_UP) {
    *action = Up;
  } else if (move == 'q' || move == 'Q') {
    *action = Terminate;
  } else if (move == 'w' || move == 'W') {
    *action = Pause;
  } else if (move == 'e' || move == 'E') {
    *action = Start;
  } else {
    *action = Action;
  }
}

void userInput(UserAction_t action, int *shift_horizontal, int *shift_vertical,
               int *rotate, int *end_game, int *game_paused, int *game_start) {
  if (action == Left) {
    *shift_horizontal = -1;
  } else if (action == Right) {
    *shift_horizontal = 1;
  } else if (action == Down) {
    *shift_vertical = 1;
  } else if (action == Up) {
    *rotate = 1;
  } else if (action == Terminate) {
    *end_game = 1;
  } else if (action == Pause) {
    *game_paused = 1;
    *game_start = 0;
  } else if (action == Start) {
    *game_paused = 0;
    *game_start = 1;
  }
}

// Начальная скорость - 0.50 сек.
void update_level(GameInfo_t *game_info, int *speed_game) {
  if (game_info->score >= 600) {
    game_info->level = 2;
    *speed_game = 450000;  // 0.45 сек.
  }
  if (game_info->score >= 1200) {
    game_info->level = 3;
    *speed_game = 400000;  // 0.40 сек.
  }
  if (game_info->score >= 1800) {
    game_info->level = 4;
    *speed_game = 350000;  // 0.35 сек.
  }
  if (game_info->score >= 2400) {
    game_info->level = 5;
    *speed_game = 300000;  // 0.30 сек.
  }
  if (game_info->score >= 3000) {
    game_info->level = 6;
    *speed_game = 250000;  // 0.25 сек.
  }
  if (game_info->score >= 3600) {
    game_info->level = 7;
    *speed_game = 200000;  // 0.20 сек.
  }
  if (game_info->score >= 4200) {
    game_info->level = 8;
    *speed_game = 150000;  // 0.15 сек.
  }
  if (game_info->score >= 4800) {
    game_info->level = 9;
    *speed_game = 100000;  // 0.10 сек.
  }
  if (game_info->score >= 5400) {
    game_info->level = 10;
    *speed_game = 50000;  // 0.05 сек.
  }
}

void GameInfo_t_initialization(GameInfo_t *game_info) {
  game_info->field = (int **)malloc(HEIGHT * sizeof(int *));
  for (int i = 0; i < HEIGHT; i++) {
    game_info->field[i] = (int *)malloc(WIDTH * sizeof(int));
  }
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      game_info->field[i][j] = 0;
    }
  }
  game_info->level = 1;
  game_info->high_score = 0;
  game_info->score = 0;
  game_info->speed = 1;
  game_info->pause = 0;
}

int figure_horizontal_collision(GameInfo_t *game_info, Figure_t *figure,
                                Coordinates_t *coordinates,
                                int shift_horizontal) {
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (figure->block[i][j] == 1) {
        if (!(coordinates->y + j + shift_horizontal < WIDTH &&
              coordinates->y + j + shift_horizontal >= 0 &&
              game_info->field[coordinates->x + i]
                              [coordinates->y + j + shift_horizontal] == 0)) {
          shift_horizontal = 0;
        }
      }
    }
  }
  coordinates->y += shift_horizontal;
  return 0;
}

void destroy_line(GameInfo_t *game_info) {
  int count_line = 0;
  for (int i = 0; i < HEIGHT; i++) {
    int line_filled = 1;
    for (int j = 0; j < WIDTH; j++) {
      if (game_info->field[i][j] != 1) {
        line_filled = 0;
        break;
      }
    }
    if (line_filled) {
      count_line++;
      for (int j = 0; j < WIDTH; j++) {
        game_info->field[i][j] = 0;
      }
      for (int k = i; k > 0; k--) {
        for (int j = 0; j < WIDTH; j++) {
          game_info->field[k][j] = game_info->field[k - 1][j];
        }
      }
    }
  }
  count_score(game_info, count_line);
}

void count_score(GameInfo_t *game_info, int count_line) {
  if (count_line == 1) {
    game_info->score += 100;
  } else if (count_line == 2) {
    game_info->score += 300;
  } else if (count_line == 3) {
    game_info->score += 700;
  } else if (count_line >= 4) {
    game_info->score += 1500;
  }
}

void free_field(GameInfo_t *game_info) {
  for (int i = 0; i < HEIGHT; i++) {
    free(game_info->field[i]);
  }
  free(game_info->field);
  game_info->field = NULL;
}

void draw_figure_on_field(GameInfo_t *game_info, Figure_t *figure,
                          Coordinates_t *coordinates) {
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (figure->block[i][j] == 1) {
        game_info->field[coordinates->x + i][coordinates->y + j] = 1;
      }
    }
  }
}

void delete_figure(GameInfo_t *game_info, Figure_t *figure,
                   Coordinates_t *coordinates) {
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (figure->block[i][j] == 1) {
        game_info->field[i + coordinates->x][j + coordinates->y] = 0;
      }
    }
  }
}

void coordinates_figures(int rand_figure, Coordinates_t *coordinates) {
  if (rand_figure == 1) {
    coordinates->x = 0;
    coordinates->y = 3;
  } else {
    coordinates->x = 0;
    coordinates->y = 4;
  }
}

Figure_t create_figure(int rand_figure) {
  Figure_t figure;
  switch (rand_figure) {
    case 0:
      figure = create_o_figure();
      break;
    case 1:
      figure = create_i_figure();
      break;
    case 2:
      figure = create_t_figure();
      break;
    case 3:
      figure = create_l_figure();
      break;
    case 4:
      figure = create_j_figure();
      break;
    case 5:
      figure = create_s_figure();
      break;
    case 6:
      figure = create_z_figure();
      break;
  }
  return figure;
}

int figure_vertical_collision(GameInfo_t *game_info, Figure_t *figure,
                              Coordinates_t *coordinates) {
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (figure->block[i][j] == 1) {
        if (!(coordinates->x + i < HEIGHT - 1 &&
              game_info->field[coordinates->x + i + 1][coordinates->y + j] ==
                  0)) {
          return 1;
        }
      }
    }
  }
  return 0;
}

void figure_move_down(GameInfo_t *game_info, Figure_t *figure,
                      Coordinates_t *coordinates) {
  while (figure_vertical_collision(game_info, figure, coordinates) == 0) {
    coordinates->x++;
  }
}

int check_game_over(GameInfo_t *game_info) {
  int result = 0;
  for (int i = 0; i < WIDTH; i++) {
    if (game_info->field[0][i] == 1) {
      result = 1;
    }
  }
  return result;
}

void update_hiscore(GameInfo_t *game_info) {
  if (game_info->score > game_info->high_score) {
    game_info->high_score = game_info->score;
    push_hiscore_on_file(game_info);
  }
}

void push_hiscore_on_file(GameInfo_t *game_info) {
  FILE *file = fopen("brick_game/tetris/high_score.txt", "w");
  if (file) {
    fprintf(file, "%d", game_info->high_score);
    fclose(file);
  }
}

void get_hiscore_from_file(GameInfo_t *game_info) {
  FILE *file = fopen("brick_game/tetris/high_score.txt", "r");
  if (file) {
    fscanf(file, "%d", &game_info->high_score);
    fclose(file);
  } else {
    game_info->high_score = 0;
  }
}