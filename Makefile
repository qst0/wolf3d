#Makefile by Mason

NAME = wolf3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3

MAIN = main.c guts.c hooks.c keys.c time.c utils.c texture.c

FRAMEWORKS = -framework OpenGL -framework AppKit
INC = -I .

INC_MINILIBX = -I minilibx
LINK_MINILIBX = -L minilibx -lmlx
MINILIBX = $(INC_MINILIBX) $(LINK_MINILIBX)

all: $(NAME)

minilibx/libmlx.a:
	@echo "Making minilibx"
	@make -C minilibx re

$(NAME): minilibx/libmlx.a
	$(CC) $(CFLAGS) $(MAIN) $(MINILIBX) $(INC) $(FRAMEWORKS) -o $(NAME)
	@echo "Creating ./$(NAME)"

clean:
	@rm -rf build
	@echo "clean successful"

tclean:
	make -C minilibx clean
	make fclean

fclean: clean
	@echo "Removing ./$(NAME)"
	rm -f $(NAME)

re: fclean all
