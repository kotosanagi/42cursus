/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 11:09:06 by skotoyor          #+#    #+#             */
/*   Updated: 2020/12/01 23:08:46 by skotoyor         ###   ########.fr       */
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
	int num_int;	//なぜ追加したのか、、、(もしかしたら出力の処理が25行に納らないから？)関数の引数も足りないから？
	int num_digits;
	int num_base;	//なぜ追加したのか、、、(もしかしたら出力の処理が25行に納らないから？)
}				t_content;

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
void	put_char_count(char c, int *printed_len);
void	put_notconv_count(char *str, int i, int *printed_len);
void	put_string_or_nbr(va_list *ap, t_content *content, int *printed_len);

int		is_flag(char c, t_content *content);
int		is_conversion(char c, t_content *content);
int		is_width(char c, t_content *content, va_list *ap);
int		is_prec(char c, t_content *content, va_list *ap);

void	ft_putnbr(int nb);
// 
size_t	ft_strlen(const char *s);

#endif