/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 11:09:06 by skotoyor          #+#    #+#             */
/*   Updated: 2020/12/19 17:41:16 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

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
	E_UNSIGNED,
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

typedef	struct			s_content
{
	int					flag[E_FLAG_NUM];
	int					width;
	int					prec;
	int					conv;
	int					num_int;
	unsigned int		num_uint;
	unsigned long long	num_ptr;
	int					num_digits;
	int					num_base;
}						t_content;

int						ft_printf(const char *format, ...);
int						put_conv_c(va_list *ap, t_content *content);
int						put_conv_s(va_list *ap, t_content *content);
int						put_conv_p(va_list *ap, t_content *content,
char *base_str);
int						put_conv_di(va_list *ap, t_content *content);
int						put_conv_u_sx_lx(va_list *ap, t_content *content,
char *base_str);
int						put_conv_percent(t_content *content);
int						is_flag(char c, t_content *content);
int						is_width(char c, t_content *content, va_list *ap);
int						is_prec(char c, t_content *content, va_list *ap);
char					*get_base_info(char *base_num_ptn, t_content *content);
int						get_digits(t_content *content);
int						put_char_count(char c);
int						put_notconv_count(char *str, int put_str_len);
int						putnbr_narr_uxxp(unsigned long long n,
char *n_arr, t_content *content);
int						put_space(t_content *content, int offset);
size_t					ft_strlen(const char *s);

#endif
