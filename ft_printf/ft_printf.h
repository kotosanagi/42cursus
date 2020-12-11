/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 11:09:06 by skotoyor          #+#    #+#             */
/*   Updated: 2020/12/12 08:40:34 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>/////////
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

typedef	enum	e_conversion
{
	E_NOT_CONV,
	E_CHAR,
	E_STRING,
	E_POINTER,
	E_DECIMAL,
	E_INTEGER,
	E_UNSIGNED,//////
	E_XDECIMAL_SMALL,
	E_XDECIMAL_LARGE,
	E_PERCENT
}				t_conversion;

typedef	enum	e_flag
{
	E_MINUS,
	E_ZERO,
	E_FLAG_NUM
}				t_flag;

typedef	struct	s_content
{
	int	flag[E_FLAG_NUM];
	int	width;
	int	prec;
	int	conv;
	int num_int;
	unsigned int num_uint;////////
	int num_digits;
	int num_base;
}				t_content;

int		ft_printf(const char *format, ...);
// void	is_char(t_content *content);
// void	is_string(t_content *content);
// void	is_pointer(t_content *content);
// void	is_decimal(t_content *content);
// void	is_integer(t_content *content);
// void	is_unsigned(t_content *content);
// void	is_x_small(t_content *content);
// void	is_x_large(t_content *content);
// void	is_percent(t_content *content);
void	init_content(t_content *content);
// void	put_char_count(char c, int *printed_len);
int		put_char_count(char c);
int		put_notconv_count(char *str, int put_str_len);
// void	put_notconv_count(char *str, int put_str_len, int *printed_len);
int		put_string_or_nbr(va_list *ap, t_content *content);
// void	put_string_or_nbr(va_list *ap, t_content *content, int *printed_len);

int		is_flag(char c, t_content *content);
int		is_conversion(char c, t_content *content);
int		is_width(char c, t_content *content, va_list *ap);
int		is_prec(char c, t_content *content, va_list *ap);
void	ft_putnbr_fd(int n, int fd);
// 
size_t	ft_strlen(const char *s);

#endif
