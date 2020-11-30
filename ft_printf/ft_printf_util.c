/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 19:08:07 by skotoyor          #+#    #+#             */
/*   Updated: 2020/11/30 15:45:55 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_char_count(char c, int *printed_len)
{
	write(1, &c, 1);
	*printed_len += 1;
}

void	put_notconv_count(char *str, int i, int *printed_len)
{
	write(1, str, i);
	*printed_len += i;
}

int		is_flag(char c, t_content *content)
{
	if (c == '-')
	{
		content->flag[E_MINUS] = true;
		return (1);
	}
	if (content->width < 0 && content->prec < 0 && c == '0')
	{
		content->flag[E_ZERO] = true;
		return (1);
	}
	return (0);
}

int		is_width(char c, t_content *content, va_list *ap)
{
	int ret;
	int tmp;

	ret = 1;
	if (content->prec < 0 && c == '*')//'*'がきたら対応したつもり
	{
		tmp = va_arg(*ap, int);
		content->width = (tmp < 0) ? -tmp : tmp;
		if (tmp < 0)
			content->flag[E_MINUS] = true;
	}
	else if (content->width < 0 && (content->prec < 0) && ('1' <= c && c <= '9'))//widthがまだデフォかつ、precがデフォかつ、0以外の数字
		content->width = c - '0';
	else if ((content->prec < 0) && ('0' <= c && c <= '9'))//precがデフォかつ、数字
		content->width = ((content->width * 10) + (c - '0'));
	else
		ret = 0;
	return (ret);
}

int		is_prec(char c, t_content *content, va_list *ap)
{
	int ret;
	int tmp;

	ret = 1;
	//とりあえず.がきたら、precは0にして良い。-とかはあとで考える。
	if (content->prec < 0 && c == '.')
		content->prec = 0;
	else if (content->prec == 0 && c == '*')
	{
		tmp = va_arg(*ap, int);
		content->prec = (tmp < 0) ? -1 : tmp;// tmpが負なら-1のまま
	}
	else if (content->prec >= 0 && '0' <= c && c <= '9')
		content->prec = (content->prec * 10) + (c - '0');
	else
		ret = 0;
	return (ret);
}

int		is_conversion(char c, t_content *content)
{
	if (c == 'c')
		content->conv = E_CHAR;
	else if (c == 's')
		content->conv = E_STRING;
	else if (c == 'p')
		content->conv = E_POINTER;
	else if (c == 'd')
		content->conv = E_DECIMAL;
	else if (c == 'i')
		content->conv = E_INTEGER;
	else if (c == 'u')
		content->conv = E_UNSIGNED;
	else if (c == 'x')
		content->conv = E_XDECIMAL_SMALL;
	else if (c == 'X')
		content->conv = E_XDECIMAL_LARGE;
	else if (c == '%')
		content->conv = E_PERCENT;
	return (content->conv);
}

void	init_content(t_content *content)
{
	content->flag[E_MINUS] = false;
	content->flag[E_ZERO] = false;
	content->width = -1;
	content->prec = -1;
	content->conv = E_NOT_CONV;
}

// void	put_string_or_nbr(va_list *ap, t_content *content, int *printed_len)
// {
// 	// if (content->conv == E_CHAR)

// 	// if (content->conv == E_STRING)

// 	// if (content->conv == E_POINTER)

// 	// if ((content->conv == E_DECIMAL) || (content->conv == E_INTEGER))

// 	// if (content->conv == E_UNSIGNED)

// 	// if (content->conv == E_XDECIMAL_SMALL)

// 	// if (content->conv == E_XDECIMAL_LARGE)

// 	// if (content->conv == E_PERCENT)
// 	// 	put_conv_
// }