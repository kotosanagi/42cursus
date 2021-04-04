/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:10:08 by skotoyor          #+#    #+#             */
/*   Updated: 2020/12/19 17:46:02 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	is_conversion(char c, t_content *content)
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

static void	init_content(t_content *content)
{
	content->flag[E_MINUS] = false;
	content->flag[E_ZERO] = false;
	content->width = -1;
	content->prec = -1;
	content->conv = E_NOT_CONV;
	content->num_int = 0;
	content->num_uint = 0;
	content->num_ptr = 0;
	content->num_digits = 0;
	content->num_base = 0;
}

static int	put_string_or_nbr(va_list *ap, t_content *content)
{
	int put_len;

	put_len = 0;
	if (content->conv == E_CHAR)
		put_len += put_conv_c(ap, content);
	else if (content->conv == E_STRING)
		put_len += put_conv_s(ap, content);
	else if (content->conv == E_POINTER)
		put_len += put_conv_p(ap, content, "0123456789abcdef");
	else if ((content->conv == E_DECIMAL) || (content->conv == E_INTEGER))
		put_len += put_conv_di(ap, content);
	else if (content->conv == E_UNSIGNED)
		put_len += put_conv_u_sx_lx(ap, content, "0123456789");
	else if (content->conv == E_XDECIMAL_SMALL)
		put_len += put_conv_u_sx_lx(ap, content, "0123456789abcdef");
	else if (content->conv == E_XDECIMAL_LARGE)
		put_len += put_conv_u_sx_lx(ap, content, "0123456789ABCDEF");
	else if (content->conv == E_PERCENT)
		put_len += put_conv_percent(content);
	return (put_len);
}

static int	process_percent(va_list *ap, char *str, int *printed_len)
{
	int			str_i;
	t_content	content;

	init_content(&content);
	str_i = 1;
	while (str[str_i])
	{
		if (is_flag(str[str_i], &content))
			;
		else if (is_width(str[str_i], &content, ap))
			;
		else if (is_prec(str[str_i], &content, ap))
			;
		else if (is_conversion(str[str_i++], &content))
			break ;
		else
			break ;
		str_i++;
	}
	if (content.conv == E_NOT_CONV)
		*printed_len += put_notconv_count(str, str_i);
	else
		*printed_len += put_string_or_nbr(ap, &content);
	return (str_i);
}

int			ft_printf(const char *format, ...)
{
	va_list	ap;
	int		printed_len;
	int		i;
	char	*tmp_format;

	tmp_format = (char *)format;
	va_start(ap, format);
	printed_len = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
			i += process_percent(&ap, tmp_format + i, &printed_len);
		else
		{
			printed_len += put_char_count(format[i]);
			i++;
		}
	}
	va_end(ap);
	return (printed_len);
}
