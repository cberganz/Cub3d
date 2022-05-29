# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: charles <charles@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 14:42:18 by cberganz          #+#    #+#              #
#    Updated: 2022/05/29 03:08:36 by charles          ###   ########.fr        #
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
					overlay.c		\
					raycast.c		\
					mouse.c			\
					game.c			\
					initialize.c	\
					utils.c			\
					parsing.c		\
					exit.c

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
