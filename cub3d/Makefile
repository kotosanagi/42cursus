# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/13 13:41:32 by skotoyor          #+#    #+#              #
#    Updated: 2021/03/07 16:56:05 by skotoyor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
SRCS	=	srcs/main.c \
srcs/analyze_mapdata.c \
srcs/calc_func.c \
srcs/draw_func.c \
srcs/error_func2.c \
srcs/error_func.c \
srcs/escape_func.c \
srcs/get_floor_ceiling_color.c \
srcs/get_mapfile_info.c \
srcs/get_mapfile_info_util.c \
srcs/get_mappart_data.c \
srcs/get_sprite_info.c \
srcs/get_window_size.c \
srcs/init_func.c \
srcs/is_closed_map.c \
srcs/is_correct_arg.c \
srcs/key_press_release.c \
srcs/key_update.c \
srcs/load_texture.c \
srcs/set_buf.c \
srcs/sort_sprites.c \
srcs/store_sprite.c \
srcs/store_wall2.c \
srcs/store_wall.c \
srcs/create_bmp.c

OBJS	=	$(SRCS:%.c=%.o)
HEAD	=	./includes/cub3d.h
INCS	=	-I./includes
LINK	=	-L./libraries -L/usr/lib
LIBS	=	-lmlx_linux -lft -lgnl -lXext -lX11 -lm -lz

all:$(NAME)

$(NAME):$(OBJS)
	make -C libft
	cp libft/libft.a ./libraries/
	make -C gnl
	cp gnl/libgnl.a ./libraries/
	make -C mlx_linux
	cp mlx_linux/libmlx*.a ./libraries/
	$(CC) -o $(NAME) $(OBJS) $(LINK) $(INCS) $(LIBS)

clean:
	rm -f $(OBJS)
	make clean -C libft
	make clean -C gnl
	make clean -C mlx_linux

fclean:clean
	rm -f $(NAME)
	rm -f *.bmp
	make clean -C libft
	make clean -C gnl
	make clean -C mlx_linux
	rm -f libraries/*.a

re:fclean all

.PHONY: all clean fclean re
