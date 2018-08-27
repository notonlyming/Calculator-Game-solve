calulator_game.exe:main.c game.c game_input.c game_output.c game_process.c
	gcc $^ -Wall -Wextra -Werror -lm -o $@