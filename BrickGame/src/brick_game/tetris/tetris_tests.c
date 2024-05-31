#include <check.h>

#include "tetris.h"

START_TEST(tetris_test_1) {
  GameInfo_t game_info;
  Figure_t figure;
  Coordinates_t figure_coordinates;
  Windos_t windows;
  int next_figure;
  WINDOW *pause_window;
  int rand_figure = 0;
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
    int end_game = 1;
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
END_TEST

START_TEST(tetris_test_2) {
  GameInfo_t game_info;
  Figure_t figure;
  Coordinates_t figure_coordinates;
  Windos_t windows;
  int next_figure;
  int rand_figure = 1;
  int game_iteration;
  int game_paused;
  int game_start;
  initialize_game(&game_info, &figure, &figure_coordinates, &windows,
                  &next_figure, &game_iteration, &game_paused, &game_start,
                  &rand_figure);
}
END_TEST

START_TEST(tetris_test_3) {
  GameInfo_t game_info;
  Figure_t figure;
  Coordinates_t figure_coordinates;
  Windos_t windows;
  int next_figure;
  int rand_figure = 2;
  int game_iteration;
  int game_paused;
  int game_start;
  initialize_game(&game_info, &figure, &figure_coordinates, &windows,
                  &next_figure, &game_iteration, &game_paused, &game_start,
                  &rand_figure);
}
END_TEST

START_TEST(tetris_test_4) {
  GameInfo_t game_info;
  Figure_t figure;
  Coordinates_t figure_coordinates;
  Windos_t windows;
  int next_figure;
  int rand_figure = 3;
  int game_iteration;
  int game_paused;
  int game_start;
  initialize_game(&game_info, &figure, &figure_coordinates, &windows,
                  &next_figure, &game_iteration, &game_paused, &game_start,
                  &rand_figure);
}
END_TEST

START_TEST(tetris_test_5) {
  GameInfo_t game_info;
  Figure_t figure;
  Coordinates_t figure_coordinates;
  Windos_t windows;
  int next_figure;
  int rand_figure = 4;
  int game_iteration;
  int game_paused;
  int game_start;
  initialize_game(&game_info, &figure, &figure_coordinates, &windows,
                  &next_figure, &game_iteration, &game_paused, &game_start,
                  &rand_figure);
}
END_TEST

START_TEST(tetris_test_6) {
  GameInfo_t game_info;
  Figure_t figure;
  Coordinates_t figure_coordinates;
  Windos_t windows;
  int next_figure;
  int rand_figure = 5;
  int game_iteration;
  int game_paused;
  int game_start;
  initialize_game(&game_info, &figure, &figure_coordinates, &windows,
                  &next_figure, &game_iteration, &game_paused, &game_start,
                  &rand_figure);
}
END_TEST

START_TEST(tetris_test_7) {
  GameInfo_t game_info;
  Figure_t figure;
  Coordinates_t figure_coordinates;
  Windos_t windows;
  int next_figure;
  int rand_figure = 6;
  int game_iteration;
  int game_paused;
  int game_start;
  initialize_game(&game_info, &figure, &figure_coordinates, &windows,
                  &next_figure, &game_iteration, &game_paused, &game_start,
                  &rand_figure);
}
END_TEST

START_TEST(tetris_test_8) { print_logo_game(); }
END_TEST

START_TEST(tetris_test_9) { print_game_over(); }
END_TEST

START_TEST(tetris_test_10) {
  WINDOW *pause_window;
  window_game_pause(&pause_window);
}
END_TEST

START_TEST(tetris_test_11) {
  Figure_t figure;
  rotate_i_figure_left(&figure);
}
END_TEST

START_TEST(tetris_test_12) {
  Figure_t figure;
  rotate_i_figure_up(&figure);
}
END_TEST

START_TEST(tetris_test_13) {
  GameInfo_t game_info;
  int count_line = 1;
  count_score(&game_info, count_line);
}
END_TEST

START_TEST(tetris_test_14) {
  GameInfo_t game_info;
  int count_line = 2;
  count_score(&game_info, count_line);
}
END_TEST

START_TEST(tetris_test_15) {
  GameInfo_t game_info;
  int count_line = 3;
  count_score(&game_info, count_line);
}
END_TEST

START_TEST(tetris_test_16) {
  GameInfo_t game_info;
  int count_line = 4;
  count_score(&game_info, count_line);
}
END_TEST

START_TEST(tetris_test_17) {
  GameInfo_t game_info;
  game_info.score = 700;
  int speed_game = 500000;
  update_level(&game_info, &speed_game);
}
END_TEST

START_TEST(tetris_test_18) {
  UserAction_t action;
  int move = KEY_LEFT;
  create_action(&action, move);
}
END_TEST

START_TEST(tetris_test_19) {
  UserAction_t action;
  int move = KEY_RIGHT;
  create_action(&action, move);
}
END_TEST

START_TEST(tetris_test_20) {
  UserAction_t action;
  int move = KEY_DOWN;
  create_action(&action, move);
}
END_TEST

START_TEST(tetris_test_21) {
  UserAction_t action;
  int move = KEY_UP;
  create_action(&action, move);
}
END_TEST

START_TEST(tetris_test_22) {
  UserAction_t action;
  int move = 'q';
  create_action(&action, move);
}
END_TEST

START_TEST(tetris_test_23) {
  UserAction_t action;
  int move = 'w';
  create_action(&action, move);
}
END_TEST

START_TEST(tetris_test_24) {
  UserAction_t action;
  int move = 'e';
  create_action(&action, move);
}
END_TEST

START_TEST(tetris_test_25) {
  GameInfo_t game_info;
  game_info.score = 1300;
  int speed_game = 500000;
  update_level(&game_info, &speed_game);
}
END_TEST

START_TEST(tetris_test_26) {
  GameInfo_t game_info;
  game_info.score = 1900;
  int speed_game = 500000;
  update_level(&game_info, &speed_game);
}
END_TEST

START_TEST(tetris_test_27) {
  GameInfo_t game_info;
  game_info.score = 2500;
  int speed_game = 500000;
  update_level(&game_info, &speed_game);
}
END_TEST

START_TEST(tetris_test_28) {
  GameInfo_t game_info;
  game_info.score = 3100;
  int speed_game = 500000;
  update_level(&game_info, &speed_game);
}
END_TEST

START_TEST(tetris_test_29) {
  GameInfo_t game_info;
  game_info.score = 3700;
  int speed_game = 500000;
  update_level(&game_info, &speed_game);
}
END_TEST

START_TEST(tetris_test_30) {
  GameInfo_t game_info;
  game_info.score = 4300;
  int speed_game = 500000;
  update_level(&game_info, &speed_game);
}
END_TEST

START_TEST(tetris_test_31) {
  GameInfo_t game_info;
  game_info.score = 4900;
  int speed_game = 500000;
  update_level(&game_info, &speed_game);
}
END_TEST

START_TEST(tetris_test_32) {
  GameInfo_t game_info;
  game_info.score = 5400;
  int speed_game = 500000;
  update_level(&game_info, &speed_game);
}
END_TEST

START_TEST(tetris_test_33) {
  GameInfo_t game_info;
  game_info.field = (int **)malloc(HEIGHT * sizeof(int *));
  for (int i = 0; i < HEIGHT; i++) {
    game_info.field[i] = (int *)malloc(WIDTH * sizeof(int));
  }
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      game_info.field[i][j] = 0;
    }
  }
  destroy_line(&game_info);
  free_field(&game_info);
}
END_TEST

START_TEST(tetris_test_34) {
  GameInfo_t game_info;
  game_info.field = (int **)malloc(HEIGHT * sizeof(int *));
  for (int i = 0; i < HEIGHT; i++) {
    game_info.field[i] = (int *)malloc(WIDTH * sizeof(int));
  }
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      game_info.field[i][j] = 1;
    }
  }
  destroy_line(&game_info);
  free_field(&game_info);
}
END_TEST

START_TEST(tetris_test_35) {
  GameInfo_t game_info;
  Coordinates_t coordinates;
  can_rotate_figure(&game_info, &coordinates);
}
END_TEST

START_TEST(tetris_test_36) {
  UserAction_t action;
  action = Left;
  int shift_horizontal = 0;
  int shift_vertical = 0;
  int rotate = 0;
  int end_game = 0;
  int game_paused = 0;
  int game_start = 0;
  userInput(action, &shift_horizontal, &shift_vertical, &rotate, &end_game,
            &game_paused, &game_start);
}
END_TEST

START_TEST(tetris_test_37) {
  UserAction_t action;
  action = Right;
  int shift_horizontal = 0;
  int shift_vertical = 0;
  int rotate = 0;
  int end_game = 0;
  int game_paused = 0;
  int game_start = 0;
  userInput(action, &shift_horizontal, &shift_vertical, &rotate, &end_game,
            &game_paused, &game_start);
}
END_TEST

START_TEST(tetris_test_38) {
  UserAction_t action;
  action = Down;
  int shift_horizontal = 0;
  int shift_vertical = 0;
  int rotate = 0;
  int end_game = 0;
  int game_paused = 0;
  int game_start = 0;
  userInput(action, &shift_horizontal, &shift_vertical, &rotate, &end_game,
            &game_paused, &game_start);
}
END_TEST

START_TEST(tetris_test_39) {
  UserAction_t action;
  action = Up;
  int shift_horizontal = 0;
  int shift_vertical = 0;
  int rotate = 0;
  int end_game = 0;
  int game_paused = 0;
  int game_start = 0;
  userInput(action, &shift_horizontal, &shift_vertical, &rotate, &end_game,
            &game_paused, &game_start);
}
END_TEST

START_TEST(tetris_test_40) {
  UserAction_t action;
  action = Terminate;
  int shift_horizontal = 0;
  int shift_vertical = 0;
  int rotate = 0;
  int end_game = 0;
  int game_paused = 0;
  int game_start = 0;
  userInput(action, &shift_horizontal, &shift_vertical, &rotate, &end_game,
            &game_paused, &game_start);
}
END_TEST

START_TEST(tetris_test_41) {
  UserAction_t action;
  action = Pause;
  int shift_horizontal = 0;
  int shift_vertical = 0;
  int rotate = 0;
  int end_game = 0;
  int game_paused = 0;
  int game_start = 0;
  userInput(action, &shift_horizontal, &shift_vertical, &rotate, &end_game,
            &game_paused, &game_start);
}
END_TEST

START_TEST(tetris_test_42) {
  UserAction_t action;
  action = Start;
  int shift_horizontal = 0;
  int shift_vertical = 0;
  int rotate = 0;
  int end_game = 0;
  int game_paused = 0;
  int game_start = 0;
  userInput(action, &shift_horizontal, &shift_vertical, &rotate, &end_game,
            &game_paused, &game_start);
}
END_TEST

START_TEST(tetris_test_43) {
  GameInfo_t game_info;
  Coordinates_t coordinates;
  Figure_t figure;
  int rand_figure = 0;
  rotate_figure(&game_info, &coordinates, &figure, rand_figure);
}
END_TEST

START_TEST(tetris_test_44) {
  GameInfo_t game_info;
  Coordinates_t coordinates;
  Figure_t figure;
  int rand_figure = 1;
  rotate_figure(&game_info, &coordinates, &figure, rand_figure);
}
END_TEST

START_TEST(tetris_test_45) {
  GameInfo_t game_info;
  Coordinates_t coordinates;
  Figure_t figure;
  figure.block[1][1] = 0;
  int rand_figure = 1;
  rotate_figure(&game_info, &coordinates, &figure, rand_figure);
}
END_TEST

START_TEST(tetris_test_46) {
  GameInfo_t game_info;
  game_info.high_score = 0;
  push_hiscore_on_file(&game_info);
}
END_TEST

Suite *tetris_tests_suite() {
  Suite *selection;
  TCase *test_core;
  selection = suite_create("tetris_tests");
  test_core = tcase_create("core");
  tcase_add_test(test_core, tetris_test_1);
  tcase_add_test(test_core, tetris_test_2);
  tcase_add_test(test_core, tetris_test_3);
  tcase_add_test(test_core, tetris_test_4);
  tcase_add_test(test_core, tetris_test_5);
  tcase_add_test(test_core, tetris_test_6);
  tcase_add_test(test_core, tetris_test_7);
  tcase_add_test(test_core, tetris_test_8);
  tcase_add_test(test_core, tetris_test_9);
  tcase_add_test(test_core, tetris_test_10);
  tcase_add_test(test_core, tetris_test_11);
  tcase_add_test(test_core, tetris_test_12);
  tcase_add_test(test_core, tetris_test_13);
  tcase_add_test(test_core, tetris_test_14);
  tcase_add_test(test_core, tetris_test_15);
  tcase_add_test(test_core, tetris_test_16);
  tcase_add_test(test_core, tetris_test_17);
  tcase_add_test(test_core, tetris_test_18);
  tcase_add_test(test_core, tetris_test_19);
  tcase_add_test(test_core, tetris_test_20);
  tcase_add_test(test_core, tetris_test_21);
  tcase_add_test(test_core, tetris_test_22);
  tcase_add_test(test_core, tetris_test_23);
  tcase_add_test(test_core, tetris_test_24);
  tcase_add_test(test_core, tetris_test_25);
  tcase_add_test(test_core, tetris_test_26);
  tcase_add_test(test_core, tetris_test_27);
  tcase_add_test(test_core, tetris_test_28);
  tcase_add_test(test_core, tetris_test_29);
  tcase_add_test(test_core, tetris_test_30);
  tcase_add_test(test_core, tetris_test_31);
  tcase_add_test(test_core, tetris_test_32);
  tcase_add_test(test_core, tetris_test_33);
  tcase_add_test(test_core, tetris_test_34);
  tcase_add_test(test_core, tetris_test_35);
  tcase_add_test(test_core, tetris_test_36);
  tcase_add_test(test_core, tetris_test_37);
  tcase_add_test(test_core, tetris_test_38);
  tcase_add_test(test_core, tetris_test_39);
  tcase_add_test(test_core, tetris_test_40);
  tcase_add_test(test_core, tetris_test_41);
  tcase_add_test(test_core, tetris_test_42);
  tcase_add_test(test_core, tetris_test_43);
  tcase_add_test(test_core, tetris_test_44);
  tcase_add_test(test_core, tetris_test_45);
  tcase_add_test(test_core, tetris_test_46);
  suite_add_tcase(selection, test_core);
  return selection;
}

void case_tests(Suite *selection, int *fail) {
  SRunner *runner = srunner_create(selection);
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  *fail = srunner_ntests_failed(runner);
  srunner_free(runner);
}

int main() {
  int fail = 0;
  case_tests(tetris_tests_suite(), &fail);
  return 0;
}