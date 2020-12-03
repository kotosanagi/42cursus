NAME = ft_mini_ls
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_mini_ls.c \
ft_mini_ls_utils.c

OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
