#include "../../brick_game/tetris/tetris.h"

void init_windows(GameInfo_t *game_info, Windos_t *window,
                  int next_num_figure) {
  // Окно print_game_field
  window->game_window = newwin(22, 12, 0, 0);
  box(window->game_window, 0, 0);
  print_game_field(game_info, window);
  // Окно GAME INFORMATION:
  window->information_window = newwin(3, 21, 0, 12);
  box(window->information_window, 0, 0);
  mvwprintw(window->information_window, 1, 2, "GAME INFORMATION:");
  wrefresh(window->information_window);
  // Окно printf_hiscore
  window->hi_score_window = newwin(3, 21, 3, 12);
  box(window->hi_score_window, 0, 0);
  print_hiscore(game_info, window);
  // Окно print_score
  window->score_window = newwin(3, 21, 6, 12);
  box(window->score_window, 0, 0);
  print_score(game_info, window);
  // Окно print_level
  window->level_window = newwin(3, 21, 9, 12);
  box(window->level_window, 0, 0);
  print_level(game_info, window);
  // Окно print_next_figure
  window->next_figure = newwin(10, 21, 12, 12);
  box(window->next_figure, 0, 0);
  print_next_figure(next_num_figure, window);
}

void refresh_windows(GameInfo_t *game_info, Windos_t *window,
                     int next_num_figure) {
  print_game_field(game_info, window);
  print_hiscore(game_info, window);
  print_score(game_info, window);
  print_level(game_info, window);
  print_next_figure(next_num_figure, window);
}

void print_level(GameInfo_t *game_info, Windos_t *window) {
  mvwprintw(window->level_window, 1, 2, "LEVEL: %d", game_info->level);
  wrefresh(window->level_window);
}

void print_score(GameInfo_t *game_info, Windos_t *window) {
  mvwprintw(window->score_window, 1, 2, "SCORE: %d", game_info->score);
  wrefresh(window->score_window);
}

void print_hiscore(GameInfo_t *game_info, Windos_t *window) {
  mvwprintw(window->hi_score_window, 1, 2, "HISCORE: %d",
            game_info->high_score);
  wrefresh(window->hi_score_window);
}

void print_game_field(GameInfo_t *game_info, Windos_t *window) {
  for (int i = 0; i < HEIGHT; i++) {
    wmove(window->game_window, i + 1, 1);
    for (int j = 0; j < WIDTH; j++) {
      if (game_info->field[i][j] == 0) {
        wprintw(window->game_window, "%c", '.');
      } else {
        wprintw(window->game_window, "%c", '#');
      }
    }
  }
  wrefresh(window->game_window);
}

void print_next_figure(int next_num_figure, Windos_t *window) {
  mvwprintw(window->next_figure, 1, 2, "NEXT FIGURE:");
  Figure_t figure = create_figure(next_num_figure);
  for (int i = 0; i < FIGURE_SIZE; i++) {
    wmove(window->next_figure, i + 3, 2);
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (figure.block[i][j] == 0) {
        wprintw(window->next_figure, "%c", ' ');
      } else {
        wprintw(window->next_figure, "%c", '#');
      }
    }
  }
  wrefresh(window->next_figure);
}

void delete_windows(Windos_t *window) {
  delwin(window->game_window);
  delwin(window->information_window);
  delwin(window->hi_score_window);
  delwin(window->score_window);
  delwin(window->level_window);
  delwin(window->next_figure);
}

void window_game_pause(WINDOW **pause_window) {
  *pause_window = newwin(3, 10, 8, 1);
  box(*pause_window, 0, 0);
  mvwprintw(*pause_window, 1, 2, "PAUSE:");
  wrefresh(*pause_window);
}

void delete_window_game_pause(WINDOW **pause_window) { delwin(*pause_window); }

void print_logo_game() {
  mvprintw(0, 1, "  ______         __             _         ");
  mvprintw(1, 1, " /_  __/  ___   / /_   _____   (_)   _____");
  mvprintw(2, 1, "  / /    / _ \\ / __/  / ___/  / /   / ___/");
  mvprintw(3, 1, " / /    /  __// /_   / /     / /   (__  ) ");
  mvprintw(4, 1, "/_/     \\___/ \\__/  /_/     /_/   /____/  ");
  mvprintw(5, 1, "   ____ _  ____ _   ____ ___   ___ ");
  mvprintw(6, 1, "  / __ `/ / __ `/  / __ `__ \\ / _ \\");
  mvprintw(7, 1, " / /_/ / / /_/ /  / / / / / //  __/");
  mvprintw(8, 1, " \\__, /  \\__,_/  /_/ /_/ /_/ \\___/ ");
  mvprintw(9, 1, "/____/                             ");
}

void print_game_over() {
  printf("   ______\n");
  printf("  / ____/___ _____ ___  ___\n");
  printf(" / / __/ __ `/ __ `__ \\/ _ \\\n");
  printf("/ /_/ / /_/ / / / / / /  __/\n");
  printf("\\____/\\__,_/_/ /_/ /_/\\___/\n");
  printf("   ___\n");
  printf("  / __ \\_   _____  _____\n");
  printf(" / / / / | / / _ \\/ ___/\n");
  printf("/ /_/ /| |/ /  __/ /\n");
  printf("\\____/ |___/\\___/_/\n\n");
}