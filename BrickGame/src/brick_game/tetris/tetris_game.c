#include "tetris.h"

int main() {
  // valgrind --tool=memcheck --leak-check=yes  ./game
  initscr();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  curs_set(0);
  srand(time(NULL));
  clear();
  refresh();
  tetris();
  endwin();
  print_game_over();
  return 0;
}