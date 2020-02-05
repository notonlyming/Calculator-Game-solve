calculator_game:src/*.c
	clang $^ -Wall -Wextra -Werror -lm -o $@ -Ofast
