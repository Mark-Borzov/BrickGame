GCC = gcc
GCC_FLAGS = -Wall -Wextra -Werror
FLAGS_COV = -lcheck -lgcov -fprofile-arcs --coverage
FLAGS_L = -lcheck -lm -lpthread -lrt -lsubunit -lncurses

all: install dist

tetris.a:
	$(GCC) $(GCC_FLAGS) -c brick_game/tetris/tetris.c brick_game/tetris/tetris.h gui/cli/tetris_interface.c 
	ar rcs tetris.a tetris.o tetris_interface.o
	ranlib tetris.a
	mv tetris.a brick_game/tetris
	rm -rf brick_game/tetris/tetris.h.gch
	rm -rf tetris_interface.o
	rm -rf tetris.o

clean:
	rm -rf brick_game/tetris/tetris.a
	rm -rf game
	rm -rf *.o
	rm -rf brick_game/tetris/tetris.h.gch
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf gcov_report.info
	rm -rf report
	rm -rf test

game:
	build_tetris/./game

test:
	build_tetris/./test

gcov_report: clean
	$(CC) brick_game/tetris/tetris_tests.c brick_game/tetris/tetris.c gui/cli/tetris_interface.c $(FLAGS_L) -o test $(FLAGS_COV)
	./test
	lcov -t "gcov_report" -o gcov_report.info -c -d ./
	genhtml -o report gcov_report.info;
	open report/index.html
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf gcov_report.info
	rm -rf test

install: clean tetris.a
	$(CC) $(GCC_FLAGS) brick_game/tetris/tetris_game.c brick_game/tetris/tetris.a $(FLAGS_L) -o game
	$(CC) $(GCC_FLAGS) brick_game/tetris/tetris_tests.c brick_game/tetris/tetris.a $(FLAGS_L) -o test
	mkdir -p ./build_tetris
	mv game ./build_tetris
	mv test ./build_tetris

uninstall: clean
	rm -rf build_tetris
	rm -rf dist_tetris
	rm -rf archive_dist.tar

dist:
	mkdir -p ./dist_tetris
	tar -czvf archive_dist.tar build_tetris ./brick_game/tetris ./gui/cli
	mv archive_dist.tar ./dist_tetris

dvi:
	open brick_game/tetris/documentation.md

check_clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n brick_game/tetris/*.c
	clang-format -n brick_game/tetris/*.h
	clang-format -n gui/cli/*.c
	rm -rf .clang-format

done_clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -i brick_game/tetris/*.c
	clang-format -i brick_game/tetris/*.h
	clang-format -i gui/cli/*.c
	rm -rf .clang-format