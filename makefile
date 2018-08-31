calulator_game:main.c game.c game_input.c game_output.c game_process.c
	clang $^ -Wall -Wextra -Werror -lm -o $@
game_test:game_test.c game.c game_input.c game_output.c game_process.c
	clang $^ -Wall -Wextra -Werror -lm -o $@
