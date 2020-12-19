/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_conv_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 16:55:18 by skotoyor          #+#    #+#             */
/*   Updated: 2020/12/19 17:33:28 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	put_conv_c(va_list *ap, t_content *content)
{
	int		i;
	char	c;
	int		put_len;

	i = 1;
	put_len = 0;
	c = (char)va_arg(*ap, int);
	if (content->flag[E_MINUS])
	{
		put_len += put_char_count(c);
		while (i++ < content->width)
			put_len += put_char_count(' ');
	}
	else
	{
		while (i++ < content->width)
			put_len += put_char_count(' ');
		put_len += put_char_count(c);
	}
	return (put_len);
}
