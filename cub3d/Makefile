# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/13 13:41:32 by skotoyor          #+#    #+#              #
#    Updated: 2021/03/07 09:14:45 by skotoyor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# gcc -Wall -Wextra -Werror srcs/*.c libft/*.o gnl/*.o -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -I./includes -L./libraries -lXext -lX11 -lm -lz

NAME	=	cub3D
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
SRCS	=	srcs/*.c ############################ MUST BE CHANGED
OBJS	=	$(SRCS:%.c=%.o)

HEAD	=	./includes/cub3d.h
INCS	=	-I./includes
LINK	=	-L./libraries ##-L/usr/lib ????
LIBS	=	-lft -lgnl -lXext -lX11 -lm -lz


all:$(NAME)

$(NAME): $(OBJS)
	make -C libft
	cp libft/libft.a ./libraries/
	make -C gnl
	cp gnl/libgnl.a ./libraries/
	make -C mlx_linux
	cp mlx_linux/libmlx*.a ./libraries/
	$(CC) -o $(NAME) $(OBJS) $(LINK) $(INCS) $(LIBS)

clean:
	rm -f $(OBJS)		####################
	make clean -C libft
	make clean -C gnl
	make clean -C mlx_linux


fclean:clean
	rm -f $(NAME)
	make clean -C libft
	make clean -C gnl
	make clean -C mlx_linux
	rm -f libraries/*.a

re:fclean all

.PHONY: all clean fclean re
