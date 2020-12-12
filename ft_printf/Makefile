# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/12 19:03:33 by skotoyor          #+#    #+#              #
#    Updated: 2020/12/12 19:37:10 by skotoyor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCFILE = ft_printf.c \
		ft_printf_util.c

SRCDIR = srcs/

SRCS = $(addprefix $(SRCDIR), $(SRCFILE))



INCS = -I includes/ft_printf.h



OBJS = $(SRCS:.c=.o)

NAME = libftprintf.a

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