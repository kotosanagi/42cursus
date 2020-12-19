# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/12 19:03:33 by skotoyor          #+#    #+#              #
#    Updated: 2020/12/19 17:38:08 by skotoyor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRCFILE = ft_printf.c \
ft_printf_input_utils.c \
ft_printf_output_utils.c \
put_conv_c.c \
put_conv_di.c \
put_conv_p.c \
put_conv_percent.c \
put_conv_s.c \
put_conv_u_sx_lx.c
SRCDIR = srcs/
SRCS = $(addprefix $(SRCDIR), $(SRCFILE))
INCS = -I includes/ft_printf.h
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBDIR = ./libft/
LIBNAME = libft.a
LIB = ./libft/libft.a

all : $(NAME)

.c.o :
	$(CC) $(CFLAGS) $(INCS) -c $< -o $(<:.c=.o)

$(NAME): $(LIBNAME) $(OBJS)
	cp $(LIB) $(NAME)
	ar rc $(NAME) $(OBJS)

$(LIBNAME):
	make -C $(LIBDIR)

clean :
	rm -f $(OBJS)
	make clean -C $(LIBDIR)

fclean : clean
	rm -f $(NAME)
	make fclean -C $(LIBDIR)

re : fclean all

.PHONY : all clean fclean re