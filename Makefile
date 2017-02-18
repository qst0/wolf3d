# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/19 05:40:13 by myoung            #+#    #+#              #
#    Updated: 2017/01/28 01:40:35 by myoung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3

MAIN = main.c

FILES +=	hooks.c		# hooks, all kinds
FILES +=	init.c		# view init functions
FILES +=	keys.c		# toggle keys
FILES +=	time.c		# Keeping track of the fps and cur_sec
FILES +=	texture.c	# Texture Generation
FILES +=	draw.c		# point_to_img -  draw filled square
FILES +=	image.c		# create / use image
FILES +=	sort.c		# sort funcs needed for sprites
FILES +=	move.c		# player movement and turning
FILES +=	minimap.c	# minimap and player minimap token stuff
FILES +=	sprites.c	# sprite functions and casting
FILES +=	raycast.c	# The raycasting functions
FILES +=	floorcast.c	# The raycasting functions
FILES +=	loop_hook.c	# THE LOOP HOOK ITSELF
FILES +=	parse.c			# For parsing the map
FILES +=	ft_strsplit.c	# For parsing

SRCS = $(addprefix srcs/, $(FILES))
OBJS = $(addprefix objs/, $(FILES:.c=.o))

FRAMEWORKS = -framework OpenGL -framework AppKit
INC = -I .

INC_MINILIBX = -I minilibx
LINK_MINILIBX = -L minilibx -lmlx
MINILIBX = $(INC_MINILIBX) $(LINK_MINILIBX)

all: $(NAME)

minilibx/libmlx.a:
	@echo "Making minilibx"
	@make -C minilibx re

$(NAME): minilibx/libmlx.a $(OBJS)
	$(CC) $(CFLAGS) $(MAIN) $(OBJS) \
		$(MINILIBX) $(INC) $(FRAMEWORKS) -o $(NAME)
	@echo "Creating ./$(NAME)"

objs:
	@mkdir objs

objs/%.o: srcs/%.c | objs
	@echo "Building $@"
	@$(CC) $(CFLAGS) $(INC_MINILIBX) $(INC) -c $< -o $@

clean:
	@rm -rf objs
	@echo "clean successful"

tclean:
	make -C minilibx clean
	make fclean

fclean: clean
	@echo "Removing ./$(NAME)"
	rm -f $(NAME)

re: fclean all
