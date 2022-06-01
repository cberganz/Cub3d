# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 14:42:18 by cberganz          #+#    #+#              #
#    Updated: 2022/05/30 18:53:56 by rbicanic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= Cub3d
NAME_BONUS		= Cub3d_bonus

INCLUDE			= include/

HEADER			= ${INCLUDE}cub3d.h

CC				= clang

CFLAGS			= -Wall -Wextra -Werror -g

SRC_NAME		=	main.c			\
					minimap.c		\
					raycast.c		\
					mouse.c			\
					game.c			\
					initialize.c	\
					utils.c			\
					exit.c			\
					parsing/parsing_file_to_strs.c		\
					parsing/parsing_file_get_textures.c	\
					parsing/parsing_get_map.c			\
					parsing/check_path.c				\
					parsing/check_map_error.c			\
					parsing/check_instructions_error.c	\
					parsing/parsing_images.c			\
					parsing/global_parsing.c			\
					utils/utils_exit.c					\
					utils/utils_str_to_int.c


SRC_DIR			= src/
SRC				= ${addprefix ${SRC_DIR}, ${SRC_NAME}}

OBJ_DIR			= objs/
OBJ_DIRS		= ${sort ${dir ${OBJ}}}
OBJ_NAME		= ${SRC_NAME:.c=.o}
OBJ				= ${addprefix ${OBJ_DIR}, ${OBJ_NAME}}

all: ${NAME}

$(NAME): $(OBJ)
	@make -sC ./libft/
	@make -sC ./mlx-linux/
	$(CC) $(CFLAGS) -L./libft ${OBJ} -lft -Lmlx-linux -lmlx_Linux -L/usr/lib -Ilibmlx_linux -lXext -lX11 -lm -lz -o $(NAME)

bonus: $(NAME_BONUS)

${OBJ_DIRS}:
	mkdir -p $@

${OBJ}: | ${OBJ_DIRS}

${OBJ_DIR}%.o: ${SRC_DIR}%.c ${HEADER}
	${CC} ${CFLAGS} -I${INCLUDE} -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	@make clean -sC ./libft/
	@make clean -sC ./mlx-linux/
	rm -rf ${OBJ_DIR}

fclean: clean
	@make fclean -sC ./libft/
	rm -f ${NAME}
	rm -f ${NAME_BONUS}

re: fclean all

.PHONY : all clean fclean re
