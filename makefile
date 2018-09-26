source := $(shell ls src/*.c)
calulator_game:$(source)
	clang $^ -Wall -Wextra -Werror -lm -o $@