/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 19:08:07 by skotoyor          #+#    #+#             */
/*   Updated: 2020/11/27 21:43:17 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_char_count(char c, int *printed_len)
{
	// printf("========\n%d\n",*printed_len);
	write(1, &c, 1);
	*printed_len += 1;
	// printf("\n%d\n",*printed_len);
}

int		is_conversion(char c, t_content *content)
{
	if (c == 'c')
		is_char(content);
	else if (c == 's')
		is_string(content);
	else if (c == 'p')
		is_pointer(content);
	else if (c == 'd')
		is_decimal(content);
	else if (c == 'i')
		is_integer(content);
	else if (c == 'u')
		is_unsigned(content);
	else if (c == 'x')
		is_x_small(content);
	else if (c == 'X')
		is_x_large(content);
	else if (c == '%')
		is_percent(content);
	return (content->conv);
}

void	init_content(t_content *content)
{
	content->flag[E_MINUS] = 0;
	content->flag[E_ZERO] = 0;
	content->width = 0;
	content->prec = 0;
	content->conv = E_NOT_CONV;
}